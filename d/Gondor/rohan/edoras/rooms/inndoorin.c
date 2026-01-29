inherit "/std/door";
#include "/d/Gondor/defs.h"

public void
create_door()
{
    ::create_door();
    set_door_id("edoras_inn");
    set_pass_command(({"w","west"}));
    set_door_name(({"wooden door","door"}));
    set_door_desc(BS("The door leads out of the inn onto the stairs leading up the hill to the golden hall Meduseld.\n"));
    set_other_room(EDORAS_DIR + "stairs2");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_pick(40);
    set_key("_sleeping_stallion_key");
}
 
/*
 * Function name:       pass_door
 * Description  :       perform combat checks before calling parent's
 *                      pass_door().
 * Arguments    :       string arg - arguments given
 */
int
pass_door(string arg)
{
    if ( !ENV()->check_combat() )
        return ::pass_door(arg);
 
    return 1;
}
