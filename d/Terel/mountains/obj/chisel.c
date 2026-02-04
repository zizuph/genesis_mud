

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("chisel");
    set_adj("iron");
    set_short("chisel");
    set_long("An iron chisel, for carving stone.\n" );
    set_hit(5);
    set_pen(5);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
/*    add_prop(OBJ_I_VALUE, comp_value(2)); */
}
