import unittest

class TestDisplayProtocol(unittest.TestCase):
    def setUp(self):
        self.protocol = DisplayProtocol()

    def test_clear_display(self):
        command = [0x01, 0x07E0]  # RGB565, зелёный цвет
        result = self.protocol.parse_command(command)
        self.assertEqual(result, "Clearing display with color 2016")  # 0x07E0 соответствует зелёному цвету в RGB565

    def test_draw_pixel(self):
        command = [0x02, 10, 20, 0x07E0]  # x=10, y=20, цвет = зелёный
        result = self.protocol.parse_command(command)
        self.assertEqual(result, "Drawing pixel at (10, 20) with color 2016")

    def test_draw_line(self):
        command = [0x03, 10, 20, 30, 40, 0x07E0]  # линия от (10, 20) до (30, 40), цвет = зелёный
        result = self.protocol.parse_command(command)
        self.assertEqual(result, "Drawing line from (10, 20) to (30, 40) with color 2016")

    def test_invalid_command(self):
        command = [0x99]  # несуществующая команда
        result = self.protocol.parse_command(command)
        self.assertEqual(result, "Unknown command")

    def test_invalid_parameters(self):
        command = [0x02, 10]  # Недостаточно параметров для команды draw pixel
        result = self.protocol.parse_command(command)
        self.assertEqual(result, "Error: Expected 3 parameters, got 1")

if __name__ == '__main__':
    unittest.main()
