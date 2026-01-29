/* towncastle/doors/hdoor_a.c is cloned by towncastle/hatchery.c */
inherit "/std/door";
 
#include "../default.h"
 
void
create_door()
{
    set_door_id("hatcherydoor");
    set_pass_command(({"n", "north"}));
    set_door_name(({"door", "hatchery door"}));
    set_other_room(TCASTLE_DIR + "corridor");
    set_open(0);
}
