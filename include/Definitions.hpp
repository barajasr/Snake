#ifndef __DEFINITIONS_HPP__
#define __DEFINITIONS_HPP__

enum Direction{UP, DOWN, LEFT, RIGHT};
enum Tile{EMPTY, FOOD, HAZARD};

const unsigned BOARD_X = 61;
const unsigned BOARD_Y = 61;
const unsigned IMAGESIZE = 8;
const unsigned MARGIN = 10;
const unsigned SCORE_MARGIN = 30;
const unsigned WINDOW_X = BOARD_X * IMAGESIZE + BOARD_X + MARGIN - 1;
const unsigned WINDOW_Y = BOARD_Y * IMAGESIZE + BOARD_Y + MARGIN + SCORE_MARGIN - 1;

#endif
