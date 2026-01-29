inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("crown");
    set_short("light, golden emerald-studded crown");
    add_adj(({"light", "golden", "emerald-studded"}));
    set_ac(10);
    set_at(A_HEAD);
    set_long("This lovely crown is the one that sits upon the "+
	"head of the Queen of Telberin. Upon each spike is embedded "+
	"a lustrous, large emerald. At the front of the crown is the "+
	"emblem of Telberin."+
	"\n");
}
