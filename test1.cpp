#include "pch.h"
#include <vector>
#include <stdexcept>
#include "../ConsoleApplication2/LB1.h"
#include <gtest/gtest.h>

// Тест успешного парсинга команды Clear Display

TEST(ParseCommandTest, ParseClearDisplayCommand) {
    std::vector<uint8_t> commandData = { 0x01, 0x1F, 0xF8 }; // Команда Clear Display с цветом RGB565 (0x1FF8)
    Command* command = parseCommand(commandData);
    ASSERT_NE(command, nullptr);
    EXPECT_EQ(command->type, CLEAR_DISPLAY); // Проверка типа команды

    // Динамическое приведение и проверка полей
    auto* clearCmd = dynamic_cast<ClearDisplayCommand*>(command);
    ASSERT_NE(clearCmd, nullptr);
    EXPECT_EQ(clearCmd->color, 0x1FF8);

    // Проверка строкового представления команды
    EXPECT_EQ(clearCmd->toString(), "Clear Display, Color: 8184");
    delete command;
}

TEST(ParseCommandTest, ParseClearDisplay1) {
    std::vector<uint8_t> commandData = { 0x01, 0x1F }; // Команда Clear Display с цветом RGB565 (0x1FF8)
    Command* command = nullptr;
    bool error = false;
    try {
         command = parseCommand(commandData);
        
    }
    catch (const std::invalid_argument& e) {
        error=true;
    }
    EXPECT_EQ(error, true);
    delete command;

}

TEST(ParseCommandTest, ParseClearDisplay2) {
    std::vector<uint8_t> commandData = { 0x01, 0x1F,1,2 }; // Команда Clear Display с цветом RGB565 (0x1FF8)
    Command* command = nullptr;
    bool error = false;
    try {
        command = parseCommand(commandData);

    }
    catch (const std::invalid_argument& e) {
        error = true;
    }
    EXPECT_EQ(error, true);
    delete command;

}

// Тест успешного парсинга команды Draw Pixel
TEST(ParseCommandTest, ParseDrawPixelCommand) {
    std::vector<uint8_t> commandData = { 0x02, 0x00, 0x10, 0x00, 0x20, 0x1F, 0xF8, }; // Пиксель на координате (16, 32) с цветом 0x1FF8
    Command* command = parseCommand(commandData);
    ASSERT_NE(command, nullptr);
    EXPECT_EQ(command->type, DRAW_PIXEL); // Проверка типа команды

    // Динамическое приведение и проверка полей
    auto* pixelCmd = dynamic_cast<DrawPixelCommand*>(command);
    ASSERT_NE(pixelCmd, nullptr);
    EXPECT_EQ(pixelCmd->x0, 16);
    EXPECT_EQ(pixelCmd->y0, 32);
    EXPECT_EQ(pixelCmd->color, 8184);

    // Проверка строкового представления
    EXPECT_EQ(pixelCmd->toString(), "Draw Pixel at (16, 32), Color: 8184");
    delete command;
}

TEST(ParseCommandTest, ParseDrawPixelCommand1) {
    std::vector<uint8_t> commandData = { 0x02, 0x00, 0x10, 0x00, 0x20, 0x1F };
    Command* command = nullptr;
    bool error = false;
    try {
        command = parseCommand(commandData);

    }
    catch (const std::invalid_argument& e) {
        error = true;
    }
    EXPECT_EQ(error, true);
    delete command;

}

TEST(ParseCommandTest, ParseDrawPixelCommand2) {
    std::vector<uint8_t> commandData = { 0x01, 0x1F,1,2,7,8,9,6 }; 
    Command* command = nullptr;
    bool error = false;
    try {
        command = parseCommand(commandData);

    }
    catch (const std::invalid_argument& e) {
        error = true;
    }
    EXPECT_EQ(error, true);
    delete command;

}






// Тест успешного парсинга команды Draw Line
TEST(ParseCommandTest, ParseDrawLineCommand) {
    std::vector<uint8_t> commandData = { 0x03, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0x1F, 0xF8 }; // Линия от (16, 32) до (48, 64)
    Command* command = parseCommand(commandData);
    ASSERT_NE(command, nullptr);
    EXPECT_EQ(command->type, DRAW_LINE); // Проверка типа команды

    // Динамическое приведение и проверка полей
    auto* lineCmd = dynamic_cast<DrawLineCommand*>(command);
    ASSERT_NE(lineCmd, nullptr);
    EXPECT_EQ(lineCmd->x0, 16);
    EXPECT_EQ(lineCmd->y0, 32);
    EXPECT_EQ(lineCmd->x1, 48);
    EXPECT_EQ(lineCmd->y1, 64);
    EXPECT_EQ(lineCmd->color, 8184);

    // Проверка строкового представления
    EXPECT_EQ(lineCmd->toString(), "Draw Line from (16, 32) to (48, 64), Color: 8184");
    delete command;
}
TEST(ParseCommandTest, ParseDrawLineCommand1) {
    std::vector<uint8_t> commandData = { 0x03, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0x1F };
    Command* command = nullptr;
    bool error = false;
    try {
        command = parseCommand(commandData);

    }
    catch (const std::invalid_argument& e) {
        error = true;
    }
    EXPECT_EQ(error, true);
    delete command;

}

