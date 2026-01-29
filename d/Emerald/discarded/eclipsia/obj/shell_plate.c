inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("platemail");
    set_short("shell platemail");
    add_adj("shell");
    set_long("This piece of armour is a rather strange, but "+
	"effective-looking piece of work. It covers the entire "+
	"torso, and the upper arms with a double-layer of overlapping "+
	"shells with a underlining of chainmail"+
	".\n");
    set_ac(35);
    set_at(A_TORSO|A_R_ARM|A_L_ARM);
}
