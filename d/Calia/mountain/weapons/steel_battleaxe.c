/*  steel battleaxe wielded by some elite krougs

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
    set_name("battleaxe");
    add_name("axe");
    set_adj("steel");
    set_short("steel battleaxe"); 
    set_pshort("steel battleaxes"); 
    set_long("A powerful looking weapon used by elite kroug warriors. " +
             "The battleaxe has big, razor-sharp twin steel blades.\n");
    set_hit(36);
    set_pen(36);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 14000);
    add_prop(OBJ_I_VOLUME, 7000);
}

