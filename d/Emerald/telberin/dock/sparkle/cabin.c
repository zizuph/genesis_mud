/*
 *  /d/Emerald/telberin/dock/sparkle/cabin.c
 *
 *  This is the cabin of the ship which transports players from Emerald
 *  to Sparkle.
 *
 *  Created August 2007, by Cooper Sherry (Gorboth)
 * Ported to the new ship system, Tapakah 10/2008
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"
inherit STDSHIPROOM;


/*
 * Function name:        create_cabin
 * Description  :        set up the cabin
 */
public void
create_room()
{
	::create_shiproom();
    set_short("within the cabin of a strange gleaming vessel");
    set_long("Comfortable seats have been placed around the cabin"
      + " of this vessel so that passengers may ride out the"
      + " occasional storm that might interrupt the normal passage"
      + " between ports.\n");

    add_item( ({ "cabin", "area", "here" }), long);
    add_item( ({ "ship", "vessel", "strange vessel", "gleaming vessel",
                 "strange gleaming vessel" }),
        "From here in the cabin it is difficult to see the ship"
      + " itself.\n");
    add_item( ({ "illumination", "light", "glow", "gleam" }),
        "Light is everywhere in this ship, seeming to come from the"
      + " materials from which it was constructed.\n");
    add_item( ({ "sky", "up", "ceiling" }),
        "Above you is the ceiling of the cabin.\n");
    add_item( ({ "down", "floor", "ground" }),
        "The floor of the cabin is just as bright as everything"
      + " else in this vessel.\n");
    add_item( ({ "seat", "chair", "seats", "comfortable seat",
                 "comfortable seats" }),
        "Seats have been arranged for passengers to rest upon during"
      + " the passage of these waters.\n");

    add_cmd_item( ({ "seat", "seats", "comfortable seats", "chair",
                     "chairs" }), ({ "sit", "recline" }),
        "You sit down on one of the seats, reclining in the comfortable"
      + " areas of the cabin. Presently, you rise again as the ship"
      + " prepares to move on.\n");

    add_prop(ROOM_I_HIDE, 10); /* easy to hide with all the cargo here */

    set_cabin_sound("You feel the vessel moving onward.\n");
    set_bump_sound("With a sudden bump, the vessel comes to a halt.\n");

    add_exit("deck", "fore");
} /* create_cabin */

