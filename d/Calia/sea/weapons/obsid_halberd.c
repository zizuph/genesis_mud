
 /*    Obsidian halberd for the water krougs

    coder(s):   Digit

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
    set_name("halberd");
    set_adj("obsidian");
    set_short("obsidian halberd");
    set_long("The obsidian halberd has a black blade the size of "+
        "your hand at the end of a long black pole.  It looks "+
        "razor sharp.\n");
    set_hit(23);
    set_pen(25);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
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
