/*	revision of /d/Genesis/start/human/town/parrot.c
 *
 *	When I created the first draft to Sparkle there was a parrot
 *	sitting on a pole down by the docks. The location, maybe not
 *	so properly named, parrot.c is still here but the parrot is
 *	not. It has most likely been edited out at some point in the
 *	rooms revision history.
 *	So, I thought I should reintroduce the poor creature.
 *	Anyway... I have done so, not here but in a central Liwitch
 *	control room which in turn moves the parrot to this location.
 *	It moves around a bit but when you see Polly, do ask her some
 *	questions and see what happens. :)
 *	
 *	/Styles 081030
 *
 *  Modifications:
 *    - Converted to new Genesis ShipLines, Petros, April 2009
 *
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>                                                   
#include <macros.h>
#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

public void
create_pier()
{
    set_short("Berth 9 - Calia");
    set_long("\n"+
		"You walk along the south pier of Sparkle harbour.\n" +
		"The sea is lapping gently beneath you in rippling patterns.\n" + 
		"On a pole here there is a sign which reads: Berth 9 - Calia.\n");

    add_item(({"pier" }),"It's a pier. It allows for the ships to moor.\n");     
	add_item(({"pole", "wooden pole" }),"A sturdy wooden pole "+
		"with a sign on.\n");
    add_item(({"sign" }),"The sign has text which reads: " +
		"Passage to the Lands of Calia.\n");
    add_item(({"sea", "water", "waves" }),
		"You know, that watery stuff that drips everywhere. " +
		"There seems to be a lot of it around here. This variety " +
		"is salty too.\n"); 

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit(TOWN_DIR + "pier8", "west");
    add_exit(TOWN_DIR + "pier10", "east");

    setuid();
    seteuid(getuid());    
    add_pier_entry(MASTER_OB(this_object()), "Sparkle", "Pier to Gelan");    
}
