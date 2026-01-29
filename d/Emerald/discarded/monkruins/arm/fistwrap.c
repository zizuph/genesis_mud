inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("wraps");
    set_pname("pairs of wraps");
    set_short("pair of strong brown leather wraps");
    add_adj(({"strong", "leather", "brown"}));
    set_long("These strips of leather, when worn, are wrapped around "+
	"the fists, and down the forearm, protecting the arms and hands. "+
	"They bear scars and strains of many strong blows over years of "+
	"combat and training."+
	"\n");
    set_ac(9);
    set_am( ({-1,0,1}) );
    set_at(A_ARMS|A_HANDS);
}
