#include <iostream>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <sstream>

enum CommandType {
    CLEAR_DISPLAY = 0x01,
    DRAW_PIXEL = 0x02,
    DRAW_LINE = 0x03,
    DRAW_RECTANGLE = 0x04,
    FILL_RECTANGLE = 0x05,
    DRAW_ELLIPSE = 0x06,
    FILL_ELLIPSE = 0x07,
    DRAW_IMAGE = 0x0D
};

// Базова структура команди
struct Command {
    CommandType type;  // Тип команди
    std::vector<uint8_t> data;  // Дані команди

    virtual std::string toString() const = 0;  // Віртуальна функція для перетворення команди в текст
    virtual ~Command() = default;  // Віртуальний деструктор для коректного видалення через базовий вказівник
};

// Структура для команди очищення дисплея
struct ClearDisplayCommand : public Command {
    uint16_t color;  // Колір у форматі RGB565

    ClearDisplayCommand(const std::vector<uint8_t>& data) {
        if (data.size() != 2) throw std::invalid_argument("Invalid data size for Clear Display");
        color = (data[0] << 8) | data[1];
    }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Clear Display, Color: 0x" << std::hex << color;
        return oss.str();
    }
};

// Структура для малювання пікселя
struct DrawPixelCommand : public Command {
    int16_t x0, y0;
    uint32_t color;  // Колір у форматі RGB888

    DrawPixelCommand(const std::vector<uint8_t>& data) {
        if (data.size() != 8) throw std::invalid_argument("Invalid data size for Draw Pixel");
        x0 = (data[0] << 8) | data[1];
        y0 = (data[2] << 8) | data[3];
        color = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
    }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Draw Pixel at (" << x0 << ", " << y0 << "), Color: 0x" << std::hex << color;
        return oss.str();
    }
};

// Структура для малювання лінії
struct DrawLineCommand : public Command {
    int16_t x0, y0, x1, y1;
    uint16_t color;  // Колір у форматі RGB565

    DrawLineCommand(const std::vector<uint8_t>& data) {
        if (data.size() != 10) throw std::invalid_argument("Invalid data size for Draw Line");
        x0 = (data[0] << 8) | data[1];
        y0 = (data[2] << 8) | data[3];
        x1 = (data[4] << 8) | data[5];
        y1 = (data[6] << 8) | data[7];
        color = (data[8] << 8) | data[9];
    }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Draw Line from (" << x0 << ", " << y0 << ") to (" << x1 << ", " << y1 << "), Color: 0x" << std::hex << color;
        return oss.str();
    }
};

// Структура для малювання прямокутника
struct DrawRectangleCommand : public Command {
    int16_t x0, y0;
    int16_t width, height;
    uint16_t color;  // Колір у форматі RGB565

    DrawRectangleCommand(const std::vector<uint8_t>& data) {
        if (data.size() != 10) throw std::invalid_argument("Invalid data size for Draw Rectangle");
        x0 = (data[0] << 8) | data[1];
        y0 = (data[2] << 8) | data[3];
        width = (data[4] << 8) | data[5];
        height = (data[6] << 8) | data[7];
        color = (data[8] << 8) | data[9];
    }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Draw Rectangle at (" << x0 << ", " << y0 << "), width: " << width 
            << ", height: " << height << ", color: 0x" << std::hex << color;
        return oss.str();
    }
};

// Структура для заповнення прямокутника
struct FillRectangleCommand : public Command {
    int16_t x0, y0;
    int16_t width, height;
    uint16_t color;  // Колір у форматі RGB565

    FillRectangleCommand(const std::vector<uint8_t>& data) {
        if (data.size() != 10) throw std::invalid_argument("Invalid data size for Fill Rectangle");
        x0 = (data[0] << 8) | data[1];
        y0 = (data[2] << 8) | data[3];
        width = (data[4] << 8) | data[5];
        height = (data[6] << 8) | data[7];
        color = (data[8] << 8) | data[9];
    }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Fill Rectangle at (" << x0 << ", " << y0 << "), width: " << width 
            << ", height: " << height << ", color: 0x" << std::hex << color;
        return oss.str();
    }
};

