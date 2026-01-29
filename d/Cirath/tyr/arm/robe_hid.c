/* robe_hid: The best common cloak in the Athas. */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("cloak");
    set_short("stiff hide cloak");
    set_long("Mekillot hide is not very flexible, but it makes fine armour, "+
             "even in the role of a simple cloak.\n");
    set_adj("stiff");
    add_adj("hide");

    set_ac(20);
    set_am(({ -3, 1, 2}));
    set_at(A_ROBE);

    add_prop(OBJ_I_WEIGHT, 6700);
    add_prop(OBJ_I_VOLUME, 3350);
}
