#ifndef LB1_H
#define LB1_H

#include <vector>
#include <string>
#include <stdexcept>
#include <cstdint>

// Определение типов команд
enum CommandType {
    CLEAR_DISPLAY = 0x01,
    DRAW_PIXEL = 0x02,
    DRAW_LINE = 0x03,
    DRAW_RECTANGLE = 0x04,
    FILL_RECTANGLE = 0x05,
    DRAW_ELLIPSE = 0x06,
    FILL_ELLIPSE = 0x07,
    DRAW_IMAGE = 0x0D,
    // Добавьте другие типы команд здесь
};

// Базовый класс для команд
class Command {
public:
    CommandType type;

    virtual std::string toString() const = 0; // Чистая виртуальная функция для строкового представления
    virtual ~Command() = default; // Виртуальный деструктор
};

// Класс для команды Clear Display
class ClearDisplayCommand : public Command {
public:
    uint16_t color;

    ClearDisplayCommand(uint16_t color) : color(color) {
        type = CLEAR_DISPLAY;
    }

    std::string toString() const override {
        return "Clear Display, Color: " + std::to_string(color);
    }
};

// Класс для команды Draw Pixel
class DrawPixelCommand : public Command {
public:
    int x0, y0;
    uint16_t color;

    DrawPixelCommand(int x, int y, uint16_t color) : x0(x), y0(y), color(color) {
        type = DRAW_PIXEL;
    }

    std::string toString() const override {
        return "Draw Pixel at (" + std::to_string(x0) + ", " + std::to_string(y0) + "), Color: " + std::to_string(color);
    }
};

// Класс для команды Draw Line
class DrawLineCommand : public Command {
public:
    int x0, y0, x1, y1;
    uint16_t color;

    DrawLineCommand(int x0, int y0, int x1, int y1, uint16_t color)
        : x0(x0), y0(y0), x1(x1), y1(y1), color(color) {
        type = DRAW_LINE;
    }

    std::string toString() const override {
        return "Draw Line from (" + std::to_string(x0) + ", " + std::to_string(y0) +
            ") to (" + std::to_string(x1) + ", " + std::to_string(y1) + "), Color: " + std::to_string(color);
    }
};

// Класс для команды Draw Rectangle
class DrawRectangleCommand : public Command {
public:
    int x0, y0, width, height;
    uint16_t color;

    DrawRectangleCommand(int x0, int y0, int width, int height, uint16_t color)
        : x0(x0), y0(y0), width(width), height(height), color(color) {
        type = DRAW_RECTANGLE;
    }

    std::string toString() const override {
        return "Draw Rectangle at (" + std::to_string(x0) + ", " + std::to_string(y0) +
            "), width: " + std::to_string(width) +
            ", height: " + std::to_string(height) +
            ", Color: " + std::to_string(color);
    }
};

// Класс для команды Fill Rectangle
class FillRectangleCommand : public Command {
public:
    int x0, y0, width, height;
    uint16_t color;

    FillRectangleCommand(int x0, int y0, int width, int height, uint16_t color)
        : x0(x0), y0(y0), width(width), height(height), color(color) {
        type = FILL_RECTANGLE;
    }

    std::string toString() const override {
        return "Fill Rectangle at (" + std::to_string(x0) + ", " + std::to_string(y0) +
            "), width: " + std::to_string(width) +
            ", height: " + std::to_string(height) +
            ", Color: " + std::to_string(color);
    }
};

// Класс для команды Draw Ellipse
class DrawEllipseCommand : public Command {
public:
    int x0, y0, width, height;
    uint16_t color;

    DrawEllipseCommand(int x0, int y0, int width, int height, uint16_t color)
        : x0(x0), y0(y0), width(width), height(height), color(color) {
        type = DRAW_ELLIPSE;
    }

    std::string toString() const override {
        return "Draw Ellipse at (" + std::to_string(x0) + ", " + std::to_string(y0) +
            "), width: " + std::to_string(width) +
            ", height: " + std::to_string(height) +
            ", Color: " + std::to_string(color);
    }
};

// Класс для команды Fill Ellipse
class FillEllipseCommand : public Command {
public:
    int x0, y0, width, height;
    uint16_t color;

    FillEllipseCommand(int x0, int y0, int width, int height, uint16_t color)
        : x0(x0), y0(y0), width(width), height(height), color(color) {
        type = FILL_ELLIPSE;
    }

    std::string toString() const override {
        return "Fill Ellipse at (" + std::to_string(x0) + ", " + std::to_string(y0) +
            "), width: " + std::to_string(width) +
            ", height: " + std::to_string(height) +
            ", Color: " + std::to_string(color);
    }
};

// Класс для команды Draw Image
class DrawImageCommand : public Command {
public:
    int x0, y0, width, height;
    std::vector<uint16_t> image_data;

