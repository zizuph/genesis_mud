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
    ::create_room();

    add_exit("roomd2", "east");

} /* create_room */

/*
 * Function name:        get_exit_dir
 * Description  :        returns room exit
 */
string
get_exit_dir()
{
    return "east";
} /* get_exit_dir */
