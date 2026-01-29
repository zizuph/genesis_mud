/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp14.c
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
   	set_long("This is deep into the encampment. Wandering "+
		"about this area are soldiers as well as women and children "+
		"going through the various routines of their lives. Some are "+
		"milling about cooking fires, others making repairs on the "+
		"felt rugs used for the yurts, and some are seeing to their "+
		"weapons. All about the noises of a busy camp can be heard.  "+
		"There are no yurts facing this area, and to the north is the "+
		"stockade of the Khahan.\n");
	
   	add_item("soldiers","These are the warriors in the Khahan's army, "+
		"when not occupied in battle, these men perform various "+
		"duties within the encampment. Thier first priority is to the "+
		"Khahan, and as such they are busy making sure thier equipment "+
		"is ready for when they are called to duty.\n");
   	add_item("women","These women are busy making sure everything "+
		"necessary to run a camp is being attended to. They are "+
		"dressed in wool tunics called kalats, trousers, and some "+
		"a head cloak known as a paranji.\n");
   	add_item("stockade","This simple wooden barrier seperates the rest "+
		"of the encampment from the Khahan.\n");

  	add_exit(KAT_CAMP + "camp15","south", 0, 1);  
  	add_exit(KAT_CAMP + "camp19","west", 0, 1);
  	add_exit(KAT_CAMP + "camp5","east", 0, 1);
  	reset_room();
}

