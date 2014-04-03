//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height and width of paddle
#define BHEIGHT 10
#define BWIDTH 60

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // check for mouse movement
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        // if there is an event
        if(event != NULL)
        {
            // if event is movement
            if(getEventType(event) == MOUSE_MOVED)
            {
                // move paddle along x axis with cursor
                double x = getX(event) - getWidth(paddle) / 2;
                double y = getY(paddle);
                setLocation(paddle, x, y);
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // generate table of bricks with colored rows

    double row = (getHeight(window) / 11); // row y starting coordinate
    
    for(int i = 0; i < 5; i++)
    {
        char *color[] = {
        "RED",
        "ORANGE",
        "YELLOW",
        "GREEN",
        "BLUE"
        };
        double width = (getWidth(window) - (11 * 4)) / 10; // brick width
        double height = 10; // brick height
        double gapX = 4;    // horizontal gap x starting coordinate
        double gapY = 4;    // vertical gap y staring coordinate

        
        for(int j = 0; j < 10; j++)
        {
            GRect brick = newGRect(gapX, row, width, height);
            gapX = (getX(brick) + width + 4);
            setFilled(brick, true);
            setColor(brick, color[i]);
            add(window, brick);
        }
        row = row + height + gapY;
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // instantiate ball
    GOval ball = newGOval(0, 0, 20, 20);
    add(window, ball);
    setFilled(ball, true);
    setColor(ball, "Black");
    
    // set location to center
    double x = ((getWidth(window) - getWidth(ball)) / 2);
    double y = ((getHeight(window) - getHeight(ball)) / 2);
    setLocation(ball, x, y);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Instantiate paddle.gi
    GRect paddle = newGRect(0, 0, BWIDTH, BHEIGHT);
    setFilled(paddle, true);
    setColor(paddle, "BLACK");
    add(window, paddle);
    
    // Set paddle location to bottom center
    double x = (getWidth(window) - getWidth(paddle)) / 2;
    double y = (getHeight(window)) - ((getHeight(window) - getHeight(paddle)) / 10);
    setLocation(paddle, x, y);
    
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
