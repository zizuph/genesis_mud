/*
 *  /d/Emerald/blackwall/delrimmon/obj/wep/shad_axe.c
 *
 *  This is one of the weapons from the very old Emerald domain. I
 *  have included it in a list of such weapons which are wielded at
 *  random by the orc captain in the caves at Del Rimmon. I figure
 *  that these weapons, while pretty lame, will warm a few old players
 *  hearts, and that isn't such a bad thing.
 *
 *  Resurrected by Gorboth - Fall 2001. Original Coder unknown.
 *
 *  Minor code fixes done, but a more significant cleanup is needed
 *  - Shiva Sept. 12 2003
 */
inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Emerald/defs.h"

/* defines */
#define  CAP(x)        capitalize(x)

/* prototypes */
public mixed       steal_check();




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
   add_prop(OBJ_M_NO_STEAL, steal_check);
   add_prop(MAGIC_AM_ID_INFO, ({ 
        "This axe is fairly magical which you can feel "+
        "through your hand. It has an ability to cause great damage in "+
	"battle and would drain the mana of the wielder when doing so.\n", 100,
        "This magical axe can cause special damage "+
        "in battle by releasing magical power onto the opponent. This "+
        "power comes at an expense, it drains the magical powers of the "+
	"user.\n", 80,
        "The axe can deliver great damage in battle "+
        "but at the cost of the mental health of the wielder.\n", 60,
        "Death swings with this double headed axe. "+
        "You can feel the very power it exhibits pulsing through the "+
	"blade whilst you are holding it.\n", 40,
        "This extremely magical axe is a work of art. "+
        "It can release extreme energies in battle but the wielders "+
        "invariably feel drained afterwards.\n", 20 }));

   add_prop(OBJ_S_WIZINFO, 
       "This magical axe is one of the weapons from the Emerald legacy"
     + " of old. I have included many of these weapons to be wielded at"
     + " random by the orc captain in the Del Rimmon area of Emerald."
     + " They aren't particularly brilliant, but I figure this will warm"
     + " the hearts of a few of the remaining old players.\n");
}

string
desc()
{
   return break_string("A pulsating energy glides through this "+
        "blackened weapon, its shadowy blades whispering with an inner "+
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

/* Filter the people without see_blood, so they dont see the special hits 
*/
static void
tell_watcher(string str, object enemy)
{
    query_wielded()->tell_watcher(str, enemy);
}

/* After we tried to hit something this function is called with the result. 
*/
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{
    object blind;
    int ran;
    object wielder;
    wielder = query_wielded();

    ran = random(12);

    if (phurt == -1 || phurt == -2)
    {
        wielder->catch_msg("Shadows seem to engulf "+ 
           enemy->query_the_name(wielder)+ " as your axe swings close by "+
           POS(enemy)+" body.\n");
        enemy->catch_msg("You can see shadows extend from "+
           wielder->query_the_possessive_name(enemy) +
           " axe as it swings close to you.\n");
        tell_watcher("Dark shadows seem to extend from "+
           QTPNAME(wielder)+" axe as it nearly hits "+QTNAME(enemy)+
           ".\n", enemy);
        return 0;
    }
    if (phurt == 0)
    {
        wielder->catch_msg("Power surges into your hands as your "+
           "axe closely misses "+ enemy->query_the_name(wielder)+".\n");
        enemy->catch_msg(wielder->query_the_possessive_name(enemy)+
           " axe narrowly misses you. You hear a crackling of energy.\n");
        tell_watcher("A crackling of energy accompanies a narrow miss "+
           "from "+QTPNAME(wielder)+" axe.\n",enemy);
    }
    else
    {
        if(ran == 1)
        {
           wielder->catch_msg(enemy->query_The_name(wielder)+
              " staggers backwards as your axe bites deep and hard.\n");
           enemy->catch_msg("You stagger backwards as "+
                wielder->query_the_possessive_name(enemy)+
                " axe bites deep and hard.\n");
           tell_watcher(QCTPNAME(wielder)+" shadow axe bites "+
                "deep into "+QTNAME(enemy)+" pushing "+OBJ(enemy)+
                " backwards.\n", enemy);
           enemy->heal_hp(min(0, -(150 + (wielder->query_skill(SS_SPELLCRAFT)) -
                (enemy->query_skill(SS_ELEMENT_LIFE)) + 
                (wielder->query_stat(SS_STR) / 2))));
           enemy->command("$scream");
   /* The element of life is required here because the axe is taking life */
   /* from the enemy. Any other element would be useless.                 */
           if(enemy->query_hp() <= 0)
                enemy->do_die(wielder);
           wielder->add_mana(-30);
   /* Instead of having to recharge the weapon, it will take away 30 mana */
   /* on each hit, which would make some people think twice about using   */
   /* it.                                                                 */
           return 1;
        }
        if (ran == 2)
        {
           wielder->catch_msg("The axe shudders as you hit into "+
                enemy->query_the_possessive_name(wielder)+" body. "+
                CAP(PRON(enemy))+" seems shocked.\n");
           enemy->catch_msg("You are slightly stunned as "+
                wielder->query_the_name(enemy)+"'s axe slams into you.\n");
           tell_watcher(QCTPNAME(wielder)+" shadow axe shudders "+
                "as it slams into "+QTNAME(enemy)+".\n",enemy);
           enemy->add_attack_delay(MIN(5, (wielder->
                    query_skill(SS_WEP_AXE) / 20)));
   /* This part adds an attack delay which is a minimum of the axe skill */
   /* divided by 20 or 5 (in heartbeats). The player will pay 30 mana    */
   /* this attack just as the one above.                                 */
           wielder->add_mana(-30);
           if(enemy->query_hp() <= 0)
                enemy->do_die(wielder);
           return 1;
        }
        return 0;
    }
}


/*
 * Function name:        steal_check
 * Description  :        this sword cannot be stolen from Akugla
 * Returns      :        string - can't steal msg, 0 - can steal
 */
public mixed
steal_check()
{
    if (environment(this_object())->id("del_rimmon_akugla"))
    {
        return "As you reach for the weapon, the fearsome orc"
          + " captain turns upon you and, with a single glance,"
          + " stops you cold.\n";
    }

    return 0;
} /* steal_check */

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}
