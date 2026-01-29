/* body_hid: Armour made from tough Mekillot hide */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("shirt");
    set_short("tough hide shirt");
    set_long("Hide taken from the larger lizards of Athas, particularly "+
             "mekillots and braxi, can be formed into good armour by a "+
             "decent craftman. If the lizards don't mind.\n");
    set_adj("tough");
    add_adj("hide");

    set_ac(30);
    set_am(({ -6, 2, 4}));
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 6250);
    add_prop(OBJ_I_VOLUME, 3125);
}
