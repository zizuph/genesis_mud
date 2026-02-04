#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;

#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

public void
create_weapon(){
    set_name("dagger");
    add_name("knife");
    set_adj("bone-hilted");
    set_short("bone-hilted dagger");
    set_long("A black blade with a bone hilt, bearing a emblem of a chimera.\n" );
    set_hit(20);
    set_pen(20);
    set_wt(W_KNIFE);
    set_dt(W_SLASH | W_IMPALE);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, 600); 
}
