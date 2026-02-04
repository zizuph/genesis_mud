#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;

#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

public void
create_weapon(){
    set_name("sword");
    add_name("sabre");
    set_adj("black-steel");
    set_short("black-steel sabre");
    set_long("A black blade with a bone hilt, bearing a emblem of a chimera.\n" );
    set_hit(39);
    set_pen(36);
    set_wt(W_SWORD);
    set_dt(W_SLASH);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, 900); 
}
