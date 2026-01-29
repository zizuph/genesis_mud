/* File:          /d/Khalakhor/ship/macdunn/sparkle/deck.c
 * Creator:       Teth
 * Date:          April 12, 1997
 * Modifications: Converted over to a ship to sparkle.
 *                Khail - November 27, 97.
 * Purpose:       The deck is a room on the Khalakhor to
 *                Sparkle ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/sparkle/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/sparkle/box.c
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

object box;

public void
create_room()
{
   ::create_shiproom();
   set_short("on the deck of the Sgian Dubh");
    set_long("   You are standing on the deck of the " +
      "long ship Sgian Dubh, or Black Knife. The " +
      "ship is long and sleek, with three black canvas " +
      "sails stretched taut above you. The entire " +
      "ship is stained black, and drifts easily " +
      "on the low waves.\n");

    add_item(({"deck","area"}),"@@query_long");
    add_item(({"ship","boat","sgain dubh","vessel"}),"It is " +
      "the boat you are sailing on, and it ferries passengers " +
      "between Sparkle and Port Macdunn.\n");
    add_item(({"sail","sails","canvas sails","black canvas sails",
        "black sails"}),"Three black canvas sails stretch tight in " +
      "the air above your head atop tall black masts.\n");
    add_item("canvas","A sturdy material used in mast-making.\n");
    add_item(({"masts","black masts","tall masts","tall black masts"}),
      "Tall, smooth and as black as coal, the masts look like spikes " +
      "of darkness punching through the air above the ship's deck.\n");
    add_cmd_item(({"the masts","the black masts","tall masts",
        "tall black masts","up the masts","up the black masts",
        "up the tall black masts","up"}),({"climb","scale"}),
      "You attempt to climb the masts, but find the effort futile " +
      "as there is nothing to aid your climbing ability.\n");
    add_item(({"stain","black stain"}),"The black stain used on the " +
      "boat is a concoction of charcoal and oil.\n");

    add_exit(FORE, "fore", 0);

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SHIPDECK);

    set_deck_sound(sounds());
    set_is_deck(1);

    box = clone_object(BOX);
    box->move(this_object(), 1);
}

public string
sounds()
{
    if(random(2))
        return "The slim longship cuts effortlessly " +
        "through the seas.\n";

    return "The ship glides smoothly along the waves.\n";
}

