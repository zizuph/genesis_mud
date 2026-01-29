/*
 * /d/Gondor/lebennin/std/room.c
 *
 * Default base room for new rooms in Lebennin
 *
 * Based on Anorien work by Varian
 * Rugne, February 2017
 */
 
#pragma strict_types


#include "/d/Gondor/sys/sunlight.h"

inherit "/d/Gondor/common/lib/time";
inherit "/std/room";

/*
 * Function name: create_lebennin_room
 * Description  : Construct the room
 */
void create_lebennin_room() 
{
}
/*
 * Function name: create_room
 * Description  : Constructs a default room, will call the Anorien
 *              : specific constructor.
 */
void create_room()
{
    create_lebennin_room();
}
/*
 * Function name: init
 * Description  : Add commands to the player
 */
void init() 
{
    ::init();
    add_action(check_time, "time");
}
