/* 
 * /d/Kalad/common/wild/pass/wep/bclub.c
 * Purpose    : A large oak club to bonk people with
 * Located    : Used by some ogre
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
   add_adj("wooden");
   set_long("A large club, apparently carved from one of the branches "+
      "of a redwood tree. It looks perfect for bludgeoning someone into "+
      "a fleshy paste.\n");
   set_hit(17);
   set_pen(8);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,300);
   add_prop(OBJ_I_WEIGHT, 2250);
   add_prop(OBJ_I_VOLUME, 2500);
}
