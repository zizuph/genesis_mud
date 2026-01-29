inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("ring");
    add_name("_kalad_jewel_shop_");
    set_adj("diamond");
    set_short("diamond ring");
    set_long("This is a beautiful golden ring with a large diamond "+
    "gemstone on it. Around the edges of the diamond, tiny red "+
    "rubies are set and they sparkle brightly.\n");
    set_ac(0);
    set_at(A_ANY_FINGER);
    add_prop(OBJ_I_WEIGHT,40);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,5000);
}

