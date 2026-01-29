inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("cloak");
    set_short("long black cloak");
    add_adj(({"long", "black"}));
    set_ac(6);
    set_at(A_ROBE);
    set_long("This cloak is quite long and dyed a dark black. "+
	"It gives the wearer a little added protection on their "+
	"torso and legs.\n");
}
