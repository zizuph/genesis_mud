inherit "/std/armour";
#include "/sys/wa_types.h"
#include <stdproperties.h>

void create_armour()
{

    set_name("bracers");
    set_pname("bracers");
    set_adj("hide");
    add_adj("hide");
    set_short("hide bracers");
    set_pshort("pairs of hide bracers");
    set_long("The bracers are made from the hide of some" +
        " Athasian creature.\n");

    set_ac(25);
    set_am(({ -4, 2, 2}));
    set_at(A_ARMS);

    add_prop(OBJ_I_WEIGHT, 2600);
    add_prop(OBJ_I_VOLUME, 1800);
}
