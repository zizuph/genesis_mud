#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

inherit "/std/weapon";

void
create_weapon()
{
    set_name("sword");
    set_pname("swords");
    
    set_adj("golden");
    set_adj("sharp");

    set_short("sharp golden sword");

    set_long(break_string(
        "This sword is made of the finest steel, coated with a layer "+
        "of gold and sharpened to a razorsharp edge. The handle is "+
        "covered with all kinds of gemstones. It sure looks very "+
        "valuable.\n", 60));

    set_hit(27);
    set_pen(31);
    set_wt(W_SWORD);
    set_dt( (W_SLASH | W_IMPALE) );
    set_hands(W_RIGHT);

    add_prop(OBJ_I_WEIGHT, 5000 + random(1000));
    add_prop(OBJ_I_VOLUME, 3000 + random(500));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(27, 31));
}
