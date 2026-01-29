/* 
 * /d/Kalad/common/wild/pass/arm/dw_plate.c
 * Purpose    : A platemail of drow make
 * Located    : Used by drows in Undreath
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
create_armour()
{
   ::create_armour();
   set_name("platemail");
   set_adj("drow");
   set_long("This suit of platemail is extremely light, yet appears to "
      +"be quite durable. It is of average drow workmanship.\n");
   set_ac(24);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,720);
   add_prop(OBJ_I_VOLUME,4000);
   add_prop(OBJ_I_WEIGHT,4000);
}
