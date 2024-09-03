class DisplayProtocol:
    def __init__(self):
        self.commands = {
            0x01: (self.clear_display, 1),  # 1 параметр: color
            0x02: (self.draw_pixel, 3),     # 3 параметра: x0, y0, color
            0x03: (self.draw_line, 5),      # 5 параметров: x0, y0, x1, y1, color
            0x04: (self.draw_rectangle, 5), # 5 параметров: x0, y0, w, h, color
            0x05: (self.fill_rectangle, 5), # 5 параметров: x0, y0, w, h, color
            0x06: (self.draw_ellipse, 5),   # 5 параметров: x0, y0, radius_x, radius_y, color
            0x07: (self.fill_ellipse, 5),   # 5 параметров: x0, y0, radius_x, radius_y, color
        }

    def clear_display(self, color):
        return f"Clearing display with color {color}"

    def draw_pixel(self, x0, y0, color):
        return f"Drawing pixel at ({x0}, {y0}) with color {color}"

    def draw_line(self, x0, y0, x1, y1, color):
        return f"Drawing line from ({x0}, {y0}) to ({x1}, {y1}) with color {color}"

    def draw_rectangle(self, x0, y0, w, h, color):
        return f"Drawing rectangle at ({x0}, {y0}) with width {w} and height {h} with color {color}"

    def fill_rectangle(self, x0, y0, w, h, color):
        return f"Filling rectangle at ({x0}, {y0}) with width {w} and height {h} with color {color}"

    def draw_ellipse(self, x0, y0, radius_x, radius_y, color):
        return f"Drawing ellipse at ({x0}, {y0}) with radii ({radius_x}, {radius_y}) with color {color}"

    def fill_ellipse(self, x0, y0, radius_x, radius_y, color):
        return f"Filling ellipse at ({x0}, {y0}) with radii ({radius_x}, {radius_y}) with color {color}"

    def parse_command(self, command):
        cmd_id = command[0]
        if cmd_id in self.commands:
            func, expected_params = self.commands[cmd_id]
            if len(command[1:]) == expected_params:
                return func(*command[1:])
            else:
                return f"Error: Expected {expected_params} parameters, got {len(command[1:])}"
        else:
            return "Unknown command"

