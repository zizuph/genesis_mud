
 /*    A tin trident for the Thalassians

    coder(s):    Digit

    history:    4.7.95    created          Digit
               22.7.95    header added     Digit

 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("trident");
    set_adj("tin");
    set_short("tin trident");
    set_long("This trident is a large, nasty looking three-pronged "+
        "fork.  Made of tin, it is pretty long, about six feet.  It is "+
        "decorated with unusual looking runes that you do not "+
        "understand.\n");
    set_hit(33);
    set_pen(33);
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
