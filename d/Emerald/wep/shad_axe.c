inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include "default.h"

void
create_weapon()
{
   set_name("axe");
   add_name("shadow_axe");
   set_short("shadow axe");
   set_long("@@desc");
   add_item("handle","The hardwood handle is heavily roped with calfskin "+
	"leather to improve the grip.\n");
   add_item(({"leather","calfskin leather"}),"The leather appears to be "+
	"quite well used.\n");
   set_adj("shadow");
   
/* This weapon is extremely heavy and so the pen value is larger than   */
/* the hit value since it's fairly easy to hit but the hit itself will  */
/* _hurt_ a lot.                                                        */
   set_default_weapon(36, 49, W_AXE, W_BLUDGEON, W_ANYH, this_object());
   add_prop(OBJ_I_WEIGHT, 17163); 
   add_prop(OBJ_I_VOLUME,  1981); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(36, 49) + random(278) + 291);

   add_prop(MAGIC_AM_MAGIC, ({ 75, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({ 
        ({ 100, break_string("This axe is fairly magical which you can feel "+
        "through your hand. It has an ability to cause great damage in "+
        "battle and would drain the mana of the wielder when doing so.\n", 76) }),
        ({ 80, break_string("This magical axe can cause special damage "+
        "in battle by releasing magical power onto the opponent. This "+
	"power comes at an expense, it drains the magical powers of the "+
	"user.\n", 76) }),
        ({ 60, break_string("The axe can deliver great damage in battle "+
        "but at the cost of the mental health of the wielder.\n", 76) }),
        ({ 40, break_string("Death swings with this double headed axe. "+
        "You can feel the very power it exhibits pulsing through the "+
        "blade whilst you are holding it.\n", 76) }),
        ({ 20, break_string("This extremely magical axe is a work of art. "+
        "It can release extreme energies in battle but the wielders "+
	"invariably feel drained afterwards.\n", 76) }), })
 	);
   add_prop(OBJ_S_WIZINFO, break_string("This is the magical axe that the "+
	"licheking guards in the castle north of Telberin at "+
	"/d/Emerald/room/castle/r14. The liche is reincarnated as a wraith "+
	"when he dies so the players must kill two monsters to get at the "+
	"axe which is in the room beyond. They must also have a high "+
	"awareness skill to find the axe which is hidden amongst the "+
	"piles of rubbish.\n", 76));
}

string
desc()
{
   return break_string("A pulsating energy glides through this "+
	"blackened weapon, it's shadowy blades whispering with an inner "+
	"power that beckons you into it. The handle is decorated in "+
	"calf skin leather extending to the blade itself.\n", 76);
}

int
wield(object wep)
{
   if(this_player()->query_skill(SS_WEP_AXE) < 60)
   {
      write("The blade is too powerful for you to wield.\n");
      TP->heal_hp(-50);
      if(TP->query_hp() <= 0)
        TP->do_die(this_object());
      return -1;
   }
   if(TP->resolve_task(TASK_ROUTINE, ({ TS_INT, SS_SPELLCRAFT})) < 0)
   {
      write("The coldness is too much for you handle.\n");
      TP->heal_hp(-60);
      if(TP->query_hp() <= 0)
        TP->do_die(this_object());
      return -1;
   }
   return 0;
}

string
query_recover()
{
   return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
   init_wep_recover(arg);
}

int
try_hit(object ob) 
{
   return 1; 
}

/* Filter the people without see_blood, so they dont see the special hits 
*/
static void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

/* After we tried to hit something this function is called with the result. 
*/
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    object blind;
    int ran;

    ran = random(12);

    if (phurt == -1)
    {
        query_wielded()->catch_msg("Shadows seem to engulf "+QTNAME(enemy)+
	   " as your axe swings close by "+POS(enemy)+" body.\n");
        enemy->catch_msg("You can see shadows extend from "+
	   QTNAME(query_wielded())+"'s axe as it swings close to you.\n");
        tell_watcher("Dark shadows seem to extend from "+
	   QTNAME(query_wielded())+"'s axe as it nearly hits "+QTNAME(enemy)+
	   ".\n", enemy);
        return 0;
    }
    if (phurt == 0)
    {
        query_wielded()->catch_msg("Power surges into your hands as your "+
	   "axe closely misses "+QTNAME(enemy)+".\n");
        enemy->catch_msg(QCTNAME(query_wielded())+"'s axe narrowly misses "+
	   "you. You hear a crackling of energy.\n");
        tell_watcher("A crackling of energy accompanies a narrow miss "+
	   "from "+QTNAME(query_wielded())+"'s axe.\n",enemy);
    }
    else
    {
        if(ran == 1)
        {
           query_wielded()->catch_msg(QCTNAME(enemy)+" staggers backwards "+
	      "as your axe bites deep and hard.\n");
           enemy->catch_msg("You stagger backwards as "+
		QCTNAME(query_wielded())+"'s axe bites deep and hard.\n");
           tell_watcher(QCTNAME(query_wielded())+"'s shadow axe bites "+
		"deep into "+QTNAME(enemy)+" pushing "+POS(enemy)+
		" backwards.\n", enemy);
           enemy->heal_hp(250 + (query_wielded()->query_skill(SS_SPELLCRAFT)) -
                (enemy->query_skill(SS_ELEMENT_LIFE)) + 
                (query_wielded()->query_stat(SS_STR)));
	   enemy->command("scream");
   /* The element of life is required here because the axe is taking life */
   /* from the enemy. Any other element would be useless.		  */
           if(enemy->query_hp() <= 0)
                enemy->do_die(query_wielded());
 	   query_wielded()->add_mana(-30);
   /* Instead of having to recharge the weapon, it will take away 30 mana */
   /* on each hit, which would make some people think twice about using   */
   /* it.								  */
           return 1;
        }
        if (ran == 2)
        {
           query_wielded()->catch_msg("The axe shudders as you hit into "+
		QTNAME(enemy)+"'s body. "+CAP(POS(enemy))+" seems shocked.\n");
           enemy->catch_msg("You are slightly stunned as "+
		QCTNAME(query_wielded())+"'s axe slams into you.\n");
           tell_watcher(QCTNAME(query_wielded())+"'s shadow axe shudders "+
		"as it slams into "+QTNAME(enemy)+".\n",enemy);
	   enemy->add_attack_delay(MIN(5, (query_wielded()->
		    query_skill(SS_WEP_AXE) / 20)));
   /* This part adds an attack delay which is a minimum of the axe skill */
   /* divided by 20 or 5 (in heartbeats). The player will pay 30 mana    */
   /* this attack just as the one above.				 */
  	   enemy->add_mana(-30);
           if(enemy->query_hp() <= 0)
                enemy->do_die(query_wielded());
           return 1;
        }
        return 0;
    }
}

