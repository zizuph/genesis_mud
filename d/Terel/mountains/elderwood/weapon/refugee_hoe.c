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
    set_name(({"hoe"}));
    set_adj(({"gardening"}));
    set_short("gardening hoe");
    set_pshort("gardening hoes");
    set_long("A gardening hoe. The blade looks as if " +
       "it was sharpened recently.\n");

    set_default_weapon(25, 20+random(10), W_POLEARM, W_BLUDGEON | W_SLASH, W_BOTH, TO);

    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, 2500);
}