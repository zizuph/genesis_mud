/*
   Pax Tharkas, Ground level, Nurses room, Flamestrike (Matafleur).

   nurseroom.c
   -----------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/03/28
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

object dragon;


reset_pax_room()
{
   if (!present("flamestrike",TO))
   {
      dragon = clone_object(PMONSTER + "flamestrike");
      dragon->move(TO);
   }
}
	

void
create_pax_room()
{
   reset_pax_room();

   set_short("Nursemaid chamber");
   set_long("You are standing in a large, barren and windowless room. " +
            "There is no furniture in here. The only objects in this " +
            "chill, stone chamber is a huge basin of water and a huge " +
            "bucket filled with something that looks like rotten meat. " +
            "In the western wall you see an entrance to a tunnel.\n");
	
   INSIDE;

   add_prop(ROOM_I_LIGHT,0);

   add_item("basin", "A huge basin half filled with water. The basin " +
            "has been carved into the cold stone floor.\n");

   add_item("bucket", "This is a huge wooden bucket filled with more " +
            "or less rotten meat. The smell of it isn't exactly " + 
            "appetizing.\n");

   add_item(({"meat", "rotten meat"}), "The meat is lying in a huge " +
            "bucket and is more or less rotten. The smell of it makes " +
            "you want to skip the next meal.\n");

   add_item("tunnel", "The tunnel looks newer that the rest of the room. " +
            "You get the suspicion, that it has been built to " +
            "keep someone in here, or out of here.\n");

   add_exit(GROUND_LEVEL + "c_prison", "northeast", 0);
   add_exit(GROUND_LEVEL + "playroom" , "tunnel" , 0);
}

void
enter_inv(object ob, object from)
{
    object drag;

    if ((drag = present("flamestrike", TO)))
        drag->react_to_arrives(ob);

    ::enter_inv(ob, from);
}
