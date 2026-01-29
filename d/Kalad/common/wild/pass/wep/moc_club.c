/* 
 * /d/Kalad/common/wild/pass/wep/moc_club.c
 * Purpose    : A large club of onyx
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
   add_adj("onyx");
   set_long("A large club fashioned out of dark onyx. It looks capable "+
      "of crushing the most heavily armoured of opponents.\n");
   set_hit(25);
   set_pen(21);
   set_hands(W_BOTH);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,400);
   add_prop(OBJ_I_WEIGHT,16000);
   add_prop(OBJ_I_VOLUME,16000);
}
