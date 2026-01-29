inherit "/std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>

void create_armour()
{
    set_name("helm");
    set_adj("bone");
    set_short("bone helm");
    set_long("This helm is made from the bones of some large" +
        " Ahtasian creature.\n");

    set_ac(25);
    set_am(({ 2, 2, -4}));
    set_at(A_HEAD);

    add_prop(OBJ_I_WEIGHT, 1400);
    add_prop(OBJ_I_VOLUME, 700);
}
