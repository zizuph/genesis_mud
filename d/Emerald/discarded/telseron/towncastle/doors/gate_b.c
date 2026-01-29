/* towncastle/doors/gate_b.c is cloned by towncastle/moat8.c */
inherit "/std/door";
 
#include "../default.h"
 
void
create_door()
{
    set_door_id("watergate");
    set_pass_command(({"n", "north"}));
    set_door_name(({"water gate", "gate"}));
    set_door_desc( "It is a normal looking water gate.\n" );
    set_other_room(TCASTLE_DIR + "hatchery");
    set_open(0);
}
