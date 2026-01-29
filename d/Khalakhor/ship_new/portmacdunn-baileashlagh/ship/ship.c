/* File:          /d/Khalakhor/ship/macdunn/ashlagh/ship.c
 * Creator:       Zima (copied from Teth)
 * Date:          June 17, 1998
 * Modifications:
 * Purpose:       This is the Macdunn-Baile Ashlagh ship
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ashlagh/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */
 
#pragma save_binary
#pragma strict_types
 
#include "../ship.h"
#include <cmdparse.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h";

inherit STDSHIP;

public void
create_ship()
{
  ::create_ship();

  seteuid(getuid());
  set_cabin(CABIN);
  set_deck(DECK);
  set_name("boat");
  add_name(SHIP_NAME);
  add_name("ship");
  add_adj(({"tall-masted","wooden"}));
  set_short("tall-masted wooden ship");
  set_long("This sturdy wooden boat is named the "+SHIP_NAME+
           "and is famed for its great luck in sailing the south seas of "+
           "Khalakhor. The boat travels the route between Port MacDunn " +
           "and the village of Baile Ashlagh. The tall central mast with " +
           "huge sails is one of its most distinguishing characteristics.\n");
  add_item("mast",
           "The central mast of the ship is, well, massive. You wonder how "+
           "the ship doesn't topple over from its weight. Obviously designed "+
           "to withstand powerful winds, it rises high above the deck "+
           "laden with large sails.\n");
  add_item("sails",
           "The large white sails hanging from the mast seem to be made of "+
           "wool and are very voluminous. You imagine a heavy wind in "+
           "those sails on that mast could carry the ship very quickly "+
           "and safely.\n");

  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ MACDUNN_PIER, ASHLAGH_PIER }) );
}
