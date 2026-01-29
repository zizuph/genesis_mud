inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("mantle");
    set_short("black leather mantle");
    add_adj(({"black", "leather"}));
    set_ac(5);
    set_at(A_TORSO);
    set_long("This leather mantle is dyed midnight black. It seems" +
      "to provide a bit of protection.\n");
}
