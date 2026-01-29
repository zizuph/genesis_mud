inherit "/d/Shire/room";
#include "../defs.h"
#include <stdproperties.h>

create_room()
{
    set_short("Guards room.");
    set_long(
    	"This is obviously a place where the guards here spend most of their time. "
    	+"It is filled with broken weapons and broken armours. Dirt and filth covers "
    	+"the floor, and the smell in here is aweful. The walls are carved out in "
    	+"rock, and it looks like it has been made naturally. There is an exit leading "
    	+"south into a greater hall.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);

    add_item(({"broken weapons","weapons","broken armours","armours"}),
		 "The weapons and armours scattered in this room are totaly "
		+"obliterated.  They are of no use at all.\n");
   
    add_item(({"dirt","filth","floor"}),"The floor is dirty, like dirt is.\n");

    add_item(({"smell"}),"Yup, it smells bad.\n");

    add_item(({"wall","walls","rock","rock wall"}),"The walls are made out of rock.\n");
    
    //add_prop(OBJ_I_SEARCH_TIME, 6);
    //add_prop(OBJ_S_SEARCH_FUN, "wep_search");
    
    //set_search_places(({"ground", "floor", "dirt", "filth"}));
    
    add_exit(TROLLSH_DIR + "w_hall", "south", 0);
    
   reset_room();
}
reset_room() { add_stuff(); }

add_stuff()
{
   object pipe, bracelet, kit, glass;

   if(!present("pipe"))
    {
     pipe = clone_object(TROLLSH_DIR + "obj/pipe");
     pipe->add_prop(OBJ_I_HIDE, 25);
     pipe->move(TO);
    }

   if(!present("kit"))
    {
     kit = clone_object(TROLLSH_DIR + "obj/kit");
     kit->add_prop(OBJ_I_HIDE, (random(60)));
     kit->move(TO);
    }

   if(!present("glass"))
    {
     glass = clone_object(TROLLSH_DIR + "obj/glass");
     glass->move(TO);
    }
}
