/* This file is /d/Gondor/olorin/farm/road/stable1.c       */
/* It belongs to a small farm in the Ered Nimrais          */	
/* Olorin, Nov 1992                                        */

inherit "/std/room";
#include "/d/Gondor/elessar/lib/time.c"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

create_room() 
{
	set_short("A stable");
	set_long(BS("This evidently served as a stable for pigs and cows. But there seem "
            + "to be no animals left here. Everything is in good "
            + "repair, but nothing movable has been left here.\n"));
	add_exit(FARM_DIR + "road/yard1", "west", 0);
        add_prop(ROOM_I_INSIDE, 1);
}
	
sunrise()
{
  tell_room(this_object(),"The sun rises in Gondor and Middle-earth.\n");
  return 1;
}

sunset()
{
  tell_room(this_object(),"The sun sets in Gondor and Middle-earth.\n");
  return 1;
}


