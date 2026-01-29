/* 
 * Louie 2005
 * Designed by Anahita
 */

inherit "/std/armour";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define shoe_adjs ({"black","white","brown"})

public void
create_armour()
{
    string adj = ONE_OF(shoe_adjs);

    set_name("sandals");
    set_pname("sandals");
    add_name("armour");
    add_pname("armours");

    set_adj(({"leather",adj}));
    add_adj(({"suede","elaborate"}));
    add_name(({"pair of sandals","pair of leather sandals"}));
    add_pname(({"pairs of sandals","pairs of leather sandals"}));
    set_short("pair of elaborate leather sandals");
    set_pshort("pairs of elaborate leather sandals");
    set_ac(15);
    set_at(A_FEET);
    set_long("Long "+adj+" leather "+
        "straps rise from the suede soles of these sandals.  The straps "+
        "criss-cross the leg before being tied tightly just below the knee.  "+
        "\n");


    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
}