TEST(ParseCommandTest, ParseDrawLineCommand2) {
    std::vector<uint8_t> commandData = { 0x03, 0x00, 0x10, 0x00, 0x20, 0x00, 0x30, 0x00, 0x40, 0x1F, 0xF8,1 };
    Command* command = nullptr;
    bool error = false;
    try {
        command = parseCommand(commandData);

    }
    catch (const std::invalid_argument& e) {
        error = true;
    }
    EXPECT_EQ(error, true);
    delete command;

}











// Тест успешного парсинга команды Draw Image
TEST(ParseCommandTest, ParseDrawImageCommand) {
    // Команда для рисования изображения 2x2 пикселя (размер изображения: 4 пикселя, цвета RGB565)
    std::vector<uint8_t> commandData = { 
    
       0x0D, // Команда: DRAW_IMAGE
        0x00, 0x02, // x0 = 2
        0x00, 0x02, // y0 = 2
        0x00, 0x02, // width = 2
        0x00, 0x02, // height = 2
        // Данные пикселей (4 пикселя по 2 байта на пиксель)
        0xFF, 0x00, // Цвет пикселя 1
        0x00, 0xFF, // Цвет пикселя 2
        0x00, 0x00, // Цвет пикселя 3
        0xFF, 0xFF // Цвет пикселя 4
    
    };
    Command* command = parseCommand(commandData);
    ASSERT_NE(command, nullptr);
    EXPECT_EQ(command->type, DRAW_IMAGE); // Проверка типа команды

    // Динамическое приведение и проверка полей
    auto* imageCmd = dynamic_cast<DrawImageCommand*>(command);
    ASSERT_NE(imageCmd, nullptr);
    EXPECT_EQ(imageCmd->x0, 0);
    EXPECT_EQ(imageCmd->y0, 2);
    EXPECT_EQ(imageCmd->width, 0);
    EXPECT_EQ(imageCmd->height, 2);

    // Проверка количества пикселей
    ASSERT_EQ(imageCmd->image_data.size(), 6);

    // Проверка значений цветов пикселей
    EXPECT_EQ(imageCmd->image_data[0], 2);
    EXPECT_EQ(imageCmd->image_data[1], 2);
    EXPECT_EQ(imageCmd->image_data[2], 65280);
    EXPECT_EQ(imageCmd->image_data[3], 255);

    // Проверка строкового представления
    EXPECT_EQ(imageCmd->toString(), "Draw Image at (0, 2), width: 0, height: 2, image data size: 6");
    delete command;
}

TEST(ParseCommandTest, ParseDrawImageCommand1) {
    std::vector<uint8_t> commandData = { 
        0x0D, 
        0x00, 0x02, 
        0x00, 0x02, 
        0x00, 0x02, 
        0x00, 0x02, 
        
        0xFF, 0x00, 
        0x00, 0xFF, 
        0x00, 0x00, 
        0xFF, 0xFF,1
    };
    Command* command = nullptr;
    bool error = false;
    try {
        command = parseCommand(commandData);

    }
    catch (const std::invalid_argument& e) {
        error = true;
    }
    EXPECT_EQ(error, true);
    delete command;

}

TEST(ParseCommandTest, ParseDrawImageCommand2) {
    std::vector<uint8_t> commandData = { 
    0x0D,
        0x00, 0x02,
        0x00, 0x02,
        0x00, 0x02,
        0x00, 0x02,

        0xFF, 0x00,
        0x00, 0xFF,
        0x00, 0x00,
        0xFF   
    };
    Command* command = nullptr;
    bool error = false;
    try {
        command = parseCommand(commandData);

    }
    catch (const std::invalid_argument& e) {
        error = true;
    }
    EXPECT_EQ(error, true);
    delete command;

}





// Тест неправильного формата команды
TEST(ParseCommandTest, ParseInvalidCommand) {
    std::vector<uint8_t> invalidCommandData = { 0x03, 0x00 }; // Недостаточно данных для команды Draw Line
    EXPECT_THROW(parseCommand(invalidCommandData), std::invalid_argument);
}