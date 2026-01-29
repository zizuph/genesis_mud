/*
 *  Axe for goblin caves
 * - Boreaulam, April 2012
 */
#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

/*
 * Function name:        create_weapon
 * Description  :        constructor for the object
 */
void
create_weapon()
{

    set_name("axe");
    set_adj("black");
    set_adj("long");
    set_short("long black axe");
    set_long("As you study the blackened blade of this axe, you swiftly " +
        "understand that this could be a deadly weapon in the hands of a " +
        "skilled warrior. The axe has a very long handle, giving the " +
        "weapon an impressive reach and the iron blade has been blackened " +
        "for extra hardness and durability.\n");

	int wc = 20 + random (5);
    set_hit(wc);
    set_pen(wc);
    set_wt(W_AXE);
    set_dt(W_SLASH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(wc, wc) + random(200));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(wc, W_AXE));

    set_hands(W_BOTH);
} /* create_weapon */

