/* towncastle/doors/hdoor_b.c is cloned by towncastle/corridor.c */
inherit "/std/door";
 
#include "../default.h"
 
void
create_door()
{
    set_door_id("hatcherydoor");
    set_pass_command(({"s", "south"}));
    set_door_name(({"door", "hatchery door"}));
    set_other_room(TCASTLE_DIR + "hatchery");
    set_open(0);
}
