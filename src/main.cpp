/*
 * Copyright (c) 2026 HeZhijun (CodeManStudio)
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

/**
 * @file main.cpp
 * @brief MK-ServerLauncher 桌面版主程序入口
 * @author CodeManStudio
 * @version ?
 * @date 2026-02-28
 *
 * @details
 * 该文件是应用程序的入口点，负责初始化Qt环境、
 * 设置日志系统和创建主窗口。
 */
#include <WinSock2.h>
#include "FileGuy.hpp"
#include "HolyHead.hpp"
#include "MainWindow.hpp"

namespace proc = boost::process::v2;
/**
 * @brief 应用程序入口点
 *
 * 初始化Qt应用程序，设置日志系统，创建并显示主窗口
 * 这是MK-ServerLauncher桌面版的启动入口
 */
int main(int argc, char* argv[])
{
    boost::asio::io_context ctx;



    //初始化Qt应用程序
    QApplication app(argc, argv);

    spdlog::set_pattern("[%H:%M:%S][%^%l%$][%n]: %v");

    //使用spdlog的彩色控制台输出，日志器名称为"main,
    const auto serverLogger = spdlog::stdout_color_mt("server");
    const auto clientLogger = spdlog::stdout_color_mt("client");
    const auto MainLogger = spdlog::stdout_color_mt("main");
    const std::filesystem::path ExeDir=std::filesystem::path(argv[0]).parent_path();
    CMS::FileManager FileGay(MainLogger,ExeDir);
    const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        FileGay.GetLogFilePath().string(),
        true
    );
    serverLogger->sinks().push_back(file_sink);
    clientLogger->sinks().push_back(file_sink);
    MainLogger->sinks().push_back(file_sink);

    MainLogger->info("Checking MuView");
    if (!(FileGay.CheckMu()))
    {
        //TODO

    }
    MainLogger->info("Creating pipe...");
    boost::asio::readable_pipe pipe_out{ctx};
    MainLogger->info("Creating process...");
    auto java_path = proc::environment::find_executable("java");
    proc::process p(
    ctx,
    java_path.string(),
    {"-jar", (ExeDir/"MuView-all.jar").string()},
    proc::process_stdio{{},pipe_out,{}});
    MainLogger->info("Process created, checking running status...");
    if (!p.running()) {
        MainLogger->error("sub process bad！");

    }
    MainLogger->info("After running check");



    app.setApplicationName("MK-ServerLauncher Desktop");
    app.setOrganizationName("MuVerse / CodeManStudio");
    app.setApplicationVersion("26.1.0-beta");


    //创建主窗口实例，传入日志器
    //父窗口为nullptr，表示这是一个顶级窗口
    CMS::MainWindow window(nullptr, MainLogger);


    window.show();

    const std::string idk = R"(# 系统启动

欢迎使用 MK-ServerLauncherDesktop
版本: 0.0.5-Demo

CMSToolkit : 1.1.0

## 初始化完成


)";




    window.PushMessageToMainOverview(idk);


    std::vector<char> buffer(1024);
    std::function<void(boost::system::error_code, std::size_t)> read_loop=
        [&](const boost::system::error_code& ec, std::size_t length)
        {
            MainLogger->info("asio read_loop,ec= {}, length= {}", ec.value(), length);
            if (ec) {
                if (ec != boost::asio::error::eof && ec != boost::asio::error::broken_pipe) {MainLogger->error(ec.message());}return;
            }
            std::string output(buffer.data(), length);

            QMetaObject::invokeMethod(&window, [&window, output]() {
                emit window.OverviewMessageReceived(output);
            }, Qt::QueuedConnection);
            pipe_out.async_read_some(
                boost::asio::buffer(buffer.data(), buffer.size()),
                read_loop
            );
        };
    std::unique_ptr<std::thread>MKSL;
    if (p.running())
    {
        pipe_out.async_read_some(boost::asio::buffer(buffer.data(), buffer.size()),read_loop);
        MKSL=std::make_unique<std::thread>([&]() {ctx.run();});
    }


    MainLogger->info("MKSL Inited");

    window.wsManager->Start();

    MainLogger->info("Window showed");
    std::cout << "CMSToolkit_Ver: " << CMS_Ver << std::endl;cms::Init();std::cout << "CMSToolkit : " << "Included" << std::endl;


    int exitCode = app.exec();
    if (p.running()) {
        p.terminate();
    }
    int code = p.wait();

    if (MKSL && MKSL->joinable()) {
        ctx.stop();
        MKSL->join();
    }

    MainLogger->info("asio code : {} ",code);



    return exitCode;
}
