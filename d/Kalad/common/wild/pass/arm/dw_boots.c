/* 
 * /d/Kalad/common/wild/pass/arm/dw_boots.c
 * Purpose    : Leather boots for feet
 * Located    : Used by unknown
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("boots");
    set_adj("black");
    add_adj("leather");
    set_long("A fine set of travelling boots, crafted of rothe "+
      "hide, polished smooth and dyed black.\n");
    set_ac(8);
    set_am(({2, 0, -1}));
    set_at(A_FEET);
    add_prop(OBJ_I_VALUE,250);
    add_prop(OBJ_I_VALUE,1500);
    add_prop(OBJ_I_WEIGHT,1500);
}
