inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Monks Dormatory");
	set_long("   You have entered a large, simple living quarters " +
	"The floor is covered with stiff, firm mattresses, but no one is currently sleeping here. " +
	"There is a doorway to the east.\n\n");
    add_exit(TEMPLE_DIR + "quarters", "north", 0);
    add_exit(TEMPLE_DIR + "bathroom", "east", 0);
 
    add_item(({"mattress","mattresses"}),"The mattresses don't"+
       " look very comfortable. They are all stuffed with a thin layer "+
       "of straw.\n");
}
