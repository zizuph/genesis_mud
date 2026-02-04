/*
 * refugee_knife.c
 * knife coded for std_refugee.c in the elderwood forest.
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
    set_name(({"knife"}));
    set_adj(({"large","kitchen"}));
    set_short("large kitchen knife");
    set_pshort("large kitchen knives");
    set_long("The large kitchen knife looks sharp.\n");

    set_default_weapon(7, 5+random(5), W_KNIFE, W_IMPALE | W_SLASH, W_ANYH, TO);

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VALUE, 500);
}