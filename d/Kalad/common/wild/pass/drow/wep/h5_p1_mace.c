inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
int poison_used;
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   setuid(); seteuid(getuid());
   set_name("mace");
   set_adj("jet-black");
   add_adj("adamantine");
   set_long("@@long_desc");
   set_hit(29);
   set_pen(20);
   set_wf(TO);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(OBJ_S_WIZINFO,"This mace, found on the high priestess of "+
      "House Kilsek in the drow city of Undraeth (/d/Kalad/common/wild/pass/drow/npc/h5_priest1) "+
      "will, if wielded by a female with a wisdom over 119, have its hit/pen "+
      "increased from its normal  29/20 to 38/35. resultantly, when the mace "+
      "isn't wielded or is wielded by anyone not fitting the above requirements, "+
      "it will only have its normal hit/pen. Also, this player will have "+
      "themself shocked for 500hp of damage.\n");
   add_prop(MAGIC_AM_ID_INFO,({"The mace is magical.\n", 5,
            "The mace's aura indicates something concerning gender and wisdom.\n", 25,
            "Only those of the greater sex and greater wisdom may gain full "+
            "use of the mace's benefits.\n", 51}));
   add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
   add_prop(OBJ_I_VALUE,1750);
   add_prop(OBJ_I_WEIGHT,12500);
   add_prop(OBJ_I_VOLUME,12500);
   add_prop(OBJ_M_NO_BUY,1);
   poison_used = 0;
}
string
long_desc()
{
   if(poison_used)
      return "A massive mace crafted from pure adamantine, the most lasting "+
   "and enduring metal known. Its jet-black surface is covered with "+
   "intricate carvings of the Spider Queen, Lolth.\n";
   else
      return "A massive mace crafted from pure adamantine, the most lasting "+
   "and enduring metal known. Its jet-black surface is covered with "+
   "intricate carvings of the Spider Queen, Lolth. A colorless liquid "+
   "coats the head of the mace.\n";
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
         poison -> set_time(600);
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
      if(TP->query_base_stat(SS_WIS) > 119)
      {
      write("The jet-black adamantine mace glows with a soft red light, "+
         "which fades away moments later.\n");
      say(QCTNAME(TP) + "'s jet-black adamantine mace glows with a soft red "+
         "light, which fades away moments later.\n");
      what -> set_hit(38);
      what -> set_pen(35);
   E(TO)->update_weapon(TO);
      return 0;
   }
   write("The jet-black adamantine mace glows red hot and surrounds you "+
      "in a ball of red magical flame!\n");
   say(QCTNAME(TP) + " is suddenly surrounded by a ball of red magical "+
      "flame!\n");
   TP->heal_hp(-500);
   if(TP->query_hp() <= 0)
      TP->do_die(TO);
   what -> set_hit(29);
   what -> set_pen(20);
   E(TO)->update_weapon(TO);
   return 0;
}
mixed
unwield(object what)
{
   what -> set_hit(29);
   what -> set_pen(20);
   E(TO)->update_weapon(TO);
   return 0;
}