// Структура для малювання еліпса
struct DrawEllipseCommand : public Command {
    int16_t x0, y0;
    int16_t radius_x, radius_y;
    uint16_t color;  // Колір у форматі RGB565

    DrawEllipseCommand(const std::vector<uint8_t>& data) {
        if (data.size() != 10) throw std::invalid_argument("Invalid data size for Draw Ellipse");
        x0 = (data[0] << 8) | data[1];
        y0 = (data[2] << 8) | data[3];
        radius_x = (data[4] << 8) | data[5];
        radius_y = (data[6] << 8) | data[7];
        color = (data[8] << 8) | data[9];
    }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Draw Ellipse at (" << x0 << ", " << y0 << "), radius_x: " << radius_x 
            << ", radius_y: " << radius_y << ", color: 0x" << std::hex << color;
        return oss.str();
    }
};

// Структура для заповнення еліпса
struct FillEllipseCommand : public Command {
    int16_t x0, y0;
    int16_t radius_x, radius_y;
    uint16_t color;  // Колір у форматі RGB565

    FillEllipseCommand(const std::vector<uint8_t>& data) {
        if (data.size() != 10) throw std::invalid_argument("Invalid data size for Fill Ellipse");
        x0 = (data[0] << 8) | data[1];
        y0 = (data[2] << 8) | data[3];
        radius_x = (data[4] << 8) | data[5];
        radius_y = (data[6] << 8) | data[7];
        color = (data[8] << 8) | data[9];
    }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Fill Ellipse at (" << x0 << ", " << y0 << "), radius_x: " << radius_x 
            << ", radius_y: " << radius_y << ", color: 0x" << std::hex << color;
        return oss.str();
    }
};

// Структура для малювання зображення
struct DrawImageCommand : public Command {
    int16_t x0, y0;
    int16_t width, height;
    std::vector<uint8_t> image_data;  // Масив даних зображення у форматі RGB565

    DrawImageCommand(const std::vector<uint8_t>& data) {
        if (data.size() < 8) throw std::invalid_argument("Invalid data size for Draw Image");
        x0 = (data[0] << 8) | data[1];
        y0 = (data[2] << 8) | data[3];
        width = (data[4] << 8) | data[5];
        height = (data[6] << 8) | data[7];

        // Витягуємо масив піксельних даних (дані зображення)
        image_data = std::vector<uint8_t>(data.begin() + 8, data.end());
    }

    std::string toString() const override {
        std::ostringstream oss;
        oss << "Draw Image at (" << x0 << ", " << y0 << "), width: " << width 
            << ", height: " << height << ", image data size: " << image_data.size() << " bytes";
        return oss.str();
    }
};

// Функція для розбору команд з вхідних даних
Command* parseCommand(const std::vector<uint8_t>& rawData) {
    if (rawData.empty()) throw std::invalid_argument("Empty command data");

    CommandType commandType = static_cast<CommandType>(rawData[0]);
    std::vector<uint8_t> data(rawData.begin() + 1, rawData.end());

    switch (commandType) {
        case CLEAR_DISPLAY:
            return new ClearDisplayCommand(data);
        case DRAW_PIXEL:
            return new DrawPixelCommand(data);
        case DRAW_LINE:
            return new DrawLineCommand(data);
        case DRAW_RECTANGLE:
            return new DrawRectangleCommand(data);
        case FILL_RECTANGLE:
            return new FillRectangleCommand(data);
        case DRAW_ELLIPSE:
            return new DrawEllipseCommand(data);
        case FILL_ELLIPSE:
            return new FillEllipseCommand(data);
        case DRAW_IMAGE:
            return new DrawImageCommand(data);
        default:
            throw std::invalid_argument("Unknown command type");
    }
}

// Приклад використання
int main() {
    std::vector<uint8_t> commandData = {0x04, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0xFF, 0xFF};
    
    try {
        Command* command = parseCommand(commandData);
        std::cout << command->toString() << std::endl;
        delete command;  // Не забуваємо видаляти виділену пам'ять
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
