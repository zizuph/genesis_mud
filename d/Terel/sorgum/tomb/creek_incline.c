inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

reset_room()
{
     object rodent;
     if(present("squirrel"))return;
     rodent=clone_object("/d/Terel/silver/monster/squirrel");
     rodent->move(this_object());
     rodent=clone_object("/d/Terel/silver/monster/squirrel");
     rodent->move(this_object());
   }

create_room()
{
    set_short("creek");
    set_long(
       "The creek dries up here leaving a trail of frost covered mud " +
       "that leads away from the end of the creek, uphill from here.\n"
    );

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "hill_top", "west", 0);
    add_exit(TOMBDIR + "creek", "east", 0);
    reset_room();
}


