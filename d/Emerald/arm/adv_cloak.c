inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("cloak");
    set_short("bright blue cloak");
    add_adj(({"bright", "blue"}));
    set_long("This cloak seems to be a fairly gaudy armour. It seems to "+
	"be double-layered with silk on the inside and supple leather on "+
	"the outside.\n");
    set_ac(9);
    set_am( ({-1,0,1}) );
    set_at(A_ROBE);
}
