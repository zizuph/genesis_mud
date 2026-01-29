/* 
 * Room in the Thanarian Cathedral in Kabal
 * /d/Kalad/common/guilds/new_thanar/inner_mid.c
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
    
    //Selects the random long description strings
    long1 = one_of_list(LONG1);
    long2 = one_of_list(LONG2);
    long3 = one_of_list(LONG3);
    
    set_short("Inside the Cathedral");
    set_long(long1+long2+long3+"\n");  
    
           
    add_exit(RDIR + "inner_left1","west");
    add_exit(RDIR + "upper_mid5","north");
    add_exit(RDIR + "inner_right1","east");
    add_exit(RDIR + "centrance","south");
    
    //Sets the no exit message for unlisted exits
    set_no_exit_msg(get_all_no_exits(({"n","s"})),
    "The rest of the Cathedral is still under construction.\n");

    //Adds the NPC, # of them, and arms them.
    //add_npc(LIV +"cpriest", 2, &->arm_me());
            
    reset_room();
}

