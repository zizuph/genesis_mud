// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You are walking along the north corridor of the top "+
    "level of the castle. The red carpet beneath you muffles the "+
    "sound of your footsteps as you walk. The air here is hot, since "+
    "many windows line the west wall to let in sunshine. A large "+
    "mirror hangs on the east wall.\n");
    add_item(({"large mirror","mirror"}),"@@mirror@@");
    add_item("carpet","The red carpet is soft and warm.\n");
    add_item("windows","Through the windows, you can see the streets of "+
    "the noble district.\n");

    add_exit(NOBLE + "castle/c42", "east", 0, 0);
    add_exit(NOBLE + "castle/c40", "west", 0, 0);
}

string
mirror()
{
    string Pshort = TP->query_nonmet_name();

    if (TP->query_prop(LIVE_I_UNDEAD))
        return "You see the wall and windows behind you, as if "+
        "you weren't there.\n";
    else
        return "You see a "+Pshort+" smiling back at you.\n";
}

