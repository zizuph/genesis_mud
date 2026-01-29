inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("sword");
    set_adj("black");
    set_short("black sword");
    set_long("A black blade with a bone hilt, bearing the emblem of an eye.\n" );
    set_hit(36);
    set_pen(32);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
/*    add_prop(OBJ_I_VALUE, comp_value(15)); */
}
