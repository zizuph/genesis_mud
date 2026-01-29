// ROOM:  base_border.c

    /*  Calia Domain

    HISTORY

    [99-06-09] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\OUTER\GROUND\BASE_BOR.DOC].

    PURPOSE

    This is the base for ground-level rooms between the bog and the hill
    surrounding the Sanctimonian fortress.  In general, there should be a
    one-room wide border between an area built from hill rooms and one built
    from bog rooms.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/bog/baseroom";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

// FUNCTIONS

// Function:  enter_inv(object, from_object)

/*

Purpose:  register a player (or foreign npc) with the Sanctimonian control
room.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

    {

    ::enter_inv(ob, from);

    if (living(ob) && !ob->sanctimonian()) register_player(ob);

    }

// Function:  create_border(direction, *adjacent_rooms)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  string containing the compass direction to the fortress, string
array of adjacent room filenames.

Returns:  nothing.

*/

void
create_border(string direction, string *adjacent_rooms)

    {

    set_short("In a dense forest near a bog");

    set_long("The ground here rises to the " + direction +
        ", and through the trees in that direction you can see" +
        " an open, sunlit field. In the opposite direction lies a" +
        " dark bog, and its mist and dampness permeate" +
        " this area, wafting and swirling uphill" +
        " toward the sunlight.\n" +
        "There are obvious exits in every direction.\n");

    add_item(({"bog", "dark bog"}),
        "You can see little of the bog from here. The thick mist" +
        " and the shadow cast by the trees conceal all detail.\n");

    add_item(({"mist", "thick mist"}),
        "At one moment the mist crawls along between the trees" +
        " and slithers up the hill like a living thing, and at" +
        " the next it seethes and swells like a sea in" +
        " storm. Every motion seems intended to obsure your view" +
        " of what lies in the bog.\n");

    add_item(({"trees", "slender trees", "branches", "twisted branches",
        "tree", "slender tree", "branch", "twisted branch"}),
        "The trees here are all quite slender and covered" +
        " with twisted branches that entangle and knit the treetops" +
        " ito a solid canopy of leaves. They grow so closely" +
        " together that they leave little room for you to" +
        " travel between them. As far as you can see into the" +
        " bog the trees continue without interruption, but they" +
        " thin out toward the " + direction + ".\n");

    add_item(({"canopy", "solid canopy", "broad leaves", "leaves",
        "broad leaf", "leaf", "treetops"}),
        "The broad leaves grow thickly on the twisted branches" +
        " just over your head, and they form a solid canopy" +
        " that blocks all light from above.\n");

    add_item(({"ground", "hill", "field", "sunlit field", "sunlight"}),
        "You can discern a green, sunlit field" +
        " to the "  + direction + ", but the trees grow too densely" +
        " for you to observe anything more in that direction.\n");

    /*  EXITS  */

    /*  A border room must always have exits in all directions.  */

    set_noshow_obvious(1);

    add_exit(adjacent_rooms[0], "north", 0, 1);
    add_exit(adjacent_rooms[1], "northeast", 0, 1);
    add_exit(adjacent_rooms[2], "east", 0, 1);
    add_exit(adjacent_rooms[3], "southeast", 0, 1);
    add_exit(adjacent_rooms[4], "south", 0, 1);
    add_exit(adjacent_rooms[5], "southwest", 0, 1);
    add_exit(adjacent_rooms[6], "west", 0, 1);
    add_exit(adjacent_rooms[7], "northwest", 0, 1);

    /*  PROPERTIES  */

    add_prop(ROOM_I_HIDE, 80);  /*  Pretty good hiding place. */
    add_prop(ROOM_I_LIGHT, 2);  /*  Indirect sunlight. */

    /*  "uid" settings required for cloning objects.  */

    setuid();
    seteuid(getuid());

    /*  SPECIAL FUNCTION  */

    /*  Tell the Sanctimonian central control room that this room has been
        loaded.  Function is found in /d/Calia/central/bog/baseroom.c.  */

    register_room();

    }
