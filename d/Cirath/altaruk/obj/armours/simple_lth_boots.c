inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void create_armour()
{
    set_name("boots");
    set_adj("simple");
    add_adj("leather");
    set_short("pair of simple leather boots");
    set_pshort("pairs of simple leather boots");
    set_long("A pair of simple leather boots.\n");

    set_ac(10);
    set_am(({ -2, 0, 2}));
    set_at(A_FEET);

    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME, 225);
}
