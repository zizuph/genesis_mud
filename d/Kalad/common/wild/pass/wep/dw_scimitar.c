/* 
 * /d/Kalad/common/wild/pass/wep/dw_scimitar.c
 * Purpose    : A scimitar of adamantine drow make
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
   set_name("scimitar");
   add_name("sword");
   add_name("drowwep");
   set_adj("adamantine");
   set_long("An exquisitely crafted scimitar created from pure adamantine, "+
      "the strongest metal known to exist. The elegant beauty of this "+
      "weapon belies its incredible strength and endurance.\n");
   set_hit(30);
   set_pen(21);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   add_prop(OBJ_I_VALUE,600);
   add_prop(OBJ_I_WEIGHT,4500);
   add_prop(OBJ_I_VOLUME,4500);
}
