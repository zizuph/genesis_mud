inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/solace/graves/local.h"


void
create_armour()
{
    set_name("leather");
    set_long("It's a tattered piece of leather, you could barely call it armour.\n");
    set_default_armour(8);
    set_adj("tattered");
    set_short("tattered leather");
}

string
query_recover()
{
    return OBJ + "skel_arm.c:" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
