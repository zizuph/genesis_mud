/*
 * /d/Gondor/anorien/std/room.c
 *
 * Default base room for new rooms in Anorien (plains & Cair Andros)
 *
 * Created by Varian, July 2016
 */
 
inherit "/std/room";
#include "/d/Gondor/common/lib/time.c"
#include "/d/Gondor/sys/sunlight.h"

/*
 * Function name: create_anorien_room
 * Description  : Construct the room
 */
void create_anorien_room() 
{
}
/*
 * Function name: create_room
 * Description  : Constructs a default room, will call the Anorien
 *              : specific constructor.
 */
void create_room()
{
    create_anorien_room();
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