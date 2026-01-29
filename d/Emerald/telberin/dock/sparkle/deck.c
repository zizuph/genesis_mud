/*
 *  /d/Emerald/telberin/dock/sparkle/deck.c
 *
 *  This is the deck of the ship which transports players from Emerald
 *  to Sparkle.
 *
 *  Created August 2007, by Cooper Sherry (Gorboth)
 * Ported to the new ship system by Tapakah, 10/2008
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDSHIPROOM;


/*
 * Function name:        create_room
 * Description  :        set up the deck
 */
public void
create_room()
{
	::create_shiproom();
    set_short("on the deck of a strange gleaming vessel");
    set_long("The deck of this vessel is extremely spacious due to the"
      + " (unusual) fact that there are no masts present. In fact, one"
      + " has to wonder how such a ship would be propelled through the"
      + " water without using the power of air. Also rather strange is"
      + " the bright illumination that is present here. Every surface"
      + " glows with its own inner light.\n");

    add_item( ({ "deck", "area", "here" }), long);
    add_item( ({ "ship", "vessel", "strange vessel", "gleaming vessel",
                 "strange gleaming vessel" }),
        "Unlike the standard sailing ships which operate"
      + " throughout the realms of Genesis, this ship boasts no"
      + " visible masts or sails of any kind. Rather, it is comprised"
      + " of a grand hull glowing with an illumination all its own"
      + " which rises majestically out of the water.\n");
    add_item( ({ "mast", "masts" }),
        "How strange ... the glowing vessel has no masts of any kind!\n");
    add_item( ({ "sail", "sails" }),
        "No sails are visible upon the vessel. One wonders how such a"
      + " ship would move through the water.\n");
    add_item( ({ "hull", "grand hull" }),
        "The hull of the vessel is similar to what one would expect to"
      + " see on a sizeable ship of its kind. The absence of masts and"
      + " sails does, however, cause the hull to take on a bit of an"
      + " unusual quality.\n");
    add_item( ({ "illumination", "light", "glow", "gleam" }),
        "The ship gleams with an illumination that seems to be emenating"
      + " from the very material which comprises the hull.\n");
    add_item( ({ "light", "enchantment", "concentration of light",
                 "unusual light", "unusual concentration of light",
                 "prow", "prow of the ferry", "prow of the ship",
                 "front of the ship", "front of the ferry" }),
        "The prow of this vessel is unusually illuminated, and the glow"
      + " grows stronger the faster the ship moves forward. Perhaps this"
      + " is some form of enchantment used in propelling the ship"
      + " to its destination.\n");
    add_item( ({ "sky", "up" }),
        "The sky is clear and blue above you.\n");

    add_prop(ROOM_I_HIDE, 10); /* easy to hide with all the cargo here */

    set_deck_sound("The prow gleams with brilliant illumination as"
      + " the vessel speeds onward through the water.\n");
    set_bump_sound("The prow of the ship glows dully as the ship bumps"
      + " up against the pier.\n");

    add_exit("cabin", "aft");
} /* create_deck */

