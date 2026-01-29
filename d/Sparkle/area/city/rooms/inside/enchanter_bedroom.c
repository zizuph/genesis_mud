/*
 *  /d/Sparkle/area/city/rooms/inside/enchanter_bedroom.c
 *
 *  These are the personal bed chambers of Karkadelt the Enchanter.
 *
 *  Created February 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "../../defs.h"


/* Prototypes */
public void        create_room();


/*
 * Function name:        create_room
 * Description  :        the room constructor
 */
public void
create_room()
{
    set_short("in a small bedchamber");
    set_long("This is a small and humble bedchamber. Resting against"
      + " the far wall is a simple looking bed. A dresser beside it is"
      + " the only other thing in the room. A door exits the room to"
      + " the east.\n\n");

    add_item( ({ "chamber", "bedchamber", "small bedchamber",
                 "humble bedchamber", "small and humble bedchamber",
                 "room", "here", "area" }),
        "It would appear as if very little takes place in this room other"
      + " than sleeping.\n");
    add_item( ({ "bed", "simple bed", "simple looking bed" }),
        "It looks cozy enough, if a bit narrow.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "The ceiling is rather low in this room.\n");
    add_item( ({ "ground", "down", "floor" }),
        "The floor has been neatly swept.\n");
    add_item( ({ "door", "doorway", "exit", "east" }),
        "The door to the east leads out of the room.\n");
    add_item( ({ "wall", "walls" }),
        "The walls here are unadorned.\n");
    add_item( ({ "far wall" }),
        "The bed is positioned against the far wall.\n");

    add_cmd_item( ({ "bed", "on bed", "on the bed",
                     "down on the bed" }),
                  ({ "rest", "sleep", "lie", "lay", "sit" }),
        "You stretch out on the bed for a bit. After a few minutes you"
      + " decide it is probably best to move on.\n");

    add_cmd_item( ({ "dresser" }),
                  ({ "search" }),
        "As you move to inspect the dresser, a strange force grabs hold"
      + " of you, and freezes your movements. It must be enchanted"
      + " somehow. You do notice a diary resting on its top, though.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");

    add_exit("/d/Genesis/imbuement/enchanter_forge", "east");

    room_add_object("/d/Sparkle/area/orc_temple/obj/enchanter_journal");
} /* create_room */
