#include <string.h>
#include <math.h>
#include <vector>
#include <cstdlib>

#include "drivers/st7789/st7789.hpp"
#include "libraries/pico_graphics/pico_graphics.hpp"
#include "time.h"

// Place a 1.3 Round SPI LCD in the *front* slot of breakout garden.

using namespace pimoroni;


const int WIDTH = 240;
const int HEIGHT = 240;

ST7789 st7789(WIDTH, HEIGHT, ROTATE_0, true, get_spi_pins(BG_SPI_FRONT));
PicoGraphics_PenRGB332 graphics(st7789.width, st7789.height, nullptr);
Pen black = graphics.create_pen(0, 0, 0);
Pen white = graphics.create_pen(255, 255, 255);

void trivial_linear_arc(int d) {
    float r = 118;
    graphics.arc(
            Point(WIDTH / 2, HEIGHT / 2),
            Point(120 + (r * graphics.fast_sin(d)),
                  120 + (r * graphics.fast_cos(d))),
            270
    );
}

void trivial_polygon_arc(int s) {
    float r = 60;
    graphics.arc(
      Point(WIDTH / 2, HEIGHT / 2),
      Point(120 + (r * graphics.fast_sin(s)),
      120 + (r * graphics.fast_cos(s))),
      270,
      16
    );
}

int main() {
    st7789.set_backlight(255);

    for (;;) {
        for (uint16_t d = 0; d < 360; d++) {
            graphics.set_pen(black);
            graphics.clear();
            graphics.set_pen(white);
            trivial_linear_arc(d);
            trivial_polygon_arc(d);

            st7789.update(&graphics);
        }
    }
}
