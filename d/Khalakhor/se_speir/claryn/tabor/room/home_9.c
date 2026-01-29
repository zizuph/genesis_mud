/*
 * home_9.c
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
    return ({2, 9});
}

public void
create_khalakhor_room()
{
    create_home();

    add_exit(ROOM + "road_1_9", "west");
    (clone_object(OBJ+"spinning_wheel"))->move(this_object());
}
