/*
 * Polearm coded for std_refugee.c in the elderwood forest.
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
    set_name(({"stick","staff"}));
    set_adj(({"thick","walking"}));
    set_short("thick walking stick");
    set_pshort("thick walking sticks");
    set_long("The thick walking stick looks like it could " +
       "do some damage.\n");

    set_default_weapon(25, 20+random(5), W_POLEARM, W_BLUDGEON , W_BOTH, TO);

    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, 2500);
}