/* 
 * Testing room for Lizard Guild
 */
 
#include "lizards.h"

inherit "/std/room";

/*
 * Function name: create_std_thanar()
 * Description  : Constructor for the room, modify this to change room.
 */
create_room()
{
    set_short("Test room for the nightvision");
    set_long("Room set to be dark so that we can test if the "
	+"new nightvision property stuff works.\n");  
	
	add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);
    
           
    add_exit(LIZGUILD + "lizard_join","west");
            
    reset_room();
}

