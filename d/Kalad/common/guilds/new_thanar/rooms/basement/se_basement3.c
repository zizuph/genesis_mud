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
    
           
    add_exit(BASE + "se_basement4","southeast", "@@block@@");
    add_exit(BASE + "se_basement2","northwest");
        
    //sets the no exit message
    set_no_exit_msg(get_all_no_exits(({"nw","se"})),
    "The walls block your path.\n");

    add_npc(LIV +"mpriest", 1, &->arm_me());
    add_npc(LIV +"caster_priest", 1, &->arm_me());

    reset_room();
}

int block(object priest)
{
    
    if (this_player()->query_wiz_level() > 0)
    {
        write("As a wizard you are able to pass");
        return 0;
    }
    
    if (present("_thanar_priest",))
    {
        write("You are stopped from moving any further by the clergy members.\n");
        return 1;
    }
    return 0;
}
