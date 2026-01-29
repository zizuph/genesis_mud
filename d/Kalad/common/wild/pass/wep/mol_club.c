/* 
 * /d/Kalad/common/wild/pass/wep/mol_club.c
 * Purpose    : A large stone club.
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
   set_adj("enormous");
   add_adj("stone");
   set_long("A large stalagmite or stalactite that has been snapped "+
      "off and is now used as a crude, but effective club.\n");
   set_hit(15);
   set_pen(20);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,380);
   add_prop(OBJ_I_WEIGHT, 25000);
   add_prop(OBJ_I_VOLUME,12000);
}
