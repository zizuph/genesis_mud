inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("sandals");
    set_pname("pairs of sandals");
    set_short("pair of rotted sandals");
    add_adj(({"rotted", }));
    set_long("This footwear is some of the most worst kept that you "+
	"you have ever seen. The leather bottoms have rotten through "+
	"in many spots, and the lacings have mostly torn away. The "+
	"whole thing smells like rotted flesh."+
	"\n");
    set_ac(3);
    set_condition(3);
    set_am( ({-1,0,1}) );
    set_at(A_FEET);
}
