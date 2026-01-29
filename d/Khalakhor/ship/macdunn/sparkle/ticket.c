/* File:          /d/Khalakhor/ship/macdunn/sparkle/ticket.c
 * Creator:       Teth
 * Date:          April 12, 1997
 * Modifications: Converted from Khalakhor/Ansalon run.
 *                Khail - November 28/97.
 * Purpose:       The ticket to ride the Khalakhor-Sparkle ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/sparkle/
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
    add_adj("wrinkled");
    set_long("This wrinkled ticket grants passage on the Sgian Dubh, " +
      "the ship that runs passengers between Port Macdunn and " +
      "Sparkle.\n");
    add_prop(OBJ_I_VALUE, 30);
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

  if(find_object(DECK))
  obarr = FILTER_LIVE(all_inventory(find_object(DECK)));
 
  if(find_object(DECK2))
  obarr += FILTER_LIVE(all_inventory(find_object(DECK2)));

  for(i < 0; i < sizeof(obarr); i++)
    {
    if(function_exists("create_monster", obarr[i]) == CAPTAIN)
      obarr -= ({obarr[i]});
    }
  if(!present("_burwain_", environment(this_player())))
    {
    notify_fail("Without the captain present, there is no way to see who "+
      "is on board the ship.\n");
    return 0;
    }

  if(!obarr || !sizeof(obarr))
    {
    present("_burwain_", environment(this_player()))->command("say "+
      "There are no passengers on board.");
    return 1;
    }

  if(sizeof(obarr) == 1)
    {
    present("_burwain_", environment(this_player()))->command("say "+
      "Well, only "+COMPOSITE_LIVE(obarr)+" is on board!");
    return 1;
    }

  present("_burwain_",environment(this_player()))->command("say "+
    "Right now, "+COMPOSITE_LIVE(obarr)+" are passengers on the " +
    "Sgian Dubh!");
  return 1;
}
