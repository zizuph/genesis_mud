/* 
 * /d/Kalad/common/wild/pass/arm/dw_robe.c
 * Purpose    : A strong robe of drow make
 * Located    : Used by the drows in Undreath
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
create_armour()
{
    ::create_armour();
    set_name("robe");
    set_adj("black");
    set_long("This robe is of exceptional quality, and is made of a "
      +"very fine fabric. Although lightweight, there is a rigidity "
      +"to it that makes it suitable as armour.\n");
    set_ac(4);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE,320);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_WEIGHT,100);
}
