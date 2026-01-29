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
        "The walls here are decorated with paintings. There is a "+
        "small window in one wall, letting light in. The floor here "+
        "is carpetted, and it is woven with intricate patterns. There "+
        "is the spiral staircase here, leading back down.\n");
    add_item("window","You see the back of a large building, and "+
        "the streets bellow.\n");
    add_item("paintings","Many are of serene sunsets and mountains.\n");
    add_item("carpet","It is made of fine wool.\n");
    add_exit(NOBLE(aemilius/m1),"down",0,-1,-1);
    add_exit(NOBLE(aemilius/m15),"west",0,-1,-1);
}

