inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
    set_name("knife");
    set_adj("stone");
    set_short("stone knife");
    set_long("A small sharpened stone knife.\n" );
    set_hit(6);
    set_pen(8);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE);
}
