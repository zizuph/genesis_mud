/*********************************************************************
 * - ticket.c                                                      - *
 * - shipline Gont-Kabal                                           - *
 * - Recoded by Damaris 5/2003                                     - *
 *********************************************************************/
 
#pragma save_binary
#pragma strict_types
 
inherit "/std/object";
#include "../default.h"
#include "defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
 
public void create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("dingy brown");
    set_long("The dingy brown ticket is made from a thin sheet of parchment, "+
             "which is filthy. It gives the bearer passage on the shipline "+
             "that visits the ports of Kabal Port District and Gont.\n");
    add_prop(OBJ_I_VALUE,  PRICE);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 5);
}
 
public void init()
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
  if(!present("_logaan_", environment(this_player())))
    {
    notify_fail("Without the captain present, there is no way to see who "+
      "is on board the ship.\n");
    return 0;
    }
 
  if(!obarr || !sizeof(obarr))
    {
    present("_logaan_", environment(this_player()))->command("say "+
      "There is no one on the ship right now.");
    return 1;
    }
 
  if(sizeof(obarr) == 1)
    {
    present("_logaan_", environment(this_player()))->command("say "+
      "Only "+COMPOSITE_LIVE(obarr)+" is making a voyage so far.");
    return 1;
    }
 
  present("_logaan_",environment(this_player()))->command("say "+
    "Right now, "+COMPOSITE_LIVE(obarr)+" are on board.");
  return 1;
}
