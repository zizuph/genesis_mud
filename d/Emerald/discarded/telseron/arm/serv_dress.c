inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

#include "/d/Emerald/defs.h"

void
create_armour()
{
    set_name("dress");
    set_short("light-brown leather dress");
    add_adj(({"light", "brown", "light-brown", "leather"}));
    set_ac(6);
    set_at(A_BODY|A_LEGS);
    set_long("This plain brown leather dress seems to be standard "+
	"clothing for the female servants of the castle. Designed to "+
	"be inconspicuous, yet tasteful, it allows the servants to "+
	"go about their chores in the midst of splendour and ceremony "+
	"without overshadowing any of the beauty, while not appearing "+
	"like a common street-person.\n");

    add_prop(TELSERON_ARM, 1);
}
