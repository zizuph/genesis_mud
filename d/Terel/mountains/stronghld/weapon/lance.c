/*
 * lance.c 
 * Standard issue for dwarven_lancer.c
 * Tomas  -- Jan 2000.
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name(({"lance","polearm","staff"}));
    set_adj(({"wooden","long"}));
    set_short("long wooden lance");
    set_pshort("lances");
    set_long("A long wooden steep tiped lance. Commonly used " +
       "while on horseback.\n");

    set_default_weapon(30, 35, W_POLEARM, W_IMPALE, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VALUE, 800);
}
