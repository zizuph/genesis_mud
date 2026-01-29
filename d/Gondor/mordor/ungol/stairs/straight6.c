/*
 * /d/Gondor/mordor/ungol/stairs/straight6.c
 *
 * This is a part of the Straight Stair. I like these kind of rooms that have
 * all the fancy stuff in a default file.
 *
 * /Mercade, 22 November 1993
 *
 * Revision History:
 */

inherit "/d/Gondor/mordor/ungol/stairs/std_straight.c";

#include "/d/Gondor/defs.h"
#include "stairs.h"

#define UP_ROOM   STAIRS_DIR + "straight7"
#define DOWN_ROOM STAIRS_DIR + "straight_half"

void
create_room()
{
    make_the_room();
}

/*
 * Function name: query_room_down
 * Description  : This is an ugly function to allow me to define DOWN_ROOM
 *                in this file and access it from the inherited file.
 */
string
query_room_down()
{
    return DOWN_ROOM;
}

/*
 * Function name: query_room_up
 * Description  : This is an ugly function to allow me to define UP_ROOM in
 *                this file and access it from the inherited file.
 */
string
query_room_up()
{
    return UP_ROOM;
}
