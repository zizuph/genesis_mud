/*
 * refugee_shovel.c
 * shovel coded for std_refugee.c in the elderwood forest.
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
    set_name(({"shovel"}));
    set_adj(({"old"}));
    set_short("old shovel");
    set_pshort("old shovels");
    set_long("An old shovel. Looks like it could bash a " +
       "few heads. Or dig a decent trench.\n");

    set_default_weapon(20, 5+random(5), W_POLEARM, W_BLUDGEON | W_SLASH, W_BOTH, TO);

    add_prop(OBJ_I_WEIGHT, 6500);
    add_prop(OBJ_I_VALUE, 2500);
}