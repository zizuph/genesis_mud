/* 
 * /d/Kalad/common/wild/pass/giantpass/wep/gclub.c
 * Purpose    : A giant club made of wood, its HEAVY!
 * Located    : Used by the giants in the redwood forest
 * Created By : Antharanos  ??.??.??
 * Modified By: Meton 2020
 * First Modif: 
 */ 

inherit "/d/Kalad/std/weapon.c";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("club");
   set_adj("enormous");
   add_adj("redwood");
   set_long("A massive club carved from the trunk of a great redwood "+
      "tree. The club looks to be six feet in circumference! It must weigh "+
      "a ton!\n");
   set_hands(W_BOTH);
   set_hit(20);
   set_pen(30);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,900);
   add_prop(OBJ_I_WEIGHT,100000);
   add_prop(OBJ_I_VOLUME,75000);
}
