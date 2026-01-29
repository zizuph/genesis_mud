
/*
 * vest.c
 * A light leather vest, worn by a citizen of Haven
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
    set_name("vest");
    set_adj("light");
    add_adj("leather");
    set_short("light leather vest");
    set_pshort("light leather vests");
    set_long("A well-worn vest made from brown leather.  "+
        "This is more clothing than armour, but it's better "+
        "than nothing.  The vest is quite lightweight."+
        "\n");

    set_at(A_BODY);
    set_ac(4);

    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(4,A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(4));

}

