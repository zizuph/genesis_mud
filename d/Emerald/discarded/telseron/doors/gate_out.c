/* township/doors/gate_b.c is cloned by township/inside_gate.c */
inherit "/std/door";
 
#include "/d/Emerald/defs.h"
 
void
create_door()
{
    set_door_id("towngate");
    set_pass_command( ({ "nw", "northwest" }) );
    set_door_name( ({ "solid gate", "gate" }) );
    set_door_desc("The gate looks as if it has been wrought from "+
        "a single piece of steel like metal. There aren't any marks " +
        "on it and is polished to a mirror like sheen. It is " +
        "decorated with an intricate filligree design.\n");
    set_other_room(TOWNSHIP_DIR + "nw_gate");
    set_open(0);
}
