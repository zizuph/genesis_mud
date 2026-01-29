/* 
 * /d/Kalad/common/wild/pass/wep/dw_mace.c
 * Purpose    : An adamantine make of drow make
 * Located    : Used by the drows in Undreath
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
   set_name("mace");
   add_name("drowwep");
   set_adj("spiked");
   add_adj("adamantine");
   set_long("This mace is made from an alloy of some alien drow metal. "+
      "The metal is black and has enormous black spikes protruding from its "+
      "cubical head.\n");
   set_hit(25);
   set_pen(20);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON | W_IMPALE);
   add_prop(OBJ_I_VALUE, 600);
   add_prop(OBJ_I_WEIGHT,8000);
   add_prop(OBJ_I_VOLUME,8000);
}
