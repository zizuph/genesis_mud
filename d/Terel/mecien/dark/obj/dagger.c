inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("dagger");
    set_adj("stone");
    set_short("stone dagger");
    set_long("A large sharp stone dagger.\n" );
    set_hit(15);
    set_pen(15);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
}
