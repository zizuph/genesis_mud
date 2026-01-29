/*
 * l_chest.c
 * Rigid Leather Chest plate for Thanduin.
 * - Alaron Feb 1998
 */

#include "../dirheader.h"
#include "../coramar.h"
#include <wa_types.h>
#include <formulas.h>
#include "/d/Emerald/defs.h"

inherit "/std/armour";

void
create_armour()
{
    set_name("chestplate");
    add_name("plate");
    set_adj("chest"); add_adj("rigid"); add_adj("leather");
    set_short("rigid leather chestplate");

    set_long("This dark, rigid leather chest plate is lightweight and "+
             "appears extremely sturdy. Judging from the almost shining "+
             "appearance of the piece of armour, its owner must take "+
             "very good care of it, and its creator was obviously "+
             "quite skilled.\n");


    set_at(A_TORSO);
    set_am( ({0,1,-1}) );
    set_ac(8);

    add_prop(OBJ_I_WEIGHT, 1600);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8));
}
