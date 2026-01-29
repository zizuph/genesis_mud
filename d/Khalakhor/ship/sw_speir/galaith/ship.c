/**********************************************************************
 * - ship.c                                                         - *
 * - Ship that runs between Galaith - SaMorgan                      - *
 * - Created by Damaris@Genesis 12/2000                             - *
 * - Undated by Damaris@Genesis 05/2005                             - *
 **********************************************************************/

 
#pragma save_binary
#pragma strict_types
 
inherit "/d/Genesis/ship/ship";
#include "local.h"
#include <cmdparse.h>
#define  TP (this_player())
 
public void
create_ship()
{
    object cap;
    seteuid(getuid());
    set_cabin(CABIN);
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    cap->arm_me();
    set_captain(cap);
    set_places_to_go(({
        INISI + "galaith/pier/pier1",
        GALAITH + "beach",
        GALAITH + "sea1",
        GALAITH + "sea2",
        GALAITH + "beach1",
        S_WEST + "samorgan/pier/pie1206",
        GALAITH + "beach1",
        GALAITH + "sea2",
        GALAITH + "sea1",
        GALAITH + "beach",
      }));
 
    set_time_between_stops
      (({
        20, 3, 3, 3, 3,
        20, 3, 3, 3, 3,
      }));
 
    set_ticket_id(TICKET_NAME);
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
}
 
public int board(string what)
{
    object ticket, *tmp;
 
    if (!board_enabled) return 0;
 
    if (what && (!sizeof(tmp = FIND_STR_IN_OBJECT(what, environment(TP))) ||
        this_object() != tmp[0]))
        return 0;
 
    if (this_player()->query_average_stat() >= 20) return ::board(what);
 
    write("You board the ship.\n");
    environment(TP)->set_dircmd(what);
    TP->move_living("boarding the ship", query_deck()[0]);
    return 1;
}
