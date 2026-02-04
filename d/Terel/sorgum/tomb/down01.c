inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

void 
reset_room()
{
     object dweller;

     if (!present("dweller1", TO)) {
	  dweller = clone_object(TOMBDIR + "dweller1");
	  dweller -> move(TO);
     }
}

create_room()
{
     set_short("Down under the tomb\n");
     set_long("You are in a room underneath the tomb.\n");

     add_prop(ROOM_I_INSIDE);
     add_prop(ROOM_I_LIGHT, 0);

     reset_room();
}

