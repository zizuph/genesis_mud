/* 
 * Louie 2005
 * Designed by Anahita
 */

inherit "/std/armour";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define shoe_adjs ({"red","green","blue","purple","black"})

public void
create_armour()
{
    string adj = ONE_OF(shoe_adjs);

    set_name("heels");
    set_pname("heels");
    add_name("armour");
    add_pname("armours");

    set_adj(({"feathery",adj}));
    add_adj(({"glass"}));
    add_name(({"pair of heels","pair of feathery heels"}));
    add_pname(({"pairs of heels","pairs of feathery heels"}));
    set_short("pair of feathery "+adj+" heels");
    set_pshort("pairs of feathery "+adj+" heels");
    set_ac(15);
    set_at(A_FEET);
    set_long("Thin, "+
        "billowy feathers adorn the top of these alluring shoes.  The "+
        "high glass heel is designed to lend an air of seduction to "+
        "any woman who wears them.  "+
        "The heels of these shoes have been coloured "+adj+" for style.  "+
        "\n");

    add_item(({"heel","glass heel"}),
        "The glass heel is long and "+adj+", a striking fashion statement "+
        "guaranteed to get attention.\n");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
}
