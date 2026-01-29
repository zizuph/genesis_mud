/* A pearl necklace. ~solace/puzzle/armour/pearl_necklace */

inherit "/std/armour";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void create_armour()
{
    set_name("necklace");
    set_adj("pearl");
    set_long("A beautiful and expensive looking pearl necklace.\n");

    set_ac(2);
    set_at(A_NECK);

    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 250);

    add_prop(OBJ_I_VALUE, 750 + random(250));
}
