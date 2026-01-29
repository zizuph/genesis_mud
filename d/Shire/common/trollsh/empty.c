inherit "/d/Shire/room";
#include "../defs.h"
#include <stdproperties.h>

create_room()
{
    set_short("Guards room.");
    set_long(
    	"This is obviously a place where the guards here spend most of their time. "
    	+"It is filled with broken weapons and broken armours. Dirt and filth covers "
    	+"the floor, and the smell in here is awfull. The walls are carved out in "
    	+"rock, and it looks like it has been made naturally.\n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, -1);
    

    add_item(({"broken weapons","weapons","broken armours","armours"}),
		 "The weapons and armours scattered in this room are totaly "
		+"obliterated.  They are of no use at all.\n");
   
    add_item(({"dirt","filth","floor"}),"The floor is dirty, like the dirt is.\n");

    add_item(({"smell"}),"Yup, it smells bad.\n");

    add_item(({"wall","walls","rock","rock wall"}),"The walls are made out of rock.\n");

    /* is the following going to be implemented by anyone, if no comment */
    /* is given by 1.nov i will remove this feature...   Dain.   */

    //add_prop(OBJ_I_SEARCH_TIME, 6);
    //add_prop(OBJ_S_SEARCH_FUN, "wep_search");
    
    //set_search_places(({"ground", "floor", "dirt", "filth"}));
    
    add_exit(TROLLSH_DIR + "w_hall", "east", 0);
    
}

