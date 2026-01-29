inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

#include "/d/Emerald/defs.h"

void
create_armour()
{
    set_name("tunic");
    set_short("brilliant-blue embroidered tunic");
    add_adj(({"brilliant", "blue", "embroidered", "leather"}));
    set_ac(5);
    set_at(A_TORSO);
    set_long("This lovely thick cloth tunic is dyed a brilliant blue. "+
	"It is very loose-fitting and has no sleeves. It is simply "+
	"draped over the shoulders and tied at the waist. The front and "+
	"back have a large embroidered insignia of the Royal House of "+
	"Telseron on them. It seems to provide a bit of protection, but "+
	"it's main functionality seems to be some sort of uniform that is "+
	"very easily recognizable, even from a distance.\n");

    add_prop(TELSERON_ARM, 1);
}
