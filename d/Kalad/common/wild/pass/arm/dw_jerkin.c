/* 
 * /d/Kalad/common/wild/pass/arm/dw_jerkin.c
 * Purpose    : A leather jerkin of drow make
 * Located    : Used by drows in Undreath
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
create_armour()
{
    ::create_armour();
    set_name("jerkin");
    set_adj("hide");
    set_long("This jerkin is made of a rugged rothehide that is "
      +"stiff, yet beaten flexible. It has many scratches and marks "
      +"on it, probably from previous battles.\n");
    set_ac(8);
    set_am(({2, 0, -1}));
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,320);
    add_prop(OBJ_I_VOLUME,1100);
    add_prop(OBJ_I_WEIGHT,1100);
}
