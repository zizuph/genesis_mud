inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("tunic");
    set_short("red leather tunic");
    add_adj(({"red", "leather"}));
    set_ac(5);
    set_at(A_TORSO);
    set_long("This leather tunic is dyed a dark red. It seems"+
	"to provide a bit of protection.\n");
}
