/*
 * Creator:       Zima (copied from Teth)
 * Date:          June 17, 1998
 * Modifications:
 * Purpose:       The ticket to ride the MacDunn-Baile Ashlagh ship.
 * Comments:
 * Collapsed into a small file to new ship line standards by Tapakah
 */
 
#pragma save_binary
#pragma strict_types
 
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

#define TICKET_VALUE 20

inherit STDTICKET;

public void
create_object()
{
  ::create_ticket();
  set_name("ticket");
  add_name("PortmacdunnBaileAshlagh");
  add_adj("purple");
  set_long("The purple ticket is made from a thin sheet of lambskin "+
           "died purple. It gives the bearer passage on the shipline "+
           "that visits the ports of Baile Ashlagh and Port Macdunn.\n");
  add_prop(OBJ_I_VALUE, TICKET_VALUE);
  add_prop(OBJ_I_WEIGHT, 1);
  add_prop(OBJ_I_VOLUME, 5);
  set_price(TICKET_VALUE);
}
 
public void init()
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

  notify_fail("Genesis ShipLines respects the privacy of the passengers.\n");
  return 0;
 
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
  if(!present("_leabag_", environment(this_player())))
    {
    notify_fail("Without the captain present, there is no way to see who "+
      "is on board the ship.\n");
    return 0;
    }
 
  if(!obarr || !sizeof(obarr))
    {
    present("_leabag_", environment(this_player()))->command("say "+
      "There is no one on the ship right now.");
    return 1;
    }
 
  if(sizeof(obarr) == 1)
    {
    present("_leabag_", environment(this_player()))->command("say "+
      "Only "+COMPOSITE_LIVE(obarr)+" is making a voyage so far.");
    return 1;
    }
 
  present("_leabag_",environment(this_player()))->command("say "+
    "Right now, "+COMPOSITE_LIVE(obarr)+" are on board.");
  return 1;
}
*/
