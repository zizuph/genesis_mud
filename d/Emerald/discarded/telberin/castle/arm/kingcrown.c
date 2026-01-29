inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("crown");
    set_short("heavy, golden emerald-studded crown");
    add_adj(({"heavy", "golden", "emerald-studded"}));
    set_ac(13);
    set_at(A_HEAD);
    set_long("This heavy crown is the one that sits upon the "+
	"head of the ruler of Telberin. Upon each spike is embedded "+
	"a heavy, large emerald. At the front of the crown is the "+
	"emblem of Telberin."+
	"\n");
}
