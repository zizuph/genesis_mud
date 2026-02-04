inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("sword");
    add_name("sword");
    set_adj("curved");
    set_pshort("curved swords");
    set_short("curved sword");
    set_long("A wicked looking curved sword.\n");
    set_hit(36);
    set_pen(36);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
/*    add_prop(OBJ_I_VALUE, comp_value(15)); */
}
