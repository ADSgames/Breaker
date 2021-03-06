#include "MouseListener.h"
#include "../globals.h"

unsigned char MouseListener::mouse_button = 0;
unsigned char MouseListener::mouse_pressed = 0;
unsigned char MouseListener::mouse_released = 0;
unsigned char MouseListener::mouse_old = 0;
unsigned int MouseListener::x = 0;
unsigned int MouseListener::y = 0;

int MouseListener::mouse_z_change = 0;
int MouseListener::mouse_z_old = 0;

// Check those buttons!
void MouseListener::update() {
  // Check button just pressed
  for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
    // Clear old values
    mouse_pressed &= ~(1 << i);
    mouse_released &= ~(1 << i);

    // Down or not
    int check_state = ((mouse_b >> i) & 1);
    mouse_button = (mouse_button & ~(1 << i)) | (check_state << i);

    // Pressed since last tick?
    if (((mouse_button >> i) & 1) != 0 && ((mouse_old >> i) & 1) == 0)
      mouse_pressed |= 1 << i;

    // Released since last tick?
    if (((mouse_button >> i) & 1) == 0 && ((mouse_old >> i) & 1) != 0)
      mouse_released |= 1 << i;

    // Button changed
    if (((mouse_button >> i) & 1) != ((mouse_old >> i) & 1))
      mouse_old ^= 1 << i;
  }

  // Update scroll wheel
  mouse_z_change = 0;

  if (mouse_z != mouse_z_old) {
    mouse_z_change = mouse_z - mouse_z_old;
    mouse_z_old = mouse_z;
  }

  x = mouse_x * NATIVE_SCREEN_W / SCREEN_W;
  y = mouse_y * NATIVE_SCREEN_H / SCREEN_H;
}
