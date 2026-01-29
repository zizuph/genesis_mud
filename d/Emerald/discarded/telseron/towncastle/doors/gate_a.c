/* towncastle/doors/gate_a.c is cloned by towncastle/hatchery.c */
inherit "/std/door";
 
#include "../default.h"
 
void
create_door()
{
    set_door_id("watergate");
    set_pass_command(({"s", "south"}));
    set_door_name(({"water gate", "gate"}));
    set_door_desc( "It is a normal looking water gate.\n" );
    set_other_room(TCASTLE_DIR + "moat8");
    set_open(0);
}
