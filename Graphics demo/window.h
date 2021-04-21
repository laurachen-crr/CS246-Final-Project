#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <vector>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  std::vector<std::vector<char>> layout;
  unsigned long colours[10];

 public:
  Xwindow(int width=800, int height=800);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.
  Xwindow(const Xwindow&) = delete;
  Xwindow &operator=(const Xwindow&) = delete;

  enum {White=0, Gray, Red, Green, Blue}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Gray);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  // Draws a grid
  void drawGrid();

};

#endif
