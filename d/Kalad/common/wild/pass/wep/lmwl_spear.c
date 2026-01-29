/* 
 * /d/Kalad/common/wild/pass/wep/lmwl_spear.c
 * Purpose    : A strong spear that is poisoned. Poison can be used once
 * Located    : Used by the lizard men in the desert
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
int poison_used;
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("spear");
   set_adj("sharpened");
   add_adj("steel-tipped");
   set_long("@@long_desc");
   set_hit(23);
   set_pen(16);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE,210);
   add_prop(OBJ_I_WEIGHT,4500);
   add_prop(OBJ_I_VOLUME,4500);
   poison_used = 0;
}
string
long_desc()
{
   if(poison_used)
      return "A sturdy wooden shaft, with an extremely sharp steel head at "+
   "its tip.\n";
   else
      return "A sturdy wooden shaft, with an extremely sharp steel head at "+
   "its tip. A thin sheen of liquid is visible on the spear head.\n";
}
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   if(!poison_used && !random(6))
      {
      poison = clone_object("/std/poison_effect");
      if(poison)
         {
         if(random(3))
            poison_used = 1;
         poison -> move(enemy);
         poison -> set_time(100);
         poison -> set_interval(25);
         poison -> set_strength(100);
         poison -> set_damage(({POISON_FATIGUE, 200, POISON_STAT, SS_CON}));
         poison -> start_poison();
         return 0;
      }
      else
         write("Failed to load poison for some reason.\n");
   }
   return 0;
}
