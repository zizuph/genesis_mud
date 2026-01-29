
/*
 * robe.c
 * A religious robe, worn by a Seeker
 * Town of Haven
 * Created by Tibbit, 11 Feb 1998
 *
 */

inherit "/std/armour";

#include "../local.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("robe");
    set_adj("religious");
    add_adj("white");
    add_adj("and");
    add_adj("grey");
    set_short("white and grey religious robe");
    set_pshort("white and grey religious robes");
    set_long("This robe, made of white material overlaid with "+
        "patches of grey in simple designs, is hooded and "+
        "might be worn by a clergyman."+
        "\n");

    set_at(A_ROBE);
    set_ac(2);

    add_prop(OBJ_I_VOLUME, 1000);
        //About 10 cubic centimeters, if you rolled it up
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(2,A_ROBE));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(2));

}

