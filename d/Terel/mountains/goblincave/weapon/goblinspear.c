/*
 * A polearm for the std_goblin_grd.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name(({"spear","polearm"}));
    set_adj("wooden");
    set_short("wooden spear");
    set_pshort("wooden spears");
    set_long("A wooden spear. The blade is made from a single piece of " +
             "chipped obsidian. The shaft is long, wrapped in leather strips " +
             "to provide a better grip.\n");
    set_default_weapon(30, 30, W_POLEARM, W_IMPALE|W_SLASH, W_BOTH, TO);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, 500);
}
