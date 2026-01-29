/*
 *  /d/Sparkle/area/orc_temple/rooms/2_cell3.c
 *
 *  This is one of the many cells on the prison level (level 2) of the
 *  orc dungeons near Sparkle.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

#include "../defs.h"

inherit ROOMS_DIR + "cell_room";


/* 
 * Function name:        create_cell_room
 * Description  :        set up the cell
 */
public void
create_cell_room()
{
    set_door_direction("east");
}
