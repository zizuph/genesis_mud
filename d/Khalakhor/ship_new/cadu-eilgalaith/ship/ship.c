/**********************************************************************
 * - ship.c                                                         - *
 * - Ship that runs between Galaith - SaMorgan                      - *
 * - Created by Damaris@Genesis 12/2000                             - *
 * - Undated by Damaris@Genesis 05/2005                             - *
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
    object cap;
    seteuid(getuid());
    set_cabin(CABIN);
    set_deck(DECK);
    set_name("boat");
    add_name(SHIP_NAME);
    add_name("ship");
    add_adj(({"smooth","impressive"}));
    set_short("smooth impressive ship");
    set_long("This smooth impressive ship is named "+
      "the "+SHIP_NAME+ " and is famed for its sailing near a coral "+
      "reef near the south seas of Khalakhor. The soaring mast with "+
      "large sails is one of its most distinctive characteristics "+
      "about it. The boat travels the route between the isle of "+
      "Galaith and the village of SaMorgan.\n"); 
    add_item(({"mast"}),
       "The central mast of the ship is quite massive, and yet it is "+
       "incredibly fitting to this ship. It was obviously designed to "+
       "withstand formidable winds as it rises high above the deck laden "+
       "with huge sails.\n");
    add_item(({"sails"}),
       "The huge white sails that are hanging from the mast of "+
       "the "+SHIP_NAME+ " seem to be made of fleece and "+
       "are very enormous. There is an image of a woman on one "+
       "of the sails. You can imagine a heavy wind combined with "+
       "those sails could carry the ship very quickly.\n");
     add_item(({"image", "woman"}),
       "The image of the woman is difficult to distinguish due to the "+
       "blowing wind in the sails.\n");
  set_ship_line(MASTER_OB(this_object()), 
                CAPTAIN, TICKET, 
                ({ GALAITH_PIER, CADU_PIER }) );
}
