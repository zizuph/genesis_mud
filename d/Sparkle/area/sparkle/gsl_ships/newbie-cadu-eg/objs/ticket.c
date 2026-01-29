/* File:          /d/Khalakhor/ship/macdunn/calia/ticket.c
 * Creator:       Teth
 * Date:          April 15, 1997
 * Modifications:
 * Purpose:       The ticket to ride the Khalakhor-Calia ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/calia/
 *                /d/Khalakhor/open/SHIPLINES
 * Ported to the new ship system by Tapakah, 05/2009
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

#define TICKET_VALUE 45

inherit STDTICKET;
public void
create_object()
{
	::create_ticket();
  set_name("ticket");
  add_name("newbiecaduenchantedgarden");
  add_adj("ragged");
  set_long("This ragged ticket grants passage on the Cuinnsear, " +
           "the fishing vessel that occasionally ferries newbies " +
           "around Sparkle, Gelan, Cadu and Enchanted Garden of Terel.\n");
  add_prop(OBJ_I_VALUE, TICKET_VALUE);
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VOLUME, 5);
  set_price(TICKET_VALUE);
}

public void
init()
{
  ::init();
  //add_action("check_passengers", "check");
}
/*
public int
check_passengers(string str)
{
   object *obarr;
   int i;

  notify_fail("Check what? Passengers, maybe?\n");

  if(!strlen(str) || str != "passengers")
    return 0;

  if(find_object(DECK))
  obarr = FILTER_LIVE(all_inventory(find_object(DECK)));
 
  for(i < 0; i < sizeof(obarr); i++)
    {
    if(function_exists("create_monster", obarr[i]) == CAPTAIN)
      obarr -= ({obarr[i]});
    }
  if(!present("_cian_", environment(this_player())))
    {
    notify_fail("Without the captain present, there is no way to see who "+
      "is on board the ship.\n");
    return 0;
    }

  if(!obarr || !sizeof(obarr))
    {
    present("_cian_", environment(this_player()))->command("say "+
      "Business is poor right now!");
    return 1;
    }

  if(sizeof(obarr) == 1)
    {
    present("_cian_", environment(this_player()))->command("say "+
      "Well, only "+COMPOSITE_LIVE(obarr)+" is on my rowboat.");
    return 1;
    }

  present("_cian_",environment(this_player()))->command("say "+
    "Right now, "+COMPOSITE_LIVE(obarr)+" are on my little rowboat.");
  return 1;
}
*/
