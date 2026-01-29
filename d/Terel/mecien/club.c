inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("club");
    set_adj("iron-banded");
    set_short("iron-banded club");
    set_long("A huge club made from a tree trunk and banded with iron.\n" );
    set_hit(32);
    set_pen(27);
    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    add_prop(OBJ_I_WEIGHT, 30000);
    add_prop(OBJ_I_VOLUME, 10000);
}
