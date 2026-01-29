/* 
 * Basement of the Cathedral
 * /d/Kalad/common/guilds/new_thanar/rooms/basement/se_basement1.c
 */

#include "../local.h"

inherit THANAR_BASE_STD; 

/*
 * Function name: create_std_thanar()
 * Description  : Constructor for the room, modify this to change room.
 */
create_std_thanar()
{
    string long1, long2, long3;
    
    //selects the random long descriptions
    long1 = one_of_list(BASE_LONG1);
    long2 = one_of_list(BASE_LONG2);
    long3 = one_of_list(BASE_LONG3);
    
    set_short("Beneath the Cathedral");
    set_long(long1+long2+long3+"\n");  
    
           
    add_exit(BASE + "upper_basement5","east");
    add_exit(BASE + "upper_basement3","west");
        
    //sets the no exit message
    set_no_exit_msg(get_all_no_exits(({"w","e"})),
    "The walls block your path.\n");

    reset_room();
}

