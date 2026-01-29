#include "defs.h"

inherit STDROOM;

string extra;

public void
create_tower()
{
    set_short("in the collapsed ruins of a tower");
    set_long("You are in the collapsed ruins of a " +
        "tower in the northern parts of the ruins " +
        "of "+CASTLE_NAME+". The tower has collapsed " +
        "and fallen over towards the north, making " +
        "progress rather difficult in the " +
        "rubble-strewn interior. There's a large " +
        "amount of stone that has fallen away from " +
        "the walls, including the remains of what " +
        "might have once been wooden floors in this " +
        "long ruin. Now, however, they serve only as " +
        "obstacles, making the space in here very " +
        "tight, leaving room only to crawl around and " +
        "not much else. " +
        (stringp(extra) ? extra : "") +
        "\n\n");

    add_item(({"ceiling", "roof"}),
        "The 'roof' of this tower is actually its wall, " +
        "it's a little confusing with it lying on its " +
        "side like this.\n");
    add_item(({"walls"}),
        "The circular walls of the tower now serve to " +
        "also form the ceiling, now that it's fallen " +
        "on its side. A lot of the stone that was part " +
        "of the walls collapsed inwards when it fell over, " +
        "it seems, choking the center of the tower with " +
        "rubble that makes it almost impossible to move " +
        "around.\n");
    add_item(({"floor", "ground"}),
        "At the moment, the floor of the tower is comprised " +
        "of a great deal of rubble fallen from the walls, " +
        "which now fills the center of the ruined structure " +
        "almost entirely, making movement slow and arduous.\n");
    add_item(({"rubble", "remains"}),
        "The tower is filled almost entirely with tangled, " +
        "jagged heaps of broken stone and wood. None of it " +
        "is any good now, except in slowing you down.\n");    

    INSIDE;
    DARK;
    add_prop(ROOM_M_NO_ATTACK, "There's barely enough " +
        "room in here to move, let alone fight.\n");
}