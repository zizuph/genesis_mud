inherit "std/armour.c";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("boots");
    set_short("a pair of soft leather boots");
    add_adj("leather");
    set_ac(8);
    set_am( ({0,1,-1}) );
    set_at(A_LEGS);
    set_long("These soft leather boots provide ample protection.\n");
}
