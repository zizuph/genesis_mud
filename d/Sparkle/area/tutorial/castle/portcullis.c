/*
 *  /d/Sparkle/area/tutorial/castle/portcullis.c
 *
 *  This is the entrance to the castle of Baron von Krolock. Guards
 *  must be killed to pass.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

#include <stdproperties.h>

/* Prototypes */
public void        create_castle_room();
public void        reset_room();


/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("beneath a portcullis at the castle entrance");
    set_long("You stand beneath a great archway that leads into the"
      + " castle. Above your head, the sharp iron points of the"
      + " portcullis protrude from beneath the narrow slot in the"
      + " masonry that houses its framework. West, a wide corridor"
      + " extends into the castle beyond this narrow point at the"
      + " entrance. East, a plateau of rock extends towards the"
      + " cliffs.\n\n");

    add_item( ({ "portcullis", "point", "sharp point", "iron point",
                 "sharp points", "iron points", "slot", "points",
                 "narrow slot" }),
        "The portcullis is currently retracted into the masonry"
      + " of the archway, where it is housed within a narrow slot.\n");
    add_item( ({ "castle", "masonry", "stone", "stone slabs", "slab",
                 "slabs" }),
        "The castle is built of heavy stone slabs which frown down on"
      + " you from above.\n");
    add_item( ({ "entrance", "arch", "archway", "great archway",
                 "narrow point", "here" }),
        "The archway towers above you here, controlling access to the"
      + " inside of the castle via a narrow entrance.\n");
    add_item( ({ "corridor", "wide corridor", "west" }),
        "Beyond this entrance, a corridor travels into the castle to"
      + " the west.\n");
    add_item( ({ "east", "plateau", "rock", "plateau of rock",
                 "cliff", "cliffs" }),
        "Travelling east would take you out onto the plateau, outside"
      + " the castle toward the cliffs.\n");

    add_prop(ROOM_I_INSIDE, 0); /* we're not in the castle yet */
    add_outdoor_items();

    add_exit("entrance", "west", check_exit, 1, 0);
    add_exit("plateau", "east");

    set_trigger_room();
    reset_room();
} /* create_castle_room */


/*
 * Function name:        reset_room
 * Description  :        clone npcs and tutorial signs as needed
 */
public void
reset_room()
{
    clone_guard(1);
} /* reset_room */

