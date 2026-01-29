/* legs_hid: Legwear made of tough hide. */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("leggings");
    set_short("pair of braxat hide leggings");
    set_pshort("pairs of braxat hide leggings");
    set_long("Hide of this thickness is usually not flexible enough to "+
             "wear on a limb, but the skin of a braxat is unusually "+
             "pliable, particularly that from their legs.\n");
    set_adj("hide");
    add_adj("braxat");

    set_ac(30);
    set_am(({ -6, 2, 4}));
    set_at(A_LEGS);

    add_prop(OBJ_I_WEIGHT, 3600);
    add_prop(OBJ_I_VOLUME, 1800);
}
