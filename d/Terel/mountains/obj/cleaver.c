inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("cleaver");
    set_adj("steel");
    set_short("steel cleaver");
    set_long("A large steel cleaver, it has blood stains on it.\n" );
    set_hit(20);
    set_pen(20);
    set_wt(W_AXE);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
}
