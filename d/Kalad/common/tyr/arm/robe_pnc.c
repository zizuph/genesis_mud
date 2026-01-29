/* robe_pnc: A leather poncho for Eastwood fans.... */
inherit "/d/Kalad/std/armour";
#include <wa_types.h>
#include "defs.h"

void create_armour()
{
    ::create_armour();
    set_name("poncho");
    set_short("leather poncho");
    set_long("Carefully designed to block the suns rays while not keeping "+
             "the wearer restricted, the relatively hardened leather near "+
              "the shoulders should provide some protection.\n");
    set_adj("leather");

    set_ac(10);
    set_am(({ -1,  0,  1}));
    set_at(A_ROBE);

    add_prop(OBJ_I_WEIGHT, 3600);
    add_prop(OBJ_I_VOLUME, 1800);
}
