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

#include <iostream>
#include <cms_toolkit_dll.hpp>
#include <QApplication>
#include "MainWindow.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "WebSocketManager.hpp"
#include <yaml-cpp/yaml.h>
/**
 * @brief 应用程序入口点
 *
 * 初始化Qt应用程序，设置日志系统，创建并显示主窗口
 * 这是MK-ServerLauncher桌面版的启动入口
 */
int main(int argc, char* argv[])
{

    //TODO(Hzj) : File read


    //初始化Qt应用程序
    QApplication app(argc, argv);

    spdlog::set_pattern("[%H:%M:%S][%^%l%$][%n]: %v");
    //使用spdlog的彩色控制台输出，日志器名称为"main"
    const auto serverLogger = spdlog::stdout_color_mt("server");
    const auto clientLogger = spdlog::stdout_color_mt("client");
    const auto MainLogger = spdlog::stdout_color_mt("main");

    app.setApplicationName("MK-ServerLauncher Desktop");
    app.setOrganizationName("MuVerse / CodeManStudio");
    app.setApplicationVersion("26.1.0-beta");

    //创建主窗口实例，传入日志器
    //父窗口为nullptr，表示这是一个顶级窗口
    CMS::MainWindow window(nullptr, MainLogger);

    CMS::WebSocketManager wsManager(&window, 20038, "127.0.0.1", 4030, "/api/v1/overview", serverLogger, clientLogger);
    window.show();

    const QString idk = R"(# 系统启动

欢迎使用 MK-ServerLauncher
版本: 其实这只是一个演示版你们知道吗

CMSToolkit : 1.0.5

## 初始化完成
)";




    window.PushMessageToMainOverview(idk);

    MainLogger->info("Window showed");

    std::cout << "CMSToolkit_Ver: " << CMS_Ver << std::endl;
    std::cout << "CMSToolkit : " << "Included" << std::endl;

    return app.exec();
}
