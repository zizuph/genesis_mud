/**********************************************************************
 * - ticket.c                                                       - *
 * - Ticket for ship                                                - *
 * - Created by Damaris@Genesis 03/2001                             - *
 * - Created by Damaris@Genesis 03/2005                             - *
 * - Adapted for the new ship system, Tapakah 04/2009               - *
 **********************************************************************/

#pragma save_binary
#pragma strict_types
 
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

#define TICKET_VALUE 40

inherit STDTICKET;

public void
create_object ()
{
  ::create_ticket();
  set_name("ticket");
  add_name("CaduSaMorgan");
  add_adj("ocean blue");
  set_long("The ocean blue ticket is made from a thin sheet "+
		   "of parchment died ocean blue. It gives the bearer passage "+
		   "on the shipline that visits the ports of SaMorgan and Port "+
		   "Macdunn.\n");
  
  add_prop(OBJ_I_VALUE,  TICKET_VALUE);
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
	if(find_object(CABIN))
	obarr = FILTER_LIVE(all_inventory(find_object(CABIN)));
	if(find_object(DECK))
	obarr += FILTER_LIVE(all_inventory(find_object(DECK)));
	for(i < 0; i < sizeof(obarr); i++)
	{
		if(function_exists("create_monster", obarr[i]) == CAPTAIN)
		obarr -= ({obarr[i]});
	}
	if(!present("_kristo_", environment(this_player())))
	{
		notify_fail("Without the captain present, there is "+
		"no way to see who is on board the ship.\n");
		return 0;
	}
	if(!obarr || !sizeof(obarr))
	{
		present("_kristo_", environment(this_player()))->command("say There is no one on the ship right now.");
		return 1;
	}
	if(sizeof(obarr) == 1)
	{
		present("_kristo_", environment(this_player()))->command("say Only "+COMPOSITE_LIVE(obarr)+" is making a voyage "+
		"so far.");
		return 1;
	}
	present("_kristo_",environment(this_player()))->command("say "+
	"Right now, "+COMPOSITE_LIVE(obarr)+" are on board.");
	return 1;
}
*/
