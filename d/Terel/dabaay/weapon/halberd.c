/*
 *  hoe.c
 *
 *  An iron halberd, for the militia of Dabaay 
 *
 *  Goldberry October 19, 1999
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name(({"halberd"}));
    set_adj("iron");
    set_short("iron halberd");
    set_pshort("iron halberds");
    set_long(
        "A strong, nicely balanced halberd. The hardwood handle "+
        "shows evidence of lots of use. The iron blade at the end "+
        "looks as though it might have once been the blade of a hoe.\n");

    set_default_weapon(25, 30, W_POLEARM, W_SLASH, W_BOTH, TO);
    add_prop(OBJ_I_WEIGHT, 2700);
    add_prop(OBJ_I_VALUE, 480);
}

