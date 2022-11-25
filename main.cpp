#include <cmath>
#include <cstdlib>

#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"

using namespace pimoroni;

const int WIDTH = 240;
const int HEIGHT = 240;

ST7789 st7789(WIDTH, HEIGHT, ROTATE_0, true, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);

Pen blk = graphics.create_pen(0x00, 0x00, 0x00);
Pen wht = graphics.create_pen(0xFF, 0xFF, 0xFF);
Pen red = graphics.create_pen(0xFF, 0x00, 0x00);
Pen orn = graphics.create_pen(0xFF, 0xA5, 0x00);
Pen ylw = graphics.create_pen(0xFF, 0xFF, 0x00);
Pen grn = graphics.create_pen(0x00, 0x80, 0x00);
Pen blu = graphics.create_pen(0x00, 0x00, 0xFF);
Pen pur = graphics.create_pen(0x4B, 0x00, 0x82);

void rainbow(int8_t r, int8_t w) {
    graphics.arc(
        Point(WIDTH / 2, HEIGHT / 2),
        Point(WIDTH / 2 + r, HEIGHT / 2),
        180,
        w
    );
}

int main() {
    st7789.set_backlight(255);
    Point c(120, 120);

    graphics.set_pen(blk);
    graphics.clear();

    // Demo of poly impl (rainbow)
    graphics.set_pen(red);
    rainbow(120, 10);
    graphics.set_pen(orn);
    rainbow(110, 10);
    graphics.set_pen(ylw);
    rainbow(100, 10);
    graphics.set_pen(grn);
    rainbow(90, 10);
    graphics.set_pen(blu);
    rainbow(80, 10);
    graphics.set_pen(pur);
    rainbow(70, 10);

    graphics.set_pen(wht);
    // Demo of pie
    graphics.arc(c, Point(180, 180), -90, 85);
    // Demo of line arc
    for (int i = 0; i < 6; i++) {
        graphics.arc(c, Point(239 - (i * 10), 120), -180);
    }

    st7789.update(&graphics);
}
