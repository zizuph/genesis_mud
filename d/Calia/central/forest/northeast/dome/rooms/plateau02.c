// ROOM:  Dome - Southern plateau
//        DOME_ROOMS + plateau02

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        This is the southern end of the plateau upon which
        the pleasure dome resides. It has extensive gardens,
        filled with plants chosen for their delicious tastes
        or narcotic effects.

        AREA HISTORY
        This was always a garden area, but has been greatly
        expanded upon.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Plateau in the mountains");

    set_long("The path " +
        "orderly rows of vegetables and herbs. The plateau " +
        "ends east and south in sheer mountain walls, and " +
        "ends west in equally sheer cliffs.\n");

    /* ITEMS */

    add_item(({"mountain", "wall", "mountain wall", "mountains",
        "walls", "mountain walls"}), 
        "Sheer and formidable, the mountain walls to the " +
        "east and south are too smooth and steep to climb.\n");

    add_item(({"plateau", "ledge"}),
        "This a plateau, a clearing on a ledge in the side of " +
        "the mountains.\n");
 
    add_item(({"cliff", "cliffs"}), 
        "Sheer and formidable, the cliffs to the west are " +
        "too smooth and steep to climb.\n");
 
   /* TELLS */

     set_tell_time(80);

     add_tell("A chill mountain breeze blows against you.\n");
     add_tell("You hear a faint sound of falling rocks.\n");

    /* EXITS */

    add_exit("plateau01", "north", 0, 01);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 3);
    add_prop(ROOM_I_HIDE, 10);

    }
