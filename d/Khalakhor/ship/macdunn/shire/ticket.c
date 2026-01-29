/* File:          /d/Khalakhor/ship/macdunn/shire/ticket.c
 * Creator:       Teth
 * Date:          December 2, 1997
 * Modifications:
 * Purpose:       The ticket to ride the Khalakhor-Shire ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/shire/
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
    add_adj("triangular");
    set_long("This triangular ticket grants passage on the Corran, " +
      "the shipline that ferries passengers between Port Macdunn " +
      "and Grey Havens.\n");
    add_prop(OBJ_I_VALUE, 45);
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
  if(!present("_isoelte_", environment(this_player())))
    {
    notify_fail("Without the captain present, there is no way to see who "+
      "is on board the ship.\n");
    return 0;
    }

  if(!obarr || !sizeof(obarr))
    {
    present("_isoelte_", environment(this_player()))->command("say "+
      "No, no one is on board at the moment.");
    return 1;
    }

  if(sizeof(obarr) == 1)
    {
    present("_isoelte_", environment(this_player()))->command("say "+
      "Right now, only "+COMPOSITE_LIVE(obarr)+" is on my ship.");
    return 1;
    }

  present("_isoelte_",environment(this_player()))->command("say "+
    "Hmmm, "+COMPOSITE_LIVE(obarr)+" are all current passengers.");
  return 1;
}
