#include "MainWindow.hpp"
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

		wsManager = std::make_shared<WebSocketBase>(this,20038,logger_);


		setupFonts();
		logger_->info("MainWindow Created");
		setWindowTitle("MK-ServerLauncher Desktop"); ui->setupUi(this);
		ui->envTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		ui->simple->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		//TODO(Hzj) : Actually idk what to do
		QButtonGroup* buttongroup = new QButtonGroup(this);
		buttongroup->addButton(ui->btnOverview, 0);
		buttongroup->addButton(ui->btnServer, 1);
		buttongroup->addButton(ui->btnEnvironment, 2);
		buttongroup->addButton(ui->btnAbout, 3);
		if (QFile file(":/res/Dark.qss"); file.open(QFile::ReadOnly)) {
			const QString styleSheet = QLatin1String(file.readAll());
			qApp->setStyleSheet(styleSheet);
			file.close();
		}
		else {
			logger_->error("Failed to load stylesheet: {}",file.errorString().toStdString());

		}

		connect(buttongroup, QOverload<int>::of(&QButtonGroup::idClicked), this, [this](int id) {
	if (m_isAnimating || ui->stackedWidget->currentIndex() == id) {
		return;
	}

	m_isAnimating = true;

	QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(ui->TweenGuy);
	ui->TweenGuy->setGraphicsEffect(effect);

	QSequentialAnimationGroup *group = new QSequentialAnimationGroup(this);
	QPropertyAnimation *fadeOut = new QPropertyAnimation(effect, "opacity");
	fadeOut->setDuration(100);
	fadeOut->setStartValue(1.0);
	fadeOut->setEndValue(0.0);
	fadeOut->setEasingCurve(QEasingCurve::InOutQuad);

	QPropertyAnimation *fadeIn = new QPropertyAnimation(effect, "opacity");
	fadeIn->setDuration(100);
	fadeIn->setStartValue(0.0);
	fadeIn->setEndValue(1.0);
	fadeIn->setEasingCurve(QEasingCurve::InOutQuad);

	group->addAnimation(fadeOut);
	group->addAnimation(fadeIn);

	connect(fadeOut, &QPropertyAnimation::finished, [this, id]() {
		ui->stackedWidget->setCurrentIndex(id);
	});

	connect(group, &QSequentialAnimationGroup::finished, [this, group]() {
		m_isAnimating = false;
		if (m_tween == group) {
			m_tween = nullptr;
		}
		group->deleteLater();
	});

	m_tween = group;
	group->start();
});
		connect(wsManager.get(),&WebSocketBase::systemStatusUpdated,this,[this](int cpu, int mem, int totalServer,
							 int onlineServer, int offlineServer)
		{
			ui->CPUPro->setValue(cpu);ui->MemPro->setValue(mem);
			//TODO 没必要一直刷新这个
			ui->simple->setItem(0, 0, new QTableWidgetItem(std::move(QString::number(onlineServer))));
			ui->simple->setItem(0, 1, new QTableWidgetItem(std::move(QString::number(offlineServer))));
			ui->simple->setItem(0, 2, new QTableWidgetItem(std::move(QString::number(totalServer))));

		});
		connect(this,&MainWindow::OverviewMessageReceived,this,&MainWindow::onProcessOutput,
			Qt::QueuedConnection);

	}

	void MainWindow::onProcessOutput(const std::string& msg)
	{
		PushMessageToMainOverview(msg);
	}

	MainWindow::~MainWindow()
	{
		if (m_tween) {
			m_tween->stop();
			m_tween = nullptr;
		}
		m_isAnimating = false;

		if (logger_) {
			logger_->info("Application destroyed successfully");
		}


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
	void MainWindow::PushMessageToMainOverview(const std::string_view message) {
		if (!OverviewText.isEmpty()) { OverviewText += "\n\n"; }
		OverviewText += QString::fromStdString(message.data());
		ui->textEdit->setMarkdown(OverviewText);
	}
} // namespace CMS