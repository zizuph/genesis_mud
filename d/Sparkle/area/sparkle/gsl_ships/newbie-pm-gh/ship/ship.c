/* File:          /d/Khalakhor/ship/macdunn/sparkle/ship.c
 * Creator:       Teth
 * Date:          April 13, 1997
 * Modifications: Converted from the Khalakhor/Ansalon run.
 *                Khail - November 27, 97.
 * Purpose:       This is the Macdunn-Sparkle, or Khalakhor-Sparkle
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/sparkle/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 * Rerouted via PM-GH newbie line, Tapakah, 05/2009
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"
#include "../ship.h"

inherit NEWBIE_SHIP;

public void
create_ship()
{
  ::create_ship();
    seteuid(getuid());
    set_deck(({DECK, FORE}));
    set_name("longboat");
    add_name(SHIP_NAME);
    add_name("ship");
    add_name("boat");
    add_adj("sleek");
    add_adj("black");
    set_long("This sleek black ship is the Sgian Dubh, or " +
      "Black Knife, a ship running between the villages of " +
      "Port Macdunn and Sparkle. Three black, canvas sails " +
      "rise above her dark decks, her only apparent means " +
      "of motion. Built long and low, she looks not to be " +
      "built for heavy seas, but you doubt there are many " +
      "ships afloat that can outrun her.\n");
    add_item(({"sail","canvas sail"}),"The black sails " +
      "snap sharply in the wind, shining darkly in the " +
      "light.\n");
    add_item(({"deck","decks","dark decks"}),
      "The deck of the Sgian Dubh is made of the same " +
      "material as the rest of the ship, a solid wood, " +
      "probably oak, stained a dark black.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ GELAN_PIER, SPARKLE_PIER,
                   MACDUNN_PIER, GREY_HAVENS_PIER, }) );

}
