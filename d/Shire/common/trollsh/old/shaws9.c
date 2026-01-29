/* File: /d/Shire/common/trollsh/shaws9.c */

#include "defs.h"
inherit "/d/Shire/common/trollsh/shawrom"; /*master object*/


create_shawrom()
{
    set_short("Deep in the Trollshaw on a ridge.");
    set_extraline(
	 "You are deep in the Trollshaw. "
	+"There are a lot of bushes on the south end of this ridge. "
	+"It's not possible to see the ground, because of the dense "
	+"vegetation. To the east there is a small path following "
	+"the ridge, while to the south a slope seems to lead "
        +"to a lightly vegetated area.");
    
	EAST("shaws13");
	SOUTH("shaws8");
  
   if (!present("_outside_troll", TO))
      room_add_object("/d/Shire/common/trollsh/npc/outside_troll",1,
          "A troll wanders in grinning.\n");
}

