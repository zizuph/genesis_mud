inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("halberd");
    set_adj("silver");
    set_short("silver halberd");
    set_long("A well made polearm, with a silver blade.\n");
    set_hit(35);
    set_pen(30);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_SLASH);
/*    add_prop(OBJ_I_VALUE, comp_value(30)); */
}
