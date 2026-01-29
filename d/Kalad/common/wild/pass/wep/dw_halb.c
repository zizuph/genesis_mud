/* 
 * /d/Kalad/common/wild/pass/wep/dw_halb.c
 * Purpose    : An adamantine halberd of drow make
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
   set_name("halberd");
   add_name("drowwep");
   set_adj("adamantine");
   set_long("This weapon is crafted from an alloy of adamantite, "+
      "adamantine. Its long, cruel blade is easily the size of a small "+
      "shield and practically glows with power. The shaft looks specifically "+
      "molded for the hands of drow, so fine and light weight is it.\n");
   set_hit(26);
   set_pen(35);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE | W_SLASH);
   add_prop(OBJ_I_VALUE, 1000);
   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,10000);
}