    DrawImageCommand(int x0, int y0, int width, int height, const std::vector<uint16_t>& image_data)
        : x0(x0), y0(y0), width(width), height(height), image_data(image_data) {
        type = DRAW_IMAGE;
    }

    std::string toString() const override {
        return "Draw Image at (" + std::to_string(x0) + ", " + std::to_string(y0) +
            "), width: " + std::to_string(width) +
            ", height: " + std::to_string(height) +
            ", image data size: " + std::to_string(image_data.size());
    }
};

// Функция для парсинга команд
Command* parseCommand(const std::vector<uint8_t>& rawData) {
    if (rawData.empty()) {
        throw std::invalid_argument("Raw data cannot be empty");
    }

    switch (rawData[0]) {
    case CLEAR_DISPLAY: {
        if (rawData.size() != 3) {
            throw std::invalid_argument("Insufficient data for Clear Display commandCD");
        }
        uint16_t color = (rawData[1] << 8) | rawData[2]; // Пример конвертации цвета
        return new ClearDisplayCommand(color);
    }
    case DRAW_PIXEL: {
        if (rawData.size() != 7) {
            throw std::invalid_argument("Insufficient data for Draw Pixel commandXXX");
        }
        int x = (rawData[1] <<8)| rawData [2];
        int y = (rawData[3] <<8)| rawData[4];
        uint16_t color = (rawData[5] << 8) | rawData[6]; // Пример конвертации цвета
        return new DrawPixelCommand(x, y, color);
    }
    case DRAW_LINE: {
        if (rawData.size() != 11) {
            throw std::invalid_argument("Insufficient data for Draw Line command");
        }
        int x0 = (rawData[1] << 8) | rawData[2];
        int y0 = (rawData[3] << 8) | rawData[4];
        int x1 = (rawData[5] << 8) | rawData[6];
        int y1 = (rawData[7] << 8) | rawData[8];
        uint16_t color = (rawData[9] << 8) | rawData[10]; // Пример конвертации цвета
        return new DrawLineCommand(x0, y0, x1, y1, color);
    }
    case DRAW_RECTANGLE: {
        if (rawData.size() != 11) {
            throw std::invalid_argument("Insufficient data for Draw Rectangle command");
        }
         int x0 = (rawData[1] << 8) | rawData[2];
     int y0 = (rawData[3] << 8) | rawData[4];
     int width = (rawData[5] << 8) | rawData[6];
     int height = (rawData[7] << 8) | rawData[8];
     uint16_t color = (rawData[9] << 8) | rawData[10];  // Пример конвертации цвета
        return new DrawRectangleCommand(x0, y0, width, height, color);
    }
    case FILL_RECTANGLE: {
        if (rawData.size() != 7) {
            throw std::invalid_argument("Insufficient data for Fill Rectangle command");
        }
        int x0 = rawData[1];
        int y0 = rawData[2];
        int width = rawData[3];
        int height = rawData[4];
        uint16_t color = (rawData[5] << 8) | rawData[6]; // Пример конвертации цвета
        return new FillRectangleCommand(x0, y0, width, height, color);
    }
    case DRAW_ELLIPSE: {
        if (rawData.size() != 7) {
            throw std::invalid_argument("Insufficient data for Draw Ellipse command");
        }
        int x0 = rawData[1];
        int y0 = rawData[2];
        int width = rawData[3];
        int height = rawData[4];
        uint16_t color = (rawData[5] << 8) | rawData[6]; // Пример конвертации цвета
        return new DrawEllipseCommand(x0, y0, width, height, color);
    }
    case FILL_ELLIPSE: {
        if (rawData.size() != 7) {
            throw std::invalid_argument("Insufficient data for Fill Ellipse command");
        }
        int x0 = rawData[1];
        int y0 = rawData[2];
        int width = rawData[3];
        int height = rawData[4];
        uint16_t color = (rawData[5] << 8) | rawData[6]; // Пример конвертации цвета
        return new FillEllipseCommand(x0, y0, width, height, color);
    }
    case DRAW_IMAGE: {
        if (rawData.size() != 17) {
            throw std::invalid_argument("Insufficient data for Draw Image command");
        }
        int x0 = rawData[1];
        int y0 = rawData[2];
        int width = rawData[3];
        int height = rawData[4];
        std::vector<uint16_t> image_data;
        for (size_t i = 5; i < rawData.size(); i += 2) {
            if (i + 1 < rawData.size()) {
                uint16_t pixel_color = (rawData[i] << 8) | rawData[i + 1];
                image_data.push_back(pixel_color);
            }
        }
        return new DrawImageCommand(x0, y0, width, height, image_data);
    }
    default:
        throw std::invalid_argument("Unknown command type");
    }
}

#endif // LB1_H
