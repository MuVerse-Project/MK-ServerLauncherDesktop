// HolyHead.hpp
#ifndef HOLYHEAD_H
#define HOLYHEAD_H
#ifndef NOMINMAX
#define NOMINMAX
#endif
// ==================== C++标准库（最先包含） ====================
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <filesystem>
#include <vector>  // 添加 vector 支持

// ==================== 第三方库 ====================
//Boost
#include <boost/asio.hpp>
#include <boost/process/v2/process.hpp>
#include <boost/process/v2/stdio.hpp>
#include <boost/process/v2/environment.hpp>


// 日志库（在 FileGuy 之前包含）
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

// 加密库 (Crypto++)
#include <cryptopp/crc.h>
#include <cryptopp/sha.h>
#include <cryptopp/sm3.h>
#include <cryptopp/filters.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>

// YAML处理
#include <yaml-cpp/yaml.h>

// JSON处理
#include <nlohmann/json.hpp>

// 硬件信息


// ==================== Qt库 ====================
#include <QObject>
#include <QWidget>
#include <QPointer>
#include <QMainWindow>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QButtonGroup>
#include <QFile>
#include <QFontDatabase>
#include <QDebug>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>
#include <QThread>
#include <QGraphicsOpacityEffect>

// ==================== 项目头文件（最后包含） ====================
// 注意：这些文件依赖于上面的头文件
#include <nlohmann/json.hpp>
#include "ui_Client.h"
#include <cms_toolkit_dll.hpp>
#endif // HOLYHEAD_H