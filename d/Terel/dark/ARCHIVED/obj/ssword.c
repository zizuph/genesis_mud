#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;

#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

public void
create_weapon(){
    set_name("sword");
    add_name("shortsword");
    set_adj("black");
    set_short("black shortsword");
    set_long("A black blade with a bone hilt, bearing a emblem of a chimera.\n" );
    set_hit(36);
    set_pen(36);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, 700); 
}
