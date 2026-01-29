
 /*    A orichalcum trident for the Thalassians

    coder(s):    Digit

    history:    4.7.95    created          Digit
               22.7.95    header added     Digit

 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("trident");
    set_adj("orichalcum");
    set_short("orichalcum trident");
    set_long("This trident is a large, nasty looking three-pronged "+
        "fork.  Made of orichalcum, it is pretty long, about seven feet.  It is "+
        "decorated with unusual looking runes that you do not "+
        "understand.  It is fiery red in color.\n");
    set_hit((31+random(7)));   // Maximum of 37
    set_pen(32);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 3000);
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
