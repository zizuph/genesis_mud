inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("robe");
    set_short("heavy, golden fur-lined robe");
    add_adj(({"heavy", "golden", "fur-lined"}));
    set_ac(12);
    set_at(A_ROBE);
    set_long("This heavy robe is made of some very large animal "+
	"hide that has been so immaculately prepared, that it "+
	"has none of the roughness of normal animal-hide clothing. "+
	"The whole robe has been dyed a brilliant gold color, and "+
	"the collar and seams have been lined with a plush fur."+
	"\n");
}
