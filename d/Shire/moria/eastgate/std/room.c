/*
 * /d/Shire/moria/eastgate/std/room.c
 *
 * Default base room for the new rooms in the eastern
 * part of Moria
 *
 * Varian - April, 2020
 */
 
inherit "/std/room";

#include "/d/Gondor/common/lib/time.c"
#include "/d/Gondor/sys/sunlight.h"

/*
 * Function name: create_eastgate_room
 * Description  : Construct the room
 */
void create_eastgate_room() 
{
}
/* create_eastgate_room */

/*
 * Function name: create_room
 * Description  : Constructs a default room, will call the
 *                Eastgate specific constructor.
 */
void create_room()
{
    create_eastgate_room();
}
/* create_room */

/*
 * Function name: init
 * Description  : Add commands to the player
 */
void init() 
{
    ::init();
    add_action(check_time, "time");
}
/* init */