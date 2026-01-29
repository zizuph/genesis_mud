/* An example door made by Nick, 1991-12-19 */
/* used by Olorin to make door for          */
/* /d/Gondor/rohan/farm/road/yard1.c        */
/* Dec-1992                                 */

inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door() 
{
    ::create_door();
/* You need an id, and both sides should have the same id               */
    set_door_id("road_cottage_door");

    set_pass_command(({"s","south"}));

    set_door_name(({"wooden door","door"}));
    set_door_desc(BS("It looks like the typical door to a farmer's cottage.\n"));

    set_other_room(FARM_DIR + "road/house1");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0);         /* 1 if open, 0 if closed */
    set_locked(0);       /* 1 if locked, 0 if unlocked */
    set_key("Cottage_Key");
}
