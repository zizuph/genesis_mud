/* 
 * Entrance to the Thanarian Cathedral in Kabal
 * /d/Kalad/common/guilds/new_thanar/entrance
 */

#include "../local.h"

inherit THANAR_BALC_STD; 

/*
 * Function name: create_std_thanar()
 * Description  : Constructor for the room, modify this to change room.
 */
create_std_thanar()
{
    string long1, long2, long3;
    //selects the random long descriptions
    long1 = one_of_list(BALC_LONG1);
    long2 = one_of_list(BALC_LONG2);
    long3 = one_of_list(BALC_LONG3);
    
    set_short("On the Balcony");
    set_long(long1+long2+long3+"\n");  
    
           
    add_exit(BALC + "balcony_upper5","east");
    add_exit(BALC + "balcony_upper7","west");
    //sets the no exit message
    set_no_exit_msg(get_all_no_exits(({"w","e"})),
    "You don't want to jump of the balcony do you?\n");

    reset_room();
}

