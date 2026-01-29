/* File:          /d/Khalakhor/ship/macdunn/faerie/ticket.c
 * Creator:       Teth
 * Date:          November 12, 1997
 * Modifications:
 * Purpose:       The ticket to ride the Khalakhor-Faerie ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/faerie/
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
    add_adj("translucent");
    set_long("The translucent ticket is constructed from an " +
      "odd, paper-like substance. It gives the bearer " +
      "passage on the shipline that visits the ports of " +
      "Faerie and Port Macdunn.\n");
    add_prop(OBJ_I_VALUE, 20);
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

  if(find_object(DECK))
  obarr += FILTER_LIVE(all_inventory(find_object(DECK)));
 
  for(i < 0; i < sizeof(obarr); i++)
    {
    if(function_exists("create_monster", obarr[i]) == CAPTAIN)
      obarr -= ({obarr[i]});
    }
  if(!present("_gwynyd_", environment(this_player())))
    {
    notify_fail("Without the captain present, there is no way to see who "+
      "is on board the ship.\n");
    return 0;
    }

  if(!obarr || !sizeof(obarr))
    {
    present("_gwynyd_", environment(this_player()))->command("say "+
      "No... there is no one on the ship right now...");
    return 1;
    }

  if(sizeof(obarr) == 1)
    {
    present("_gwynyd_", environment(this_player()))->command("say "+
      "Only "+COMPOSITE_LIVE(obarr)+" is making a voyage so far...");
    return 1;
    }

  present("_gwynyd_",environment(this_player()))->command("say "+
    "Right now, ... "+COMPOSITE_LIVE(obarr)+" are ... on board.");
  return 1;
}
