/**********************************************************************
 * - hall2.c                                                        - *
 * - The hallway within the Temple of Thanar                        - *
 * - Created by Damaris@Genesis 3/2004                              - *
 * - New Standrad file for new area for guild. Typos fixed.         - *
 * - by Mirandus@Genesis 01/2018                                    - *
 **********************************************************************/

#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit THANAR_STD_ROOM; 

/*
 * Function name: create_std_thanar()
 * Description  : Creates the room from standard room file
 */
void
create_std_thanar()
{

    set_short("Oval Temple Hallway");
    set_long("This long hallway is a private passageway to the "+
      "inner temple rooms. Within these vaulted walls members may "+
      "meet and discuss topics of interest to them without fear "+
      "of interruption from non-believers. Only those faithful "+
      "of Thanar may enter this place.\n");
    add_item(({"room", "area", "entrance", "hall", "oval hall"}), query_long);
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);  

    add_exit("post", "north");
    add_exit("join", "southwest");
    set_no_exit_msg(get_all_no_exits(({"sw","n"})),
    "There is a wall blocking your path.\n");
}
