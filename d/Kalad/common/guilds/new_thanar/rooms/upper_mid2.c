/* 
 * Room in the Thanarian Cathedral in Kabal
 * /d/Kalad/common/guilds/new_thanar/upper_mid2.c
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
    
           
    add_exit(RDIR + "upper_mid3","east");
    add_exit(RDIR + "upper_mid1","west");
    
    //Sets the no exit message for unlisted directions
    set_no_exit_msg(get_all_no_exits(({"w","e"})),
    "The large wooden pews block your path in that direction.\n");

    //Adds the NPCs, # of them, and ARms them.
    add_npc(LIV +"mpriest", 1, &->arm_me());
    add_npc(LIV +"caster_priest", 1, &->arm_me());
    
    reset_room();
}

