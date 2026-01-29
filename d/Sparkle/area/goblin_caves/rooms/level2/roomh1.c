/*
 * Rack room base room
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_LIVING_ROOM;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    add_npc(NPCS_DIR + "l2_girl_in_love", 1, &->arm_me());

    ::create_room();

    add_exit("roomg1", "northeast");
} /* create_room */

/*
 * Function name:        get_exit_dir
 * Description  :        returns room exit
 */
string
get_exit_dir()
{
    return "northeast";
} /* get_exit_dir */
