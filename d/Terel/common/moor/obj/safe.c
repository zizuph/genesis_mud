// Created by Sorgum (c) 1994
// 
// This looks like there is supposed to be a quest to open the 
// safe. I can see items around the property that could be used
// to make something to melt the lock on the safe. I will work
// on getting this implemented while I do the conversion of the
// are from Sorgum's dir to Terel/common/
//  -- Lilith, Dec 2021
// 
// Purpose: This is the chest in the Cottage Chest Quest.
//          Player has to melt the lock with thermite in
//          order to get at the treasure inside.


inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Terel/include/Terel.h"
#include "../local.h"


void
create_container()
{
    set_name("chest");
	set_short("steel chest");
	set_long("This is a large steel chest that is still strong "+
          "despite the rot and decay surrounding it. " +
		  "There is a locking mechanism that appears to "+
		  "have corroded so badly that it is inoperable, making "+
          "the contents within forever secure.\n");
		  
	set_adj(({"large", "steel"}));
	add_name(({"safe", "strongbox", "_cottage_safe", "trunk"}));
	
	add_item(({"lock", "locking mechanism", "mechanism"}),
	    "It looks like a system of tumblers were designed to be "+
        "rotated to lock and unlock the chest, but the whole thing "+
		"is corroded beyond repair.\n");
		
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 120000);
	add_prop(CONT_I_VOLUME, 20000);
	add_prop(CONT_I_MAX_VOLUME, 40000);
	add_prop(CONT_I_TRANSP, 0);
	add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_LOCK, 1);
	add_prop(CONT_I_CLOSED, 1);
	add_prop(OBJ_I_NO_GET, 1);

}
