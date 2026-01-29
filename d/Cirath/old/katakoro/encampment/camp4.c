/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp4.c
* Comments: edited by Luther Sept 2001
*/

inherit "/std/room.c";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Cirath/common/mobber.h"

void
create_room()
{
   	set_short("Barbarian camp");
   	set_long("This is deep within the encampment. Yurts are scattered "+
   		"everywhere. All around, people are going about their business.  "+
   		"To the northwest is an unusually large yurt. Occasionally, "+
		"people will walk in and come out with various tools and "+
   		"equipment. Maybe it is some sort of merchant's residence.\n");

   	add_item("yurt","This yurt is similar to the many others that are in "+
		"the area, being made of thick felt rugs. However, this one "+
		"is strangely larger than the ones surrounding it.\n");

   	add_exit(KAT_CAMP + "camp3","south", 0, 1);  
   	add_exit(KAT_CAMP + "camp5","north", 0, 1);  
  	add_exit(KAT_YURTS + "yurt3","enter", 0, 1, 1);  
	reset_room();
}

  
