inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("shirt");
    set_short("supple leather shirt");
    add_adj(({"supple", "leather"}));
    set_ac(7);
    set_at(A_TORSO);
    set_long("This leather shirt looks quite comfortable as well as"+
	"providing a fair amount of protection for the wearer.\n");
}
