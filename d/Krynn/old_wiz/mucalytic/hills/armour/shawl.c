/* A gypsy's shawl. ~mucalytic/hills/armour/shawl */

inherit "/std/armour";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void create_armour()
{
    set_name("shawl");
    set_adj("patchwork");
    set_long("A warm looking shawl made from scraps of material sewn "+
        "together in a haphazard fashion.\n");

    set_ac(5);

    /*       Imp  Sla  Blu  */
    set_am(({ 0,  -2,   2 }));

    set_at(A_ROBE);

    set_likely_cond(1);
    set_likely_break(2);

    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 1200);
}
