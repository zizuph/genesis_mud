inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Emerald/defs.h"

void
create_armour()
{
    set_name("cap");
    set_short("deep-blue feathered cap");
    add_adj(({"deep-blue", "deep", "blue", "feathered"}));
    set_ac(2);
    set_am( ({0,1,-1}) );
    set_at(A_HEAD);
    set_long("This cap is rather striking with a large silver-dyed "+
	"feather protruding from the brim, while the cloth is made of "+
	"a richly-colored deep blue cloth that's shaped in a quite "+
	"fashionable manner with the front a sharp point that angles "+
	"down, then flares out at the sides, then folds back up to form "+
	"an raised point in the back. It seems to be a fairly weak piece "+
	"of armour, unless the attacks the wearer wishes to ward off are "+
	"fashion criticisms. A small label on the inside identifies it as "+
	"property of the Royal House of Telseron and is issued to various "+
	"ceremonial and official servents of some sort.\n");

    add_prop(TELSERON_ARM, 1);
}
