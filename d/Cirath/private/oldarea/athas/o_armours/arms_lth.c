/* arms_lth: A pair of leather shoulder pads. */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("pads");
    set_short("pair of leather shoulder pads");
    set_long("Thick and extremely sturdy, these pads of leather are made "+
             "to be strapped to the shoulder.\n");
    set_adj("leather");
    add_adj("shoulder");

    set_ac(10);
    set_am(({ -1, 0, 1}));
    set_at(A_ARMS);

    add_prop(OBJ_I_WEIGHT, 1800);
    add_prop(OBJ_I_VOLUME, 900);
}
