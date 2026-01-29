/* 
 * Room in the Thanarian Cathedral in Kabal
 * /d/Kalad/common/guilds/new_thanar/rooms/upper_left_path2.c
 */

#include "../local.h"

inherit THANAR_STD_ROOM; 

/*
 * Function name: create_std_thanar()
 * Description  : Constructor for the room, modify this to change room.
 */
create_std_thanar()
{
    string long1, long2, long3;
    
    //selects the random room description
    long1 = one_of_list(LONG1);
    long2 = one_of_list(LONG2);
    long3 = one_of_list(LONG3);
    
    set_short("Inside the Cathedral");
    set_long(long1+long2+long3+"\n"); 
    
           
    add_exit(RDIR + "upper_left_path1","southwest");
    add_exit(RDIR + "upper_left_path3","southeast");
    add_exit(BALC + "balcony2", "up");
    
    //sets the no exit message for non-listed directions
    set_no_exit_msg(get_all_no_exits(({"sw","se","u"})),
    "The large wooden pews block your path in that direction.\n");
     
    //adds the mobs to the room and arms them
    add_npc(LIV +"mpriest", 1, &->arm_me());
    add_npc(LIV +"caster_priest", 1, &->arm_me());
    
    reset_room();
}

