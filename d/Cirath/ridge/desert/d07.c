/* The road west of Tyr.
  * Code (c) Damian Horton 1998
  */

#pragma strict_types
#pragma save_binary

#include "defs.h"

inherit BASE_DESERT;

void
create_desert()
{

   set_short("On a road, west of Tyr.");
  set_long("On an elevated road of packed red Earth. The road heads "+
	"east towards Tyr, and west, towards the daunting forms of the "+
	"Ringing mountains. The road is bounded to the north and south "+
	"by the agricultural fields controlled by Tyr's nobles. The "+
	"fields are presently empty, though not unwatched.\n");

  add_item(({"crops","neep","guard","plants","crop","field","fields"}),
	"The fields are filled with a low growing crop, which you "+
	"identify as neep. The root of the neep plant is a common "+
	"item in Athasian cuisine, while the yellowish stubble "+
	"which passes for leaves is commonly used as fodder. It "+
	"is evident that neep is not presently in season, for "+
	"there are no slaves tending to the fields. However, "+
	"the occasional guard can still be seen watching "+
	"over them.\n");

  add_item("road","Its a road of packed earth, rising about "+
      "ten feet above the surrounding ground.\n");

  add_item(({"mountains","mountain","Ringing Mountains",
	"Ringing mountains","ringing mountains"}),
	"The Ringing Mountains cover the entire western horizon. "+
	"Despite their barren appearance they look beautiful as the "+
	"sunlight reflects off of their reddish colored slopes.\n");

  add_item(({"Tyr","city"}),"From here you can barely make out the "+
	"thick walls of the Citystate of Tyr.\n");

  add_cmd_item(({"food","crop","crops","neep"}),
      ({"pick","take","harvest"}),"The roots are not yet ripe, and "+
      "you have no use for fodder.\n");
    
  add_exit(RIDGE_DESERT+"d08.c","east",0,4,0);
  add_exit(RIDGE_DESERT+"d03.c","northeast",0,6,0);
  add_exit(RIDGE_DESERT+"d02.c","north",0,6,0);
  add_exit(RIDGE_DESERT+"d01.c","northwest",0,6,0);
  add_exit(RIDGE_DESERT+"d06.c","west",0,4,0);
  add_exit(RIDGE_DESERT+"d10.c","southwest",0,6,0);
  add_exit(RIDGE_DESERT+"d11.c","south",0,6,0);
  add_exit(RIDGE_DESERT+"d12.c","southeast",0,6,0);
}

