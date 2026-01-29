/* 
 * /d/Kalad/common/wild/pass/wep/dw_axe.c
 * Purpose    : An axe made of adamantine, of drow make
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
   set_name("axe");
   add_name("drowwep");
   set_adj("long-hafted");
   add_adj("adamantine");
   set_long("An axe crafted from pure adamantine, the most durable metal "+
      "in existence. The nearly delicate beauty of the weapon betrays its "+
      "drow origins, for only that race could combine such beauty with such "+
      "deadliness.\n");
   set_hit(22);
   set_pen(26);
   set_wt(W_AXE);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,700);
   add_prop(OBJ_I_WEIGHT,7000);
   add_prop(OBJ_I_VOLUME,7000);
}
