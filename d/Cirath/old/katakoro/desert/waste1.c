/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/desert/waste1.c
* Comments: edited by Luther Oct. 2001
*/


inherit "/std/room.c";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>

void
create_room()
{
  	set_short("Northern Wastelands");
   	set_long("Vast emptiness seems to stretch out forever. Scattered "+
		"about the northern steppes are many hills, but even those "+
		"blur in the distance, minor changes in a seemingly "+
		"unchanging wasteland.\n");
	
	OUTSIDE;
		
   	add_exit(KAT_DES + "waste2","south", 0, 1, 1);
   	add_exit(KAT_CAMP + "camp24","north", 0, 1, 1);
	reset_room();
}
