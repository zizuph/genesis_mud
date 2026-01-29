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

    add_exit("roomd3", "south");
    add_exit("roomb4", "northwest");
    add_exit("roomb5", "northeast");

} /* create_room */

/*
 * Function name:        get_flowers_desc
 * Description  :        returns flowers colour
 */
string
get_flowers_desc()
{
    return "green";
} /* get_flowers_desc */

/*
 * Function name:        get_exit_dir
 * Description  :        return exit to outer room
 */
string
get_exit_dir()
{
    return "northeast";
} /* get_exit_dir */

/*
 * Function name:        get_lake_dir
 * Description  :        return dir to lake
 */
string
get_lake_dir()
{
    return "southwest";
} /* get_lake_dir */
