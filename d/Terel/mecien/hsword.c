inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("sword");
    set_adj("holy");
    set_short("holy sword");
    set_long("This is an ancient holy sword, its blade contains many runes.\n" );
    set_hit(80);
    set_pen(50);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
   add_prop("mystic_weapon", 1);
    add_prop(OBJ_I_LIGHT, 3);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
/*    add_prop(OBJ_I_VALUE, comp_value(60)); */
}
