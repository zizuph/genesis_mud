/* 
 * /d/Kalad/common/wild/pass/wep/sg_club.c
 * Purpose    : A giant stone club thats HEAVY!
 * Located    : Used by giants
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("club");
   set_adj("large");
   add_adj("stone");
   set_long("A gigantic club chiselled from solid stone. Its "+
      "circumference is greater than six feet in length. Clearly, only the "+
      "strongest of individuals are capable of wielding it.\n");
   set_hands(W_BOTH);
   set_hit(18);
   set_pen(12);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,1000);
   add_prop(OBJ_I_WEIGHT,125000);
   add_prop(OBJ_I_VOLUME,100000);
}
