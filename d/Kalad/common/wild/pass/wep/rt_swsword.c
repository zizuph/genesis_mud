/* 
 * /d/Kalad/common/wild/pass/wep/rt_swsword.c
 * Purpose    : An ancient iron sword
 * Located    : Used by some ancient creatures in the pass?
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
   set_adj("ancient");
   add_adj("iron");
   set_long("A battered and ancient weapon forged from iron. Worn and faded "+
      "symbols line its dust encrusted pommel, however they appear to be "+
      "of an ancient type, one not used in centuries.\n");
   set_hit(25);
   set_pen(10);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   add_prop(OBJ_I_VALUE,250);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,5000);
}
