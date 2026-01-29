/*
 *   /d/Gondor/tolfalas/wep/orcknife.c
 *
 *
 *   Made by Toby 26 Sept 2006
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

 
int iHit = 30;
int iPen = 35;


void
create_weapon()
{
    set_name("knife");
    set_adj("jaded");
    add_adj("steel");
    set_short("jaded steel knife");
    set_long("This knife is about one foot long from the tiny crossguard to " +
             "its tip. The blade is quite broad and slightly curved, the edges " +
             "jaded but still quite sharp. The handle is wrapped tightly in " +
             "leather cords that are almost black from sweat and grease.\n");

    set_default_weapon(iHit, iPen, W_KNIFE, W_IMPALE | W_SLASH, W_ANYH, this_object());
    add_prop(OBJ_I_WEIGHT, 1500 );
    add_prop(OBJ_I_VOLUME, 1500 );
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(iHit, iPen));
}
 
