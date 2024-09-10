#include "Goal.h"

Goal::Goal(int top, int bottom, int left, int right)
{
    rect.top = top;
    rect.bottom = bottom;
    rect.right = right;
    rect.left = left;
}

RECT* Goal::GetRect()
{
    return &rect;
}
