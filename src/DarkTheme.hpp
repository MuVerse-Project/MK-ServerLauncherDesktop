#ifndef DARK_THEME_H
#define DARK_THEME_H

#include <QString>

namespace CMS {

    const QString DARK_STYLESHEET = R"(
/* ===== 全局样式 ===== */
* 

QWidget {
    background-color: #1e1e1e;
    color: #e0e0e0;
}

/* ===== 主窗口 ===== */
QWidget#Form {
    background-color: #1e1e1e;
    border: none;
}

/* ===== 左侧导航栏 ===== */
QWidget#leftVBox {
    background-color: #252526;
    border-right: 1px solid #3c3c3c;
}

/* ===== 标题标签 ===== */
QLabel#titleLabel {
    color: #ffffff;
    font-size: 15px;
    font-weight: bold;
    background-color: transparent;
}

QLabel#logoLabel {
    background-color: transparent;
}

/* ===== 导航按钮 ===== */
QPushButton {
    background-color: #2d2d2d;
    color: #e0e0e0;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    padding: 8px 16px;
    font-size: 14px;
    font-weight: bold;
    text-align: left;
}

QPushButton:hover {
    background-color: #3c3c3c;
    border-color: #505050;
}

QPushButton:pressed {
    background-color: #0e5c9e;
    border-color: #0a4780;
    color: #ffffff;
}

QPushButton:checked {
    background-color: #0e639c;
    border-color: #0a4780;
    color: #ffffff;
}

/* ===== 右侧内容区 ===== */
QStackedWidget {
    background-color: #1e1e1e;
    border: none;
}

/* ===== Overview 页面 - 日志框 ===== */
QPlainTextEdit#logView {
    background-color: #1e1e1e;
    color: #d4d4d4;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    font-family: "Consolas", "Courier New", monospace;
    font-size: 12px;
    selection-background-color: #264f78;
}

QPlainTextEdit#logView:focus {
    border-color: #0e639c;
}

/* ===== Server 页面 ===== */
QGroupBox {
    background-color: #252526;
    color: #ffffff;
    border: 1px solid #3c3c3c;
    border-radius: 4px;
    margin-top: 12px;
    font-weight: bold;
}

QGroupBox::title {
    subcontrol-origin: margin;
    left: 10px;
    padding: 0 5px 0 5px;
    color: #ffffff;
}

QLabel {
    color: #cccccc;
    background-color: transparent;
}

QSpinBox, QLineEdit {
    background-color: #2d2d2d;
    color: #ffffff;
    border: 1px solid #3c3c3c;
    border-radius: 3px;
    padding: 4px;
    min-height: 20px;
}

QSpinBox:focus, QLineEdit:focus {
    border-color: #0e639c;
}

QSpinBox::up-button, QSpinBox::down-button {
    background-color: #2d2d2d;
    border: 1px solid #3c3c3c;
    border-radius: 2px;
}

QSpinBox::up-button:hover, QSpinBox::down-button:hover {
    background-color: #3c3c3c;
}

/* ===== Environment 页面 - 表格 ===== */
QTableWidget {
    background-color: #1e1e1e;
    color: #e0e0e0;
    border: 1px solid #3c3c3c;
    gridline-color: #3c3c3c;
}

QTableWidget::item {
    padding: 4px;
}

QTableWidget::item:selected {
    background-color: #264f78;
    color: #ffffff;
}

QHeaderView::section {
    background-color: #252526;
    color: #ffffff;
    border: 1px solid #3c3c3c;
    padding: 4px;
    font-weight: bold;
}

/* ===== About 页面 ===== */
QLabel#aboutLabel {
    color: #ffffff;
    font-size: 14px;
    line-height: 1.6;
    background-color: transparent;
}

/* ===== 滚动条样式 ===== */
QScrollBar:vertical {
    background-color: #2d2d2d;
    width: 14px;
    border-radius: 7px;
}

QScrollBar::handle:vertical {
    background-color: #505050;
    min-height: 20px;
    border-radius: 7px;
}

QScrollBar::handle:vertical:hover {
    background-color: #606060;
}

QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
    height: 0px;
}

QScrollBar:horizontal {
    background-color: #2d2d2d;
    height: 14px;
    border-radius: 7px;
}

QScrollBar::handle:horizontal {
    background-color: #505050;
    min-width: 20px;
    border-radius: 7px;
}

QScrollBar::handle:horizontal:hover {
    background-color: #606060;
}

QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
    width: 0px;
}

/* ===== 分割线 ===== */
QFrame[frameShape="4"] {
    background-color: #3c3c3c;
}

/* ===== 按钮组特殊样式 ===== */
QPushButton#btnOverview, QPushButton#btnServer, 
QPushButton#btnEnvironment, QPushButton#btnAbout {
    text-align: left;
    padding-left: 20px;
}

/* ===== 状态标签 ===== */
QLabel#serverStatusValue[text="Running"] {
    color: #6a9955;
    font-weight: bold;
}

QLabel#serverStatusValue[text="Stopped"] {
    color: #f48771;
    font-weight: bold;
}

/* ===== 输入框占位符 ===== */
QLineEdit[placeholderText] {
    color: #888888;
}

/* ===== 工具提示 ===== */
QToolTip {
    background-color: #252526;
    color: #e0e0e0;
    border: 1px solid #3c3c3c;
    padding: 4px;
    border-radius: 3px;
}
)";

} // namespace CMS

#endif // DARK_THEME_H