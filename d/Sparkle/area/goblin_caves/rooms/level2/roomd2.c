/*
 * corridor room room
 * Boreaulam, Sep 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_CORRIDOR_ROOM;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    add_exit("roome2", "south");
    add_exit("roomc1", "north");
    add_exit("roomd1", "west");

} /* create_room */

/*
 * Function name:        get_flowers_desc
 * Description  :        returns flowers colour
 */
string
get_flowers_desc()
{
    return "blue";
} /* get_flowers_desc */

/*
 * Function name:        get_exit_dir
 * Description  :        return exit to outer room
 */
string
get_exit_dir()
{
    return "west";
} /* get_exit_dir */

/*
 * Function name:        get_lake_dir
 * Description  :        return dir to lake
 */
string
get_lake_dir()
{
    return "east";
} /* get_lake_dir */
