/*
 * A polearm for the guards and arena of Calathin.
 * Coded by Shinto 10-7-98
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name(({"staff","quarterstaff","polearm"}));
    set_adj("wooden");
    set_short("wooden quarterstaff");
    set_pshort("wooden quarterstaves");
    set_long("A sturdy wooden quarterstaff. The staff is about six feet long "+
             "with semi-worn leather grips of your hands.\n");
    set_default_weapon(30, 30, W_POLEARM, W_IMPALE|W_SLASH, W_BOTH, TO);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VALUE, 800);
}

