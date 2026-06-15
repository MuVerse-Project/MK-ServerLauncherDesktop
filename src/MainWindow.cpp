/**
 * @file MainWindow.cpp
 * @brief MK-ServerLauncher 桌面版主窗口实现文件
 * @author CodeManStudio
 * @version 1.0.0
 * @date 2026-02-28
 *
 * @details
 * 实现了 MainWindow 类的所有成员函数
 * 包括窗口初始化、日志设置和资源清理等功能
*/

#include "ui_Client.h"
#include "MainWindow.hpp"
#include <QWidget>
#include <QDebug>
#include <QButtonGroup>
#include <QFile>
namespace CMS {
	/**
	 * @brief 构造函数实现
	 *
	 * 初始化主窗口，包括：
	 * 调用基类 QMainWindow 构造函数
	 * 创建 UI 对象（由 Qt Designer 生成）
	 * 初始化日志器
	 * 设置窗口属性
	 * 加载 UI 布局
	 * 应用深色主题样式
	 *
	 * @param parent 父窗口指针，默认为 nullptr
	 * @param logger spdlog 日志器指针
	 *
	 * @note 日志器必须在构造函数中初始化，否则无法记录早期日志
	 * @see ~MainWindow() 析构函数负责清理资源
	 */
	MainWindow::MainWindow(QWidget* parent, const std::shared_ptr<spdlog::logger>& logger)
		: QWidget(parent), logger_(logger), ui(new Ui::Form)
	{
		setupFonts();


		logger_->info("MainWindow Created");
		setWindowTitle("MK-ServerLauncher Desktop"); ui->setupUi(this);


		//TODO(Hzj) : Actually idk what to do

		QButtonGroup* buttongroup = new QButtonGroup(this);
		buttongroup->addButton(ui->btnOverview, 0);
		buttongroup->addButton(ui->btnServer, 1);
		buttongroup->addButton(ui->btnEnvironment, 2);
		buttongroup->addButton(ui->btnAbout, 3);
		if (QFile file(":/Dark/darkstyle.qss"); file.open(QFile::ReadOnly)) {
			const QString styleSheet = QLatin1String(file.readAll());
			qApp->setStyleSheet(styleSheet);
			file.close();
		}
		else {
			qDebug() << "Failed to load stylesheet:" << file.errorString();
		}

		connect(buttongroup, QOverload<int>::of(&QButtonGroup::idClicked), this, [this](int id) {
			ui->stackedWidget->setCurrentIndex(id);

			});
	}

	MainWindow::~MainWindow()
	{
		logger_->info("Application destoyed success");
		delete ui;
	}

	void MainWindow::setupFonts() const
	{
		QFont appFont;

		const QString engFontPath = ":/res/JetBrainsMono-Medium.ttf";
		const QString chnFontPath = ":/res/SarasaMonoSC-SemiBold.ttf";

		const int engFontId = QFontDatabase::addApplicationFont(engFontPath);
		const int chnFontId = QFontDatabase::addApplicationFont(chnFontPath);

		QStringList fontFallbackList;


		if (engFontId != -1) {
			QStringList families = QFontDatabase::applicationFontFamilies(engFontId);
			if (!families.isEmpty())
				fontFallbackList << families.first();
		}

		if (chnFontId != -1) {
			QStringList families = QFontDatabase::applicationFontFamilies(chnFontId);
			if (!families.isEmpty())
				fontFallbackList << families.first();
		}



		appFont.setFamilies(fontFallbackList);
		appFont.setPointSize(10);
		qApp->setFont(appFont);


		if (logger_) {
			if (engFontId != -1 && chnFontId != -1) {
				logger_->info("Custom fonts loaded successfully");
			}
			else {
				logger_->warn("Using system fonts (custom fonts not available)");
			}
		}
	}
	void MainWindow::PushMessageToMainOverview(const QString& message) {
		if (!OverviewText.isEmpty()) { OverviewText += "\n\n"; }
		OverviewText += message;
		ui->textEdit->setMarkdown(OverviewText);
	}
} // namespace CMS