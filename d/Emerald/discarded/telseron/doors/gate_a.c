/* township/doors/gate_a.c is cloned by township/outside_gate.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void
create_door()
{
    set_door_id("towngate");
    set_pass_command( ({ "s", "south" }) );
    set_door_name( ({ "solid gate", "gate" }) );
    set_door_desc("The gate looks as if it has been wrought from "+
    "a single piece of iron ore. It looks like it has withstood "+
    "more than one attack in its time.\n");
    set_other_room(TOWNSHIP_DIR + "inside_gate");
    set_open(0);
}
