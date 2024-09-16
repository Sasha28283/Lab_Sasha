#include <UnitTest++/UnitTest++.h>
#include <vector>
#include <stdexcept>
#include "command_parser.hpp"  // Тут ми припускаємо, що код команд знаходиться у файлі "command_parser.hpp"

// Тест на успішний парсинг команди Clear Display
TEST(ParseClearDisplayCommand) {
    std::vector<uint8_t> commandData = {0x01, 0x1F, 0xF8};  // Clear Display з кольором 0x1FF8
    Command* command = parseCommand(commandData);
    CHECK(dynamic_cast<ClearDisplayCommand*>(command) != nullptr);  // Перевірка на правильний тип команди

    // Перетворюємо команду в текст та перевіряємо правильність виведення
    CHECK_EQUAL("Clear Display, Color: 0x1ff8", command->toString());

    delete command;
}

// Тест на успішний парсинг команди Draw Pixel
TEST(ParseDrawPixelCommand) {
    std::vector<uint8_t> commandData = {0x02, 0x00, 0x10, 0x00, 0x20, 0xFF, 0x00, 0x00, 0x00};  // Pixel на (16, 32) з кольором 0xFF0000 (червоний)
    Command* command = parseCommand(commandData);
    CHECK(dynamic_cast<DrawPixelCommand*>(command) != nullptr);

    // Перетворення команди у текст
    CHECK_EQUAL("Draw Pixel at (16, 32), Color: 0xff0000", command->toString());

    delete command;
}

// Тест на помилкову команду (недостатньо байтів)
TEST(ParseInvalidCommand) {
    std::vector<uint8_t> commandData = {0x02, 0x00};  // Некоректний розмір даних для Draw Pixel

    // Перевіряємо, що викидається виключення
    CHECK_THROW(parseCommand(commandData), std::invalid_argument);
}

// Тест на успішний парсинг команди Draw Line
TEST(ParseDrawLineCommand) {
    std::vector<uint8_t> commandData = {0x03, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0x1F, 0xF8};  // Лінія від (16, 32) до (48, 64)
    Command* command = parseCommand(commandData);
    CHECK(dynamic_cast<DrawLineCommand*>(command) != nullptr);

    // Перетворення команди у текст
    CHECK_EQUAL("Draw Line from (16, 32) to (48, 64), Color: 0x1ff8", command->toString());

    delete command;
}

// Тест на успішний парсинг команди Draw Rectangle
TEST(ParseDrawRectangleCommand) {
    std::vector<uint8_t> commandData = {0x04, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0x1F, 0xF8};  // Прямокутник на (16, 32) розміром 48x64
    Command* command = parseCommand(commandData);
    CHECK(dynamic_cast<DrawRectangleCommand*>(command) != nullptr);

    // Перетворення команди у текст
    CHECK_EQUAL("Draw Rectangle at (16, 32), width: 48, height: 64, color: 0x1ff8", command->toString());

    delete command;
}

// Тест на успішний парсинг команди Fill Ellipse
TEST(ParseFillEllipseCommand) {
    std::vector<uint8_t> commandData = {0x07, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0x1F, 0xF8};  // Заповнення еліпса
    Command* command = parseCommand(commandData);
    CHECK(dynamic_cast<FillEllipseCommand*>(command) != nullptr);

    // Перетворення команди у текст
    CHECK_EQUAL("Fill Ellipse at (16, 32), radius_x: 48, radius_y: 64, color: 0x1ff8", command->toString());

    delete command;
}

// Тест на успішний парсинг команди Draw Image
TEST(ParseDrawImageCommand) {
    std::vector<uint8_t> commandData = {0x0D, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0x01, 0x02};  // Зображення на (16, 32) з розміром 48x64
    Command* command = parseCommand(commandData);
    CHECK(dynamic_cast<DrawImageCommand*>(command) != nullptr);

    // Перетворення команди у текст
    CHECK_EQUAL("Draw Image at (16, 32), width: 48, height: 64, image data size: 2 bytes", command->toString());

    delete command;
}

// Головна функція для запуску всіх тестів
int main() {
    return UnitTest::RunAllTests();
}
