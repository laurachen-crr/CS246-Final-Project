#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "graphicsdisplay.h"
#include "utils.h"
#include "grid.h"

using namespace std;

// constructor for graphics display
GraphicsDisplay::GraphicsDisplay(int width, int height) {
  this->display.resize(8);
  
  for (int i = 0; i < 4; ++i) {
        this->display.at(0).emplace_back('-');
        this->display.at(0).emplace_back(' ');
        this->display.at(2).emplace_back('-');
        this->display.at(2).emplace_back(' ');
        this->display.at(4).emplace_back('-');
        this->display.at(4).emplace_back(' ');
        this->display.at(6).emplace_back('-');
        this->display.at(6).emplace_back(' ');

        this->display.at(1).emplace_back(' ');
        this->display.at(1).emplace_back('-');
        this->display.at(3).emplace_back(' ');
        this->display.at(3).emplace_back('-');
        this->display.at(5).emplace_back(' ');
        this->display.at(5).emplace_back('-');
        this->display.at(7).emplace_back(' ');
        this->display.at(7).emplace_back('-');
    }
  this->emptyboard = this->display;

  d = XOpenDisplay(NULL);
  if (d == NULL) {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  Pixmap pix = XCreatePixmap(d,w,width,
        height,DefaultDepth(d,DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0,(XGCValues *)0);

  XFlush(d);
  XFlush(d);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[7][10]={"white", "gray", "red", "green", "blue"};

  cmap=DefaultColormap(d,DefaultScreen(d));
  for(int i=0; i < 5; ++i) {
      XParseColor(d,cmap,color_vals[i],&xcolour);
      XAllocColor(d,cmap,&xcolour);
      colours[i]=xcolour.pixel;
  }

  XSetForeground(d,gc,colours[Gray]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d,True);

  usleep(1000);
}

GraphicsDisplay::~GraphicsDisplay() {
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

void GraphicsDisplay::fillRectangle(int x, int y, int width, int height, int colour) {
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Gray]);
}

void GraphicsDisplay::drawString(int x, int y, string msg) {
  XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
}

void GraphicsDisplay::drawGrid(Grid& g) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      char tmp = this->emptyboard.at(i).at(j);
      if (tmp == '-') {
        this->fillRectangle(50 + 50 * i, 50 * j, 50, 50, 0);
      } else {
        this->fillRectangle(50 + 50 * i, 50 * j, 50, 50, 1);
      }
    }
  }

  // rows
  this->drawString(25, 25, "8");
  this->drawString(25, 75, "7");
  this->drawString(25, 125, "6");
  this->drawString(25, 175, "5");
  this->drawString(25, 225, "4");
  this->drawString(25, 275, "3");
  this->drawString(25, 325, "2");
  this->drawString(25, 375, "1");

  // columns
  this->drawString(75, 425, "a");
  this->drawString(125, 425, "b");
  this->drawString(175, 425, "c");
  this->drawString(225, 425, "d");
  this->drawString(275, 425, "e");
  this->drawString(325, 425, "f");
  this->drawString(375, 425, "g");
  this->drawString(425, 425, "h");

  // draw pieces
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      char temp = this->display.at(i).at(j);
      if (temp == '-' || temp == ' ') {
        continue;
      } else {
        this->drawString(73 + 50 * j, 28 + 50 * i, string(1,temp));
      }
    }
  }
}

void GraphicsDisplay::updateGrid(Grid& g) {
  for (int i = 0; i < 8; i++ ) {
    for (int j = 0; j < 8; j++) {
      char pieceChar = Utils::pieceToChar(g.getPiece(i, j));
      if (pieceChar == 'x') {
        this->display.at(i).at(j) = this->emptyboard.at(i).at(j);
      } else {
        this->display.at(i).at(j) = pieceChar;
      }
    }
  }
  this->drawGrid(g);
}

