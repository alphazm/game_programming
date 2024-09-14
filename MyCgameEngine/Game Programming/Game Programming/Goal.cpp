#include "Goal.h"

Goal::Goal()
{
    rect.top = 10;
    rect.bottom = 10;
    rect.right = 180;
    rect.left = 180;
}

RECT* Goal::GetRect()
{
    return &rect;
}
