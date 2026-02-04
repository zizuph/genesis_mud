/*
 * refugee_pickaxe.c
 * axe coded for std_refugee.c in the elderwood forest.
 * Tomas -- June 2000
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>


void
create_weapon()
{
    set_name(({"pickaxe"}));
    set_adj(({"old"}));
    set_short("old pickaxe");
    set_pshort("old pickaxe");
    set_long("The old pickaxe has a long sharpened tip on one end " +
       "and a sharp shovel type blade on the other end.\n");

    set_default_weapon(20, 5+random(5), W_AXE, W_IMPALE | W_SLASH, W_BOTH, TO);

    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VALUE, 2900);
}