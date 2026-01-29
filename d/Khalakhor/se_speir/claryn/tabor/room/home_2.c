/*
 * home_2.c
 *
 * A simple home in Tabor Sogh.
 *
 * Khail - January 17 / 98.
 */
#pragma strict_types
#include "room.h"

inherit HOMEBASE;

public int *
query_local_coords()
{
    return ({2, 2});
}

public void
create_khalakhor_room()
{
    create_home();

    add_exit(ROOM + "road_1_2", "west");
}