inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("robe");
    set_short("grey flowing robe");
    add_adj(({"grey", "flowing"}));
    set_ac(6);
    set_at(A_ROBE);
    set_long("The robe is of a fairly heavy cloth which is dyed a "+
	"light grey. The robe is quite oversized and flows around the "+
	"wearers body loosely.\n");
}
