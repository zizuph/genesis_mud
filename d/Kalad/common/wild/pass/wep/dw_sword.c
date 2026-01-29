/* 
 * /d/Kalad/common/wild/pass/wep/dw_sword.c
 * Purpose    : An adamantine sword of drow make
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
   set_name("sword");
   add_name("drowwep");
   set_adj("adamantine");
   add_adj("long");
   set_long("A sword fashioned out of pure adamantine, the strongest "+
      "metal known to exist. The almost delicate beauty of this sword, "+
      "coupled with its obvious strength leads you to believe it was "+
      "fashioned by the infamous drow, for only they could create a weapon "+
      "of such beauty and deadly power.\n");
   set_hit(25);
   set_pen(26);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE, 600);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,5000);
}
