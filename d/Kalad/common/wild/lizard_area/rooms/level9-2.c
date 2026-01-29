/* 
* Room in the Lizard Caves
* /d/Kalad/common/wild/lizard_area/cave_start.c
*/
#include "../local.h"

inherit LIZARD_STD_ROOM;

/*
 * Function name: create_std_lizard()
 * Description  : Constructor for the room, modify this to change room.
 */
void
create_std_lizard()
{
    string long1, long2, long3;
    
    //Selects the random long description strings
    long1 = one_of_list(LONG1);
    long2 = one_of_list(LONG2);
    long3 = one_of_list(LONG3);
    
    set_short("Inside a Dark Cave");
    set_long(long1+long2+long3+"\n"); 
    
           
    add_exit(RDIR + "level9-3","east");
    add_exit(RDIR + "level9-1","west");
        
    //Sets the no exit message for unlisted directions
    set_no_exit_msg(get_all_no_exits(({"w", "e"})),
    "The cave walls block your path.\n");

    //Adds the npc, the number of them and then arms them.
    add_npc(LIV +"warrior_lizard", 1, &->arm_me());
    add_npc(LIV +"shaman_lizard", 2, &->arm_me());
    
    reset_room();
}

