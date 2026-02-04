

inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("axe");
    set_adj("steel");
    set_short("steel axe");
    set_long("A sharp steel axe.\n" );
    set_hit(25);
    set_pen(20);
    set_wt(W_AXE);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 8000);
}
