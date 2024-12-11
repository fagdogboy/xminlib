#pragma once

#define MARGIN_X 3
#define MARGIN_Y 3

#include <thread>
#include <X11/Xlib.h>
#include <unistd.h> 
#include <stdio.h>  
#include <iostream>
#include <cmath>
#include <chrono>
#include <vector>

struct layout_struct;

void draw_box(Display* display, Window window, GC gc, unsigned int anchor_x, unsigned int anchor_y, unsigned int size_x, unsigned int size_y) {

  XDrawLine(display, window, gc, anchor_x, anchor_y, anchor_x+size_x, anchor_y);
  XDrawLine(display, window, gc, anchor_x+size_x, anchor_y, anchor_x+size_x, anchor_y+size_y);
  XDrawLine(display, window, gc, anchor_x+size_x, anchor_y+size_y, anchor_x, anchor_y+size_y);
  XDrawLine(display, window, gc, anchor_x, anchor_y+size_y, anchor_x, anchor_y);

  return;
}

void draw_dynamic_box_with_text(Display* display, Window window, GC gc, unsigned int id , XFontStruct* font, unsigned int anchor_x, unsigned int anchor_y, unsigned int *size_x, unsigned int *size_y, std::string label) {

  std::string todraw = label;
  
  int font_height = font->ascent + font->descent;
  int font_ascent = font->ascent; 
  int font_descent = font->descent;
  int max_width = font->max_bounds.width;
  
  int total_text_width = (max_width * todraw.length()) + 2*MARGIN_X;
  int total_text_height = (font_height);

  *size_x = total_text_width;
  *size_y = total_text_height;

  XDrawLine(display, window, gc, anchor_x, anchor_y, anchor_x+total_text_width, anchor_y);
  XDrawLine(display, window, gc, anchor_x+total_text_width, anchor_y, anchor_x+total_text_width, anchor_y+total_text_height);
  XDrawLine(display, window, gc, anchor_x+total_text_width, anchor_y+total_text_height, anchor_x, anchor_y+total_text_height);
  XDrawLine(display, window, gc, anchor_x, anchor_y+total_text_height, anchor_x, anchor_y);
  
  XDrawString(display, window, gc, anchor_x+MARGIN_X, anchor_y+total_text_height-MARGIN_Y+1, todraw.c_str() , todraw.length() );

  XFlush(display);
  
  return;
}

void draw_dynamic_text(Display* display, Window window, GC gc, unsigned int id , XFontStruct* font, unsigned int anchor_x, unsigned int anchor_y, unsigned int *size_x, unsigned int *size_y, std::string label) {

  std::string todraw = label;
  
  int font_height = font->ascent + font->descent;
  int font_ascent = font->ascent; 
  int font_descent = font->descent;
  int max_width = font->max_bounds.width;
  
  int total_text_width = (max_width * todraw.length()) + 2*MARGIN_X;
  int total_text_height = (font_height);

  *size_x = total_text_width;
  *size_y = total_text_height;

  XDrawString(display, window, gc, anchor_x+MARGIN_X, anchor_y+total_text_height-MARGIN_Y+1, todraw.c_str() , todraw.length() );

  XFlush(display);
  
  return;
}

void draw_dynamic_underlined_text(Display* display, Window window, GC gc, unsigned int id , XFontStruct* font, unsigned int anchor_x, unsigned int anchor_y, unsigned int *size_x, unsigned int *size_y, std::string label) {

  std::string todraw = label;
  
  int font_height = font->ascent + font->descent;
  int font_ascent = font->ascent; 
  int font_descent = font->descent;
  int max_width = font->max_bounds.width;
  
  int total_text_width = (max_width * todraw.length()) + 2*MARGIN_X;
  int total_text_height = (font_height);

  *size_x = total_text_width;
  *size_y = total_text_height;

  XDrawLine(display, window, gc, anchor_x+total_text_width, anchor_y+total_text_height, anchor_x, anchor_y+total_text_height);
  
  XDrawString(display, window, gc, anchor_x+MARGIN_X, anchor_y+total_text_height-MARGIN_Y+1, todraw.c_str() , todraw.length() );

  XFlush(display);
  
  return;
}

void draw_dynamic_window_border(Display* display, Window window, GC gc, unsigned int width) {
  
  XWindowAttributes window_attributes;

  if (XGetWindowAttributes(display, window, &window_attributes)) {

    std::cout << window_attributes.width << " - width | " << window_attributes.height << " - height " << std::endl;

    for(int i = 0; i<width; ++i) {

      draw_box(display,window,gc,0+i,0+i,window_attributes.width-(i*2)-1, window_attributes.height-(i*2)-1);
   
    }
    
  } else {

    std::cout << "Failed  to get window info." << std::endl;

  }

  return;

}
