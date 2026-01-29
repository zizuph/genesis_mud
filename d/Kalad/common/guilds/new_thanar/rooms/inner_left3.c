/* 
 * Room in the Thanarian Cathedral in Kabal
 * /d/Kalad/common/guilds/new_thanar/inner_left3.c
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
    
           
    add_exit(RDIR + "nw_path1","northwest");
    add_exit(RDIR + "inner_left2","east");
    add_exit(BALC + "balcony3","up");
    
    //Sets the no exit message for unlisted directions
    set_no_exit_msg(get_all_no_exits(({"nw","e","u"})),
    "The large wooden pews block your path in that direction.\n");

    //Adds the npc, the number of them and then arms them.
    add_npc(LIV +"mpriest", 1, &->arm_me());
    add_npc(LIV +"caster_priest", 1, &->arm_me());
    
    reset_room();
}

