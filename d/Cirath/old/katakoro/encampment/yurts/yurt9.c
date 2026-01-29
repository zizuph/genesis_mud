/*
* Created by: Chaos
* Date: 19 April 1995
*
* File: /d/Cirath/katakoro/encampment/yurts/yurt9.c
* Comments: Metalworker's Yurt	,edited by Luther Oct. 2001
*/

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

void
create_room()
{
    
    	set_short("Metalworker's yurt");
    	set_long("This yurt is home to a metalworker. Scattered about the "+
		"place are various metal items in differing stages of "+
		"completion. There are sabers, arrowheads, and even a few "+
		"bows. Along with these items there are some metal shavings "+
		"scattered about the room, a result of the smith's work.  "+
		"Towards the back of the room is a small rough hewn table and "+
		"chair. There is also an exit to the north which leads to the "+
		"forge.\n");

    	add_item("table","There is nothing really remarkable about the table "+
		"other than the fact that it is made of wood, a rare item in the "+
		"treeless steppe. Sitting on the table there are some rings.\n");
    	add_item("rings","These rings are yet another example of the skilled "+
		"craftsmanship found among these barbarians. Each one is finely "+
		"crafted, with incredible detail.\n");

    	INSIDE;

	add_exit(KAT_YURTS + "forge","north", 0, 1);
	add_exit(KAT_CAMP + "camp16","out", 0, 1);
    	reset_room();
}

