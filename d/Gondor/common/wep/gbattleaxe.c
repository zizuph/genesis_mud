/* Increased hit/pen, Eowul, 2009 */
/* battleaxe  */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

public void
create_weapon()
{
    set_name(({"battleaxe","axe","weapon"}));
    set_pname("battleaxes");
    add_pname("axes");
    set_short("shiny steel battleaxe");
    set_pshort("shiny battleaxes");
    set_long("A heavy Gondorian battleaxe, made of strong oak and shiny steel.\n"+
        "It is made to be wielded in both hands.\n");
    set_adj( ({ "shiny", "steel", "large", "gondorian", }) );
    set_default_weapon(26,40,W_AXE,W_SLASH,W_BOTH,0);
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,1400);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(26,40)+random(200)-100);
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
