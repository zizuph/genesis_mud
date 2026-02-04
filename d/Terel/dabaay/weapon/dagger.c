/*
 *  dagger.c
 *
 *  A small dagger, used by the militia of Dabaay 
 *
 *  Goldberry October 19, 1999
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
    set_adj("small");
    set_short("small dagger");
    set_pshort("small daggers");
    set_long(
        "A small dagger with an iron blade and a bone handle.\n");

    set_default_weapon(18,18,W_KNIFE,W_SLASH|W_IMPALE,W_ANYH,TO);
    add_prop(OBJ_I_VOLUME,query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,18)-random(25));
}

