/**********************************************************************
 * - ship.c                                                         - *
 * -                                                                - *
 * - Created by Damaris@Genesis 02/2001                             - *
 * - Updated by Damaris@Genesis 03/2005                             - *
 * - Ported by Tapakah to new ship system 04/2009                   - *
 **********************************************************************/

#pragma save_binary
#pragma strict_types
 
#include "../ship.h"
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
	add_adj(({"sturdy","wooden"}));
	set_short("sturdy wooden ship");
	set_long("This sturdy wooden ship is named the "+SHIP_NAME+
        "and is famed for its great luck in sailing the south seas of "+
        "Khalakhor. The ship travels the route between Port MacDunn " +
        "and the village of SaMorgan.\n");
  add_item("mast",
           "The central mast of the ship is massive. You wonder how "+
           "the ship doesn't topple over from its weight. Obviously "+
           "designed to withstand powerful winds, it rises high above "+
           "the deck laden with large sails.\n");
  add_item("sails",
           "The large white sails hanging from the mast seem to be made of "+
           "wool and are very voluminous. You imagine a heavy wind in "+
           "those sails on that mast could carry the ship very quickly "+
           "and safely.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ SAMORGAN_PIER, CADU_PIER }) );
}
