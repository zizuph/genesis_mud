/* File:          /d/Khalakhor/ship/macdunn/ansalon/ticket.c
 * Creator:       Teth
 * Date:          April 12, 1997
 * Modifications:
 * Purpose:       The ticket to ride the Khalakhor-Ansalon ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include "local.h"
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

public void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("dun");
    set_long("This dun ticket grants passage on the Bonnie Lass, the " +
      "shipline that ferries passengers between Port Macdunn and " +
      "Kalaman.\n");
    add_prop(OBJ_I_VALUE, PRICE);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 5);
}

public void
init()
{
  ::init();
  add_action("check_passengers", "check");
}

public int
check_passengers(string str)
{
   object *obarr;
   int i;

  notify_fail("Check what? Passengers, maybe?\n");

  if(!strlen(str) || str != "passengers")
    return 0;


  if(find_object(CABIN))
  obarr = FILTER_LIVE(all_inventory(find_object(CABIN)));

  if(find_object(CABIN2))
  obarr += FILTER_LIVE(all_inventory(find_object(CABIN2)));

  if(find_object(DECK))
  obarr += FILTER_LIVE(all_inventory(find_object(DECK)));
 
  if(find_object(DECK2))
  obarr += FILTER_LIVE(all_inventory(find_object(DECK2)));

  for(i < 0; i < sizeof(obarr); i++)
    {
    if(function_exists("create_monster", obarr[i]) == CAPTAIN)
      obarr -= ({obarr[i]});
    }
  if(!present("_doyle_", environment(this_player())))
    {
    notify_fail("Without the captain present, there is no way to see who "+
      "is on board the ship.\n");
    return 0;
    }

  if(!obarr || !sizeof(obarr))
    {
    present("_doyle_", environment(this_player()))->command("say "+
      "Gaw, business has been slow, nae anyone on board!");
    return 1;
    }

  if(sizeof(obarr) == 1)
    {
    present("_doyle_", environment(this_player()))->command("say "+
      "Well, I've hae better days, only "+COMPOSITE_LIVE(obarr)+" is "+
      "on me ship!");
    return 1;
    }

  present("_doyle_",environment(this_player()))->command("say "+
    "Right now, "+COMPOSITE_LIVE(obarr)+" are on tha Bonnie Lass!");
  return 1;
}
