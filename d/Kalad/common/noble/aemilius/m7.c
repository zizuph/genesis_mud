inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("A short hall");
    INSIDE;
    set_long("You now stand in a short hall. There is a table "+
    "in one corner, with a small statue on it. Above, a large "+
    "lantern hangs, casting light around. To the northwest, you smell "+
    "cooking food, while the sounds of dining come from the north.\n");
    add_item("table","A strong wooden table. A statue is on top of it.\n");
    add_item("statue","The statue is of a large head. The head is "+
    "not that impressive. It is carved out of white stone. On the bottom, "+
    "you see the inscription: Lord Aemilius I.\n");
    add_item("lantern","The lantern casts soft light.\n");
    add_exit(NOBLE(aemilius/m1),"east",0,-1,-1);
    add_exit(NOBLE(aemilius/m6),"north",0,-1,-1);
    add_exit(NOBLE(aemilius/m11),"northwest",0,-1,-1);
    add_exit(NOBLE(aemilius/m10),"west",0,-1,-1);
}

