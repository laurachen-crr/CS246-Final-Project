#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cell;
class Grid;

class GraphicsDisplay {
  Display *d;
  Window w;
  int s;
  GC gc;
  vector<vector<char>> emptyboard;
  vector<vector<char>> display;
  unsigned long colours[10];

 public:
  GraphicsDisplay(int width=450, int height=450);  // Constructor; displays the window.
  ~GraphicsDisplay();                              // Destructor; destroys the window.
  GraphicsDisplay(const GraphicsDisplay&) = delete;
  GraphicsDisplay &operator=(const GraphicsDisplay&) = delete;

  enum {White=0, Gray}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Gray);

  // Draws a string
  void drawString(int x, int y, std::string msg);

  // Draws the grid
  void drawGrid(Grid& g);

  // Update the grid
  void update(Grid& g);

};

#endif
