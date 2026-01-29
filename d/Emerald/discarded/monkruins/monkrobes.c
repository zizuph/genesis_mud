inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("robes");
    set_pname("sets of robes");
    set_short("tattered, rotted robes");
    add_adj(({"tattered", "rotted"}));
    set_ac(6);
    set_at(A_ROBE);
    set_condition(4);
    set_long("These robes must have once been a simple, yet clean and "+
	"protecting, piece of clothing. Now, they are not much more than "+
	"a collection of rags still held together by a piece or two of "+
	"thread.\n");
}
