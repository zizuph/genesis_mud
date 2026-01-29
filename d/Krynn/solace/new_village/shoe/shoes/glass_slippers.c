/* 
 * Louie 2005
 * Designed by Anahita
 */

inherit "/std/armour";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
create_armour()
{
    set_name("slippers");
    set_pname("slippers");
    add_name("armour");
    add_pname("armours");

    set_adj(({"glass"}));
    add_name(({"pair of slippers","pair of glass slippers"}));
    add_pname(({"pairs of slippers","pairs of glass slippers"}));
    set_short("pair of glass slippers");
    set_pshort("pairs of glass slippers");
    set_ac(10);
    set_at(A_FEET);
    set_long("These shoes were designed by a sadist hoping "+
        "to convince unsuspecting women they were good dancing shoes.  "+
        "Legends say the huckster even managed to convince a few peasant "+
        "girls that the shoes were enchanted, and would cast love spells on "+
        "wealthy noblemen!  "+
        "\n");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_HEAD));
    //mega expensive
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
}
