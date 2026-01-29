inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <formulas.h>
int poison_used;
create_weapon()
{
   ::create_weapon();
   set_name(({"dagger","_penance_dagger1"}));
   set_adj("wicked");
   set_long("@@long_desc");
   set_hit(15);
   set_pen(30);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE);
   set_wf(TO);
   poison_used = 0;
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
   add_prop(OBJ_S_WIZINFO,"This is a very powerful dagger that is "
      +"blessed with an increased pen, but has a normal hit. It "
      +"also has a very potent poison present in the blade. Due "
      +"to these bonuses, a plyer must have an SS_KNIFE of 65, "
      +"a CON of 80, and a DEX of 100 or else the players panic "
      +"is increased.\n");
   add_prop(MAGIC_AM_ID_INFO,({"This weapon seems to have a very "
            +"sharp and enchanted tip, it could probably do a lot of "
            +"damage. It also secretes a deadly poison.\n", 55}));
}
string
long_desc()
{
   if(poison_used)
      return "A large dagger with a viciously curved blade.\n";
   else
      return "A large dagger with a viciously curved blade. There is a thin "+
   "coating of liquid on the blade.\n";
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   object poison;
   ::did_hit(aid, hdesc, phurt, enemy, dt, phit);

   if(!poison_used && !random(5))
   {
    setuid();
	seteuid(getuid());

	poison = clone_object("/std/poison_effect");
      if(poison) {
         if(random(2))
            poison_used = 1;
         poison->move(enemy);
         poison->set_time(1000);
         poison->set_interval(10);
         poison->set_strength(75);
         poison->set_damage(({POISON_MANA, 200, POISON_STAT, SS_STR}));
         poison->start_poison();
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
   if(this_player()->query_skill(SS_WEP_KNIFE) > 49)
      if (TP->query_base_stat(SS_CON) > 80)
      if (TP->query_base_stat(SS_DEX) > 100)
      {
      write("You manage to harness the dagger's power.\n");
      return 0;
   }
   TP->add_panic(random(100)-5);
   return "The dagger is too much for you to handle.\n";
}
