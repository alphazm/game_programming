#include "Goal.h"

Goal::Goal()
{
    rect.top = 10;
    rect.bottom = 10;
    rect.right = 80;
    rect.left = 80;
}

RECT* Goal::GetRect()
{
    return &rect;
}
