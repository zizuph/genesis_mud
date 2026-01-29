/* A walnut door - this door is used to get to Enzalcaspin's home.       */
/* Door for cave28c.c - coded by Tulix III, 05/11/95                     */

inherit "/std/door";

#include "/d/Emerald/defs.h"

public void
create_door()
{
    set_door_id("enzalcaspins_store_room_door");
    set_pass_command(({"exit","leave","go through","enter","north"}));
    set_door_name(({"walnut door","door"}));
    set_other_room(CAVE_DIR + "levelc/cave27c");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    add_prop(DOOR_I_HEIGHT, 200);
    set_open(0);
    set_locked(1);
}
