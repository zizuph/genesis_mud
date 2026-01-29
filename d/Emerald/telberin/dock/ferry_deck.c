/*
 *  /d/Emerald/telberin/dock/ferry_deck.c
 *
 *  This is the deck of the ferry which transports players to the
 *  north shore of the lake from the city of Telberin.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>


/*
 * Function name:        create_deck
 * Description  :        set up the deck
 */
public void
create_deck()
{
    set_short("on the deck of a long flat ferry");
    set_long("The deck of this ferry is long and flat. The many crates and"
      + " barrels which occupy the floorspace hint at the purpose this"
      + " vessel must serve, namely to resupply the troops garrisoned upon"
      + " the north shore of Lake Telberin. There is no visible mast or sail,"
      + " though you do detect an unusual concentration of light toward the"
      + " prow of the ferry, which may be some kind of magical enchantment.\n");

    add_item( ({ "deck", "area", "here" }), long);
    add_item( ({ "ship", "ferry", "ferryboard", "vessel",
                 "sailing ship", "sailing vessel", "boat" }),
        "This sailing vessel is much smaller than most you have"
      + " seen. It more closely resembles a barge than a sailing ship,"
      + " and appears suited to transport both cargo and passengers"
      + " on a single deck.\n");
    add_item( ({ "crate", "crates", "barrel", "barrels", "crates and barrels",
                 "barrels and crates", "supplies", "cargo" }),
        "The floor of the deck is crowded with various supplies which have been"
      + " loaded into barrels and crates.\n");
    add_item( ({ "floor", "down", "floorspace", "floor space", "ground" }),
        "The floor of the deck is long and flat, able to support many people"
      + " and many items of cargo.\n");
    add_item( ({ "mast", "sail" }),
        "Oddly, this ferry has no obvious means of propulsion. Perhaps some"
      + " kind of magic is involved.\n");
    add_item( ({ "light", "enchantment", "concentration of light",
                 "unusual light", "unusual concentration of light",
                 "prow", "prow of the ferry", "prow of the ship",
                 "front of the ship", "front of the ferry" }),
        "The prow of this vessel is unusually illuminated, and the glow"
      + " grows stronger the faster the ship moves forward. Perhaps this"
      + " is some form of enchantment used in propelling the ferry"
      + " to its destination.\n");
    add_item( ({ "lake", "water", "lake telberin", "telberin lake" }),
        "Lake Telberin spreads out before this ferry, its choppy surface"
      + " a clear blue field to the edges of your vision.\n");
    add_item( ({ "sky", "up" }),
        "The sky is clear and blue above you.\n");

    add_prop(ROOM_I_HIDE, 10); /* easy to hide with all the cargo here */

    set_deck_sound("The prow gleams with brilliant illumination as"
      + " the ferry speeds onward through the water.\n");
    set_bump_sound("The prow of the ship glows dully as the ship bumps"
      + " up against the pier.\n");
} /* create_deck */

