#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#define KOGRE  KNPC + "ogre"

inherit KOGRE;

void
set_colour(string c)
{
    set_color(c);
}

varargs
void arm_me(int lvl)
{
    if (lvl)
        ::arm_me(lvl);
}
