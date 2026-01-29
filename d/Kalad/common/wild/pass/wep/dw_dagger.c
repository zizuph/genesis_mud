/* 
 * /d/Kalad/common/wild/pass/wep/dw_dagger.c
 * Purpose    : An adamantine dagger of drow make
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
   set_name("dagger");
   add_name("drowwep");
   set_adj("adamantine");
   add_adj("long");
   set_long("A dagger made out of pure adamantine, the most enduring "+
      "metal known to exist. The weapon's incredible beauty, matched with "+
      "its obviously deadly purpose leads you to believe it was crafted by "+
      "the sinister drow, for only they possess the ability to meld beauty "+
      "with death.\n");
   set_hit(13);
   set_pen(14);
   set_wt(W_KNIFE);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,500);
   add_prop(OBJ_I_WEIGHT,1500);
   add_prop(OBJ_I_VOLUME,1500);
}
