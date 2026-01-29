/*
 * /d/Gondor/rhovanion/dolguldur/std/room.c
 *
 * Default base room for new rooms in Dol Guldur
 *
 * Created by Varian, November 2020
 */
 
inherit "/std/room";
#include "/d/Gondor/common/lib/time.c"
#include "/d/Gondor/sys/sunlight.h"

/*
 * Function name: create_dg_room
 * Description  : Construct the room
 */
void create_dolguldur_room() 
{
}
/*
 * Function name: create_room
 * Description  : Constructs a default room, will call the Anorien
 *              : specific constructor.
 */
void create_room()
{
    create_dolguldur_room();
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