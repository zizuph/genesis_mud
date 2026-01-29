/*
 * The audience chamber before the throne room 
 * in the castle in Telseron
 * By Finwe, November 1996
 */

inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"

void reset_room();

void create_room()
{   
    object door;
    reset_room();
    add_prop(ROOM_I_INSIDE,1);
    set_short("Mirror room");
    set_long("   You stand in a room surrounded by mirrors. There is "+
		"nothing else of note in here. Perhaps there will "+
		"be later.\nPlease mail geraden if you have made it "+
		"into this room.\n\n");

    add_item(({"mirror", "mirrors"}), "Yup, they look like mirrors. "+
		"you can see yourself in them.\n");
    add_exit( TCASTLE_DIR + "q_closet", "southwest");
    
   door = clone_object( TOWNSHIP_DIR + "castle/doors/mirror_room_in");
   door->move(this_object());

}


void reset_room()
{
}
