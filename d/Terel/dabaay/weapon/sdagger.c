/*
 *  sdagger.c
 *
 *  A steel dagger
 *
 *  Goldberry January, 2000
 * Reduced hit and pen to 19/19. Shinto, November, 2000
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

void
create_weapon()
{
    set_name(({"dagger"}));
    set_adj("steel");
    set_short("steel dagger");
    set_pshort("steel daggers");
    set_long(
        "A fine dagger with a steel blade and a wooden handle.\n");

    set_default_weapon(19,19,W_KNIFE,W_SLASH|W_IMPALE,W_ANYH,TO);
    add_prop(OBJ_I_VOLUME,query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(25,25)-random(25));
}

