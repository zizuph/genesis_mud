inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("hammer");
    set_adj("great");
    set_short("gold hammer");
    set_long("A large hammer, forged of a luminous gold metal.\n" +
             "It is of exquisite work. Cryptic runes are inscribed\n" +
             "upon it.\n");
    set_hit(30);
    set_pen(40);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 8000);
/*    add_prop(OBJ_I_VALUE, comp_value(30)); */
}
