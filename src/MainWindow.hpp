/**
 * @file MainWindow.hpp
 * @brief MK-ServerLauncher 桌面版主窗口头文件
 * @author CodeManStudio
 * @version ?
 * @date 2026-02-28
 *
 * @details
 * 该文件是主窗口定义
 * 设置日志系统和创建主窗口
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QFontDatabase>

#include <QWidget>

#include "spdlog/spdlog.h"
#include <memory>

QT_BEGIN_NAMESPACE
/**
 * @namespace Ui
 * @brief Qt Designer 生成的 UI 类所在的命名空间
 *
 * 存在Ui::Form 类，
 * ui_client_UI.h由 uic 自动生成。
 */
namespace Ui
{
    class Form;
}

QT_END_NAMESPACE

/**
 * @brief 深色主题样式表
 *
 * 定义应用程序的深色主题外观
 * anyway I like this :/
 */
namespace CMS
{
    /**
         * @class MainWindow
         * @brief 应用程序的主窗口类
         *
         * 继承自 QMainWindow，负责创建和管理应用程序的主界面
         * UI 界面
         * spdlog 日志系统
         * 深色主题样式
         *
         * @note 使用 Ui::Form 类来访问 UI 控件*/

    class MainWindow : public QWidget

    {
        Q_OBJECT ///<Qt 元对象宏

    public:
        /**
        * @brief 构造函数
        *
        * 创建主窗口实例，初始化 UI 和日志系统。
        *
        * @param parent 父窗口指针，默认为 nullptr
        * @param logger spdlog 日志器指针，用于记录日志，默认为 nullptr
        *
        * @note 如果 logger 为 nullptr，将使用默认日志器或禁用日志功能
        * @see setupLogger()
        */
        explicit MainWindow(QWidget* parent = nullptr, const std::shared_ptr<spdlog::logger>& logger = nullptr);~MainWindow() override;
        void PushMessageToMainOverview(const QString& message);

    private:
        std::shared_ptr<spdlog::logger> logger_;Ui::Form* ui;QString OverviewText;
        void setupFonts() const;
    };
} // namespace CMS

#endif // MAINWINDOW_H
