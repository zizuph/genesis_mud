/*********************************************************************
 * - ship.c                                                        - *
 * - shipline Gont-Kabal                                           - *
 * - Recoded by Damaris 5/2003                                     - *
 * - Ported to Newbie Gont-Kabal Line by Tapakah, 05/2009          - *
 *********************************************************************/
 
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
  set_cabin(CABIN);
  set_deck(DECK);
  set_name("boat");
  add_name(SHIP_NAME);
  add_name("ship");
  add_adj(({"enormous","wooden"}));
  set_short("enormous wooden ship");
  set_long("This enormous wooden ship is named the "+SHIP_NAME+ " "+
           "and by it's size it must be a galleon.\n");
  add_item("mast",
           "The central mast of the ship is massive. You wonder how "+
           "the ship doesn't topple over from its weight. Obviously designed "+
           "to with stand powerful winds, it rises high above the deck "+
           "laden with large sails.\n");
  add_item("sails",
           "The large white sails hanging from the mast seem to be made of "+
           "wool and are very voluminous. You imagine a heavy wind in "+
           "those sails on that mast could carry the ship very quickly "+
           "and safely.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ SPARKLE_PIER, GELAN_PIER,
                   GONT_PIER, KABAL_PIER, }) );
  
}
 
