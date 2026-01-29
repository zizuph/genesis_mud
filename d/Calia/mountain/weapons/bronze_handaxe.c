/*  bronze handaxe wielded by some kroug warriors

    coder(s):  Maniac

    history:     4/8/95     Created                        Maniac

*/

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("handaxe");
    add_name("axe");
    set_adj("bronze");
    set_short("bronze handaxe"); 
    set_pshort("bronze handaxes"); 
    set_long("A nasty looking weapon used by regular kroug warriors. " +
             "It is a plain, sharp looking handaxe, made of bronze.\n");
    set_hit(22);
    set_pen(20);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VOLUME, 5000);
}

