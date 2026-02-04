inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("spear");
    set_adj("old");
    set_short("old spear");
    set_long("An old spear, somewhat rotted, but its iron tip still sharp.\n");
    set_hit(20);
    set_pen(20);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
/*    add_prop(OBJ_I_VALUE, comp_value(5)); */
}
