inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/solace/graves/local.h"

void
create_armour()
{
    set_name("chainmail");
    set_long("This has got to be the strangest armour you've ever seen.\n"
      + "The armour is made of many small ringed pieces of bone all intermeshed.\n"
      + "To form a good imitation of chainmail.\n");
    set_default_armour(22);
    set_adj("bone");
    set_short("bone chainmail");
}

string
query_recover()
{
    return OBJ + "skel_arm2.c:" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
