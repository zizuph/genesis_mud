inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("tunic");
    set_short("motley multi-coloured leather tunic");
    add_adj(({"motley", "multi-coloured",  "leather"}));
    set_ac(5);
    set_at(A_TORSO);
    set_long("This leather tunic is dyed a rainbow of colours. It seems"+
	"to provide a bit of protection.\n");
}
