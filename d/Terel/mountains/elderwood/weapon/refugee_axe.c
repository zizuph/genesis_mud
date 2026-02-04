/*
 * refugee_axe.c
 * axe coded for std_refugee.c in the elderwood forest.
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
    set_name(({"axe"}));
    set_adj(({"wood","cutting","double-edged"}));
    set_short("wood cutting axe");
    set_pshort("wood cutting axe");
    set_long("The double-edged wood cutting axe looks very sharp.\n");

    set_default_weapon(30, 30+random(5), W_AXE, W_IMPALE | W_SLASH, W_BOTH, TO);

    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VALUE, 2900);
}