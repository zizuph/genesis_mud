/* 
 * /d/Kalad/common/wild/pass/giantpass/wep/gcclub.c
 * Purpose    : A giant club of iron, very HEAVY!
 * Located    : Used by the giants in the redwoodforest
 * Created By : Antharanos  ??.??.??
 * Modified By: Meton 2020
 * First Modif: 
 */ 

inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("club");
   set_adj("enormous");
   add_adj("iron");
   set_long("An enormous club forged from pig iron. The club looks positively "+
      "huge with its six foot circumference. It must weigh at least a ton!\n");
   set_hands(W_BOTH);
   set_hit(30);
   set_pen(45);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_VALUE,1500);
   add_prop(OBJ_I_WEIGHT,125000);
   add_prop(OBJ_I_VOLUME,75000);
}
