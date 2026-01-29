/* body_brl: Simple shirt for the poor who still need armour. */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("dress");
    set_short("food-stained dress");
    set_long("This stained dress is made of pretty rough cloth, so it "+
             "will endure a lot of everyday wear and tear.\n");
    set_adj("food-stained");

    set_ac(10);
    set_am(({ -1, -1, 2}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 1125);
    add_prop(OBJ_I_VOLUME, 575);
}
