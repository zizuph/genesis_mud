inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
int poison_used;
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("halberd");
   set_adj("grey");
   add_adj("adamantine");
   set_long("@@long_desc");
   set_hit(24);
   set_pen(38);
   set_hands(W_BOTH);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE | W_SLASH);
   add_prop(OBJ_I_VALUE,700);
   add_prop(OBJ_I_WEIGHT,7000);
   add_prop(OBJ_I_VOLUME,7000);
   poison_used = 0;
}
string
long_desc()
{
   if(poison_used)
      return "A fine piece of drow craftsmanship. The halberd, fashioned "+
   "from adamantine metal, is truly a work of art.\n";
   else
      return "A fine piece of drow craftsmanship. The halberd, fashioned "+
   "from adamantine metal, is truly a work of art. Upon its blade is a "+
   "thin sheen of liquid.\n";
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
         poison -> set_damage(({POISON_HP, 200, POISON_STAT, SS_CON}));
         poison -> start_poison();
         return 0;
      }
      else
         write("Failed to load poison for some reason.\n");
   }
   return 0;
}
