/* larm_chn: A chain mail sleeve for the left arm. */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("sleeve");
    set_short("rusty chain sleeve");
    set_long("Metal armour in Athas is commonly made to protect the limbs "+
             "since head or torso protection would produce heat stroke.\n");
    set_adj("rusty");
    add_adj("chain");

    set_ac(45);
    set_am(({ -6, 2, 4}));
    set_at(A_R_ARM);

    add_prop(OBJ_I_WEIGHT, 2250);
    add_prop(OBJ_I_VOLUME, 1125);
}
