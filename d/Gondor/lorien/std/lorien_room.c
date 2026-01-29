/*
 * /d/Gondor/lorien/std/room.c
 *
 * Default base room for new rooms in Lorien
 *
 * Coded Mona 2020  
 * Thanks: Varian
 */

inherit "/std/room";

#include "/d/Gondor/common/lib/time.c"
#include "/d/Gondor/sys/sunlight.h"
#include "/d/Gondor/defs.h"

/*
 * Function name: create_lorien_room
 * Description  : Construct the room
 */
void 
create_lorien_room() 
{
}

/*
 * Function name: create_room
 * Description  : Constructs a default room, will call the lorien
 *              : specific constructor.
 */
void 
create_room()
{
    create_lorien_room();
}

/*
 * Function name: init
 * Description  : Add commands to the player
 */
void
init() 
{
    ::init();
    add_action(check_time, "time");
}
