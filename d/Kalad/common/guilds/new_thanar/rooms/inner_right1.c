/* 
 * Room in the Thanarian Cathedral in Kabal
 * /d/Kalad/common/guilds/new_thanar/inner_right1.c
 */
 
#include "../local.h"

inherit THANAR_STD_ROOM; 

/*
 * Function name: create_std_thanar()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_std_thanar()
{
    string long1, long2, long3;
    
    //Selects the random long description strings
    long1 = one_of_list(LONG1);
    long2 = one_of_list(LONG2);
    long3 = one_of_list(LONG3);
    
    set_short("Inside the Cathedral");
    set_long(long1+long2+long3+"\n");  
    
           
    add_exit(RDIR + "inner_mid","west");
    add_exit(RDIR + "inner_right2","east");
    add_exit(RDIR + "centrance","southwest");
    
    //Sets the no exit message for unlisted exits
    set_no_exit_msg(get_all_no_exits(({"w","e","sw"})),
    "The large wooden pews block your path in that direction.\n");

    //Adds the NPCs, # of them, and Arms them.
    add_npc(LIV +"mpriest", 1, &->arm_me());
    add_npc(LIV +"caster_priest", 1, &->arm_me());
    
    reset_room();
}

