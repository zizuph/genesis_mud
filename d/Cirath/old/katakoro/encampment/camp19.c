/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp19.c
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
   	set_long("The frequency of yurts, as well as people has decreased "+
		"as this path wanders further away from the encampment. "+
		"To the south herds of cattle, horses and sheep can be seen "+
		"grazing on the sparse grass that has broken through the "+
		"crust of old snow. To the northwest lies a small clump of "+
		"pure white yurts, while further to the west lies the open "+
		"steppe.\n");

   	add_exit(KAT_CAMP + "camp22","west", 0, 1);
  	add_exit(KAT_CAMP + "camp14","east", 0, 1);
  	add_exit(KAT_CAMP + "camp20","northwest", 0, 1);
	reset_room();
}

