/* 
 * /d/Kalad/common/wild/pass/wep/rt_ozclub.c
 * Purpose    : A large wooden club
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
   set_adj("rotten");
   add_adj("wooden");
   set_long("A large club the size of a partricularly massive branch, "+
      "it shows signs of severe deterioration, not from exposure to the "+
      "elements, but from exposure to termites.\n");
   set_hit(15);
   set_pen(9);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,100);
   add_prop(OBJ_I_WEIGHT,25000);
   add_prop(OBJ_I_VOLUME,25000);
}
