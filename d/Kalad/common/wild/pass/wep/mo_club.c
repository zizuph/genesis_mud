/* 
 * /d/Kalad/common/wild/pass/wep/mo_club.c
 * Purpose    : A stone club
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
   set_adj("giant");
   add_adj("stone");
   set_long("Nothing more than a large stalagmite, or perhaps stalactite "+
      "that has been snapped off and is now used as a weapon of mutilation.\n");
   set_hit(15);
   set_pen(27);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,375);
   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,10000);
}
