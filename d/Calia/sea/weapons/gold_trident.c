
 /*    A golden trident for Tritons

    coder(s):    Jaacar

    history:    8.2.96    created          Jaacar

 */

inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("trident");
    set_adj("golden");
    set_short("golden trident");
    set_long("This trident is a large, nasty looking three-pronged "+
        "fork.  Made of iron, plated with gold, it is pretty long, "+
        "about seven feet.  It is "+
        "decorated with unusual looking runes that you do not "+
        "understand.\n");
    set_hit(32);
    set_pen(32);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    set_wf(this_object());
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

mixed
wield(object what)
{
    write("As you grip the trident, it beings "+
        "to glow very bright.  It becomes very hot, almost burning "+
        "your hands.  Finally the glow and heat subside and all is "+
        "normal again.\n");
    return 1;
}

mixed
unwield(object what)
{
    write("As you release your grip on the "+
        "trident, you suddenly feel drained.  After a brief "+
        "moment, the feeling passes.\n");
    return 1;
}
