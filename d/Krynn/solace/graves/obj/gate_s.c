/* gate between new and old graveyard */


inherit "/std/door";
#include "../local.h"

create_door()
{
    ::create_door();

    set_door_id("gate");
    set_pass_command(({"s","south"}));
    set_door_name(({"old wrought iron gate", "wrought iron gate", "gate", 
	"old gate"}));
    set_other_room(TDIR + "o_grave4");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0); 
    set_locked(0);
    set_pick(40);
}
