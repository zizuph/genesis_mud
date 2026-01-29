/* 
 * Louie 2005
 * Designed by Anahita
 */

inherit "/std/armour";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define shoe_adjs ({"black","white","red","transparent"})

public void
create_armour()
{
    string adj = ONE_OF(shoe_adjs);

    set_name("huarache");
    set_pname("huaraches");
    add_name(({"armour","sandals"}));
    add_pname(({"armours","sandals"}));

    set_adj(({"leather","hide"}));
    add_name(({"pair of huarache","pair of leather huaraches","pair of sandals"}));
    add_pname(({"pairs of huarache","pairs of leather huarache","pairs of sandals"}));
    set_short("pair of leather huarache");
    set_pshort("pairs of leather huarache");
    set_ac(10);
    set_at(A_FEET);
    set_long("Skilled craftswomen have worked the "+
        "leather in these sandals to make them as soft as possible. A wide "+
        "strip of hide wraps around a single toe and across the top "+
        "of the foot, leaving the rest of your skin exposed to the air.  "+
        "\n");


    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
}
