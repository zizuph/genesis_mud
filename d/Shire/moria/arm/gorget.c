/*
 * 2005/01/21 Last update
 * 2011/07/20 Lavellan - Removed MORIA_ARM prop. This is _obj_i_is_magic_armour
 *                       and is not used anywhere else... Strange.
 */

#include "defs.h";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit BASE_ARMOUR;
inherit "/lib/keep";

#include "recover"

CONSTRUCT_ARMOUR
{
    set_name("gorget");
    add_adj("iron");
    set_short("iron gorget");
    set_long("This is a plate ring which sits on the shoulders and covers " +
      "the neck. It is made of hammered iron and polished to a faded " +
      "burnished color.\n");

    set_ac(20);
    set_am(({1,1,-2}));
    set_at(A_NECK);

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME,  600);
    add_prop(OBJ_I_VALUE,   122+random(40));
//    add_prop(OBJ_I_MORIA_ARM, 1);
    set_keep();
}

