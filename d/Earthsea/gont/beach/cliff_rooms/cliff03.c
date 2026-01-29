/*
 * Cliff on Gont beach
 * By Finwe
 * May 1997
 */

#pragma strict_types
#pragma no_clone

#include "default.h"
#include <macros.h>
#include <stdproperties.h>

inherit CLIFFS_ROOM;

public void
create_cliffs()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("The side of a cliff");
    set_long( "You stand on a path that runs through the " +
      "cliffs. The rock is off white with streaks of gray " +
      "and black running through it. Over the years, the " +
      "constant wind has carved niches into the side of the " +
      "cliff. The salt air has eaten holes into the rock. Up " +
      "above, the holes are occupied by birds but down here, " +
      "most are filled with debris and dirt. A gentle spring " +
      "of water bubbles out of one hole. The excess water runs " +
      "down the path and over the side of the cliff. Someone has " +
      "cut some stairs into the cliff here.\n");

    add_item(({"water", "spring"}),
      "The water bubbles up out of a cleft in the cliffs. It is "+
      "crystal clear and clean despite all the debris nearby.\n");

    add_exit("cliff01", "northwest");
    add_exit("cliff04", "southwest");
    add_exit("cliff02", "down");

    add_prop(OBJ_I_CONTAIN_WATER, -1);
}

public int
drink_it(string str)
{
    object tp = this_player();

    if(!str || (str != "water" && str != "from spring" &&
        str != "water from spring"))
    {
        return 0;
    }

    if(tp->drink_soft(tp->drink_max() / 16, 0))
    {
        write("You kneel before the spring, cupping your hands, and take " +
              "a big drink of water. You feel refreshed as you stand up.\n");
        say(QCTNAME(tp)+" kneels down and gets a drink from the spring.\n");
        return 1;
    }

    write("You aren't thirsty at the moment.\n");
    return 1;
}

public void
init()    
{
    ::init();
    add_action(drink_it,  "drink");
}
