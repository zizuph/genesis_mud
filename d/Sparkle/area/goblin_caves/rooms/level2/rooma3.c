/*
 * Rack room base room
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_RACK_ROOM;

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    add_exit("roomb4", "south");

} /* create_room */

/*
 * Function name:        get_rack_loc
 * Description  :        returns location of rack
 */
string
get_rack_loc()
{
    return "east";
} /* get_rack_loc */
