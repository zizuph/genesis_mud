/* 
 * /d/Kalad/common/wild/pass/wep/rt_gzclub.c
 * Purpose    : A large wooden club.
 * Located    : Used by some creature in the pass?
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
   add_adj("rotten");
   add_adj("wooden");
   set_long("A massive club the size of a small tree, it show signs of "+
      "severe deterioration, not from exposure to the elements, but from exposure "+
      "to termites.\n");
   set_hit(19);
   set_pen(8);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,100);
   add_prop(OBJ_I_WEIGHT,50000);
   add_prop(OBJ_I_VOLUME,50000);
}
