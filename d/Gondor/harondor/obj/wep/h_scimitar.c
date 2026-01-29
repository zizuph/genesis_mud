/* 
 * Standard Haradrim scimitar from Harondor.
 * Serif, July 2001.
 */

#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
create_weapon()
{
    set_name(({"scimitar", "sword", "weapon"}));
    set_pname("scimitars");
    add_name("swords");
    set_short("long ornamented scimitar");
    set_pshort("long ornamented scimitars");
    set_long("A long curved haradrim sword, made of steel and "
        + "adorned with inlays of gold. It seems light but sturdy.\n");
    set_adj( ({"long", "haradrim", "ornamented", "steel", "curved", }) );
    set_default_weapon(32,30,W_SWORD,W_SLASH,W_NONE,0);
    add_prop(OBJ_I_WEIGHT,2500);
    add_prop(OBJ_I_VOLUME,800);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(30,23)+random(140)-50);
}
