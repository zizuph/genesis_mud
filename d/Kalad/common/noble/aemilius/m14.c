inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("A long hall in the House of Aemilius");
    INSIDE;
    set_long("You find yourself at the end of a long hall. "+
    "The hall contines to the west, while directly to your "+
    "northwest, you see a intersection. There is a stairscase "+
    "here leading back down. A window is off to the south, letting "+
    "in light. The floor is carpeted.\n");
    add_item("window","You see the streets below.\n");
    add_item("carpet","It is made of fine wool.\n");
    add_exit(NOBLE(aemilius/m1),"down",0,-1,-1);
    add_exit(NOBLE(aemilius/m17),"west",0,-1,-1);
}

