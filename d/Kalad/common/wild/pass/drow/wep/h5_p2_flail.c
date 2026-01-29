inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
int poison_used;
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("flail");
   set_adj("great");
   add_adj("three-headed");
   add_adj("adamantine");
   set_long("@@long_desc");
   set_hit(20);
   set_pen(15);
   set_wf(TO);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(OBJ_S_WIZINFO,"This flail, found on the Priestess of House "+
      "Kilsek in the drow city of Undraeth (/d/Kalad/common/wild/pass/drow/npc/h5_priest2) "+
      "will, if wielded by a female with a wisdom over 99, have its hit/pen "+
      "increased from its normal 20/15 to 40/33. Resultantly, when the "+
      "is not wielded or is wielded by someone that doesn't meet the above "+
      "requirements, it will only have its normal hit/pen. Anyone failing "+
      "to wield the flail will be shocked for 500 hp of damage.\n");
   add_prop(MAGIC_AM_ID_INFO,({"The flail is magical.\n", 5,
            "The flail's aura indicates something concerning gender and wisdom.\n", 25,
            "Only those of the greater sex and greater wisdom may gain full "+
            "use of the flail's benefits.\n", 51}));
   add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
   add_prop(OBJ_I_VALUE,1500);
   add_prop(OBJ_I_WEIGHT,10000);
   add_prop(OBJ_I_VOLUME,10000);
   add_prop(OBJ_M_NO_BUY,1);
   poison_used = 0;
}
string
long_desc()
{
   if(poison_used)
      return "A huge three-headed flail, forged from pure adamantine, "+
   "the most powerful metal known. Intricate carvings of the Spider Queen, "+
   "Lolth, have been etched into the flail's handle.\n";
   else
      return "A huge three-headed flail, forged from pure adamantine, "+
   "the most powerful metal known. Intricate carvings of the Spider Queen, "+
   "Lolth, have been etched into the flail's handle. A colorless liquid "+
   "coats the three heads of the flail.\n";
}
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   if(!poison_used && !random(6))
      {
       seteuid(getuid());
      poison = clone_object("/std/poison_effect");
      if(poison)
         {
         if(random(3))
            poison_used = 1;
         poison -> move(enemy);
         poison -> set_time(400);
         poison -> set_interval(50);
         poison -> set_strength(200);
         poison -> set_damage(({POISON_FATIGUE, 200, POISON_STAT, SS_CON}));
         poison -> start_poison();
         return 0;
      }
      else
         write("Failed to load poison for some reason.\n");
   }
   return 0;
}
mixed
wield(object what)
{
   if(TP->query_gender() == 1)
      if(TP->query_base_stat(SS_WIS) > 99)
      {
      write("The great three-headed adamantine flail briefly glows with "+
         "a red light.\n");
      say(QCTNAME(TP) + "'s great three-headed adamantine flail briefly "+
         "glows red.\n");
      what -> set_hit(40);
      what -> set_pen(33);
      E(TO)->update_weapon(TO);
      return 0;
   }
   write("The great three-headed adamantine flail glows red-hot and "+
      "burns you painfully!\n");
   say(QCTNAME(TP) + " is painfully burned by the great three-headed "+
      "adamantine flail.\n");
   TP->heal_hp(-500);
   if(TP->query_hp() <= 0)
      TP->do_die(TO);
   what -> set_hit(20);
   what -> set_pen(15);
   E(TO)->update_weapon(TO);
   return 0;
}
mixed
unwield(object what)
{
   what -> set_hit(20);
   what -> set_pen(15);
   E(TO)->update_weapon(TO);
   return 0;
}
