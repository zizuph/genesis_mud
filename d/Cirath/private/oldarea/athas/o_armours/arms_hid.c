/* arms_hid: Hide sleeves for arm protection */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "defs.h"

void create_armour()
{
    set_name("sleeves");
    set_short("jankx hide sleeves");
    set_pshort("pairs of jankx hide sleeves");
    set_long("A jankx is a small lizard with tough leathery skin: So "+
             "small in fact that from neck to tail its only about as "+
             "long as your arm. Of course its disconcerting to be "+
             "wearing an almost intact lizard torso for a sleeve...\n");
    set_adj("jankx");
    add_adj("hide");

    set_ac(30);
    set_am(({ -6, 2, 4}));
    set_at(A_ARMS);

    add_prop(OBJ_I_WEIGHT, 3600);
    add_prop(OBJ_I_VOLUME, 1800);
}
