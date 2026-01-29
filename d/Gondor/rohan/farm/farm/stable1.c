/* This file is /d/Gondor/olorin/farm/farm/stable1.c       */
/* It belongs to a small farm in the Ered Nimrais          */	
/* Olorin, Nov 1992                                        */

inherit "/std/room";
#include "/d/Gondor/elessar/lib/time.c"
#include "/sys/stdproperties.h"
#include <ss_types.h>
#include "/d/Gondor/defs.h"

create_room() {
	set_short("A stable");
	set_long("This evidently served as a stable for pigs and cows. But " +
        "there seem to be no animals left here. The interior has been " +
        "vandalized. A big puddle of blood on the floor makes it likely " +
        "that at least some of the animals were butchered here. It " +
        "smells terribly like death.\n");
	add_exit(FARM_DIR + "farm/yard1", "west", 0);
	add_item(({"puddle", "blood"}),
        "This is very puddle of fresh blood. It covers almost half the " +
        "floor. Hopefully, it is just animal blood.\n");

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


