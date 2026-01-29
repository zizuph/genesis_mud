inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void create_armour()
{
    set_name("boots");
    set_pname("boots");
    set_adj("leather");
    set_short("pair of leather boots");
    set_pshort("pairs of leather boots");
    set_long("A rugged pair of leather boots.\n");

    set_ac(20);
    set_am(({ -2, 0, 2}));
    set_at(A_FEET);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 750);
}
