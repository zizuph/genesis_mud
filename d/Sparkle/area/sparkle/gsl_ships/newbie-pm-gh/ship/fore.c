/* File:          /d/Khalakhor/ship/macdunn/sparkle/fore.c
 * Creator:       Teth
 * Date:          April 2, 1997
 * Modifications: Teth - added terrain types, Sept 7 1997
 *                Khail - converted into ship to sparkle,
 *                        November 28, 97.
 *                Teth - December 4, 1997, added more add_item()s
 * Purpose:       The fore is a room on the Khalakhor to
 *                Sparkle ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/sparkle/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit STDSHIPROOM;
public string sounds();

public void
create_room()
{
  ::create_shiproom();
    set_short("on the fore deck of the Sgian Dubh");
    set_long("   You are on the fore deck of the Sgian Dubh, " +
      "where the decking narrows into a sharp point " +
      "at the ship's prow. Three black masts stand " +
      "tall on the deck of the ship, supporting black " +
      "canvas sails. The ship's wood is stained black, " +
      "giving the boat a gloomy atmosphere.\n");
    add_item(({"deck","fore deck"}),"@@query_long");
    add_item(({"prow","ship's prow"}),"The sailing front of the " +
      "ship, on the Sgian Dubh it narrows to a sharp point, " +
      "giving the ship its dagger shape.\n");
    add_item(({"black masts","masts","three masts","tall masts",
      "tall black masts","three black masts"}),"The three masts " +
      "rising from the deck of the ship are black needles " +
      "puncturing a sky-blue quilt.\n");
    add_item(({"black canvas sails","sails","canvas sails",
        "black sails"}),"The black canvas sails remain permanently " +
      "taut.\n");
    add_item("mast","Each mast looks no different than the other.\n");
    add_item("sail","Each sail looks no different than the other.\n");
    add_item(({"ship","boat","sgain dubh"}),"The boat that you are " +
      "standing on, it ferries passengers between Sparkle and " +
      "Port Macdunn.\n");
    add_item(({"wood","ship's wood"}),"The wood is a dark Scotch pine.\n");
    add_item(({"pine","scotch pine"}),"A straight-grained wood, it " +
      "is used where detail and accuracy are important.\n");
    add_item(({"stain","black stain"}),"The black stain is a concoction " +
      "of charcoal and oil.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SHIPDECK);

    add_exit(DECK, "aft", 0);

    set_deck_sound(sounds());
    set_is_deck(1);
}

public string
sounds()
{
    if (random(2))
        return "Sea water splashes onto the deck of the ship as the boat " +
        "slices through a high wave.\n";

    return "The Sgian Dubh pitches sharply against the wind.\n";
}

