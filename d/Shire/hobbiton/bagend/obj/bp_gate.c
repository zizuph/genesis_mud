/*
 * Bag End back gate
 * Entrance Door
 * -- Finwe, April 2020
 */

inherit "/std/door";
#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>

create_door()
{
    ::create_door();
   
    set_door_id("back_gate");
    set_pass_command(({"w", "west"}));
    set_door_name(({"gate", "back gate", "wooden gate", "small gate", "small wooden garden gate", "garden gate"}));
    set_door_desc("This is a small garden gate. It is made of vertical wood slats. The top of the gate is semi-circular shaped and opens out to the  back of the hill.\n");
    add_item(({"slats", "wooden slats", "vertical wood slats", "wood slats"}),
        "They are the width of a hand and attacjed to a 'Z' frame. The gate has been paited white.\n");

    set_other_room(BE_ROOMS + "lawn01");
    set_open(0);
}
