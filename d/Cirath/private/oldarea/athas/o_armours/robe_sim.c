/* robe_sim: A simple commoners robe. */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("robe");
    set_short("simple dusty robe");
    set_long("While only mildly better then no cloak at all, there are many "+
             "out there who make use of such things.\n");
    set_adj("simple");
    add_adj("dusty");

    set_ac(5);
    set_am(({ -1, -1, 2}));
    set_at(A_ROBE);

    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 900);
}
