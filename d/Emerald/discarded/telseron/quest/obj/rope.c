/*
 * Rope needed for Telseron swing quest
 * By Finwe
 * February 1997
 * Based on Nick's rope example
 */
 
#include "/d/Emerald/defs.h"
inherit "/std/rope";
 
create_rope()
{
    set_name("rope");
    set_adj( ({"long,","silk"}));
    set_long("You examine the rope and discovered that it is " +
        "long, silky, and quite strong looking. It must have " +
        "belonged to an elf who passed through the forest " +
        "recently. Surely they will miss their rope but now you " +
        "have found it.\n");
}

public void
init()
{
    ::init();
 
    add_action(tie_rope, "tie");
    add_action(tie_rope, "untie");
}
