inherit "/std/drink";
#include "/sys/stdproperties.h"

create_drink()
{
    set_soft_amount(200);
    set_alco_amount(49);
    set_name(({"spirit","_flotsam_c_spirit_"}));
    set_adj("dwarven");
    set_short("shot of dwarven spirits");
    set_pshort("shots of dwarven spirits");
    set_long("This drink is traditional dwarven spirits. Be warned! " +
      "It is renown for its potency, and is not for the " +
      "weak stomach!\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
