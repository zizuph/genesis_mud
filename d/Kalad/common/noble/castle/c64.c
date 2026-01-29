// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("Toilet room");
    INSIDE;
    set_long("This is the toilet room. There is a stone chair against "+
        "one wall, with a dark hole in it. The source of the foul smell "+
        "seeems to be coming from it. On the ground, there is a towel. A "+
        "picture hangs from the south wall.\n");
    add_item("towel","It is a white towel with dark brown spots on it.\n");
    add_item("picture","A picture of a giant, fat face. It is smiling "+
        "at you.\n");
    add_item("hole","You see nothing but darkness. But you can sure "+
        "smell a whole lot more than that.\n");

    add_exit(NOBLE + "castle/c65", "east", 0, 0);
}


