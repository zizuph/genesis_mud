inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("axe");
    set_adj("great");
    set_short("great axe");
    set_long("A monstrous iron axe.\n" );
    set_hit(30);
    set_pen(30);
    set_wt(W_AXE);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 9000);
    add_prop(OBJ_I_VOLUME, 8000);
}
