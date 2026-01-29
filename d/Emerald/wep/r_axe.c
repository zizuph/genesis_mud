inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include "default.h"

int smeared;   /* Int for the smearing of corpses for their power.    */
int power_on;  /* Int for the regeneration of the power on the Axe. */

void
create_weapon()
{
   set_name("axe");
   add_name("runed axe");
   set_short("runed axe");
   set_long("@@desc");
   add_item("surface","The surface is covered in a myriad of tiny runes "+
        "which make no sense at all\nto you.\n");
   set_adj("runed");
   
/* This weapon is extremely heavy and so the pen value is larger than   */
/* the hit value since it's fairly easy to hit but the hit itself will  */
/* _hurt_ a lot.                                                        */
   set_default_weapon(33, 44, W_AXE, W_BLUDGEON, W_ANYH,  this_object());
   add_prop(OBJ_I_WEIGHT, 15163); 
   add_prop(OBJ_I_VOLUME,  1981); 
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(33, 44) + random(321) + 198);

   add_prop(MAGIC_AM_MAGIC, ({ 65, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO, ({ 
        ({ 100, break_string("This axe is fairly magical which you can feel "+
        "through your hand. It has an ability to cause great damage in "+
        "battle and can only release it's power once until recharged. "+
        "To recharge the weapon 'smear blade' or 'smear axe' should work "+
        "fine which needs to be performed 6 times.\n", 76) }),
        ({ 80, break_string("This magical axe can cause special damage "+
        "in battle by releasing magical power onto the opponent. To "+
        "get the power back once must smear the blade with blood from "+
        "a corpse.\n", 76) }),
        ({ 60, break_string("The axe can deliver great damage in battle "+
        "but only once until recharged with the magical powers it "+
        "harnesses. To get the powers back the blood of dead enemies "+
        "must be smeared onto the blade.\n", 76) }),
        ({ 40, break_string("Death swings with this double headed axe. "+
        "You can feel the very power it exhibits pulsing through the "+
        "blade whilst you are holding it. It can be recharged by smearing "+
        "blood onto the blade.\n", 76) }),
        ({ 20, break_string("This extremely magical axe is a work of art. "+
        "It can release extreme energies in battle and must feed off the "+
        "blood of the dead.\n", 76) }), })
        );
   add_prop(OBJ_S_WIZINFO, break_string("This is the runed axe of the "+
        "Emerald mines found on the warlord, at /d/Emerald/room/mine/maze6"+
        " where the warlord resides. It has a special attack, hitting "+
        "extremely hard but it can only be performed once until it is "+
        "recharged by 'smear blade' or 'smear axe' using corpses which are "+
        "farirly easy to get hold of.\n", 76));

   power_on = 1;
   smeared = 0;
}

string
desc()
{
   string extra_str;

   if(power_on)
        extra_str = " The runes glow a strange colour of blue.";
   else
        extra_str = " ";
   return break_string("This heavy axe feels remarkably light in your "+
        "expert hands, it's leather covered handle seeming to grip to "+
        "your hands. The two blades of the axe look wicked with the "+
        "light sparkling in it's reflection, illuminating the runes "+
        "a little."+extra_str+"\n", 76);
}

int
wield(object wep)
{
   if(this_player()->query_skill(SS_WEP_AXE) < 60)
   {
      write("The blade is too heavy for you to wield.\n");
      TP->heal_hp(-50);
      if(TP->query_hp() <= 0)
        TP->do_die(this_object());
      return -1;
   }
   if(TP->resolve_task(TASK_ROUTINE, ({ TS_INT, SS_SPELLCRAFT})) < 0)
   {
      write("The weapon stuns you with static!\n");
      TP->heal_hp(-60);
      if(TP->query_hp() <= 0)
        TP->do_die(this_object());
      return -1;
   }
   return 0;
}

void
init()
{
   ::init();
   add_action("do_smear","smear");
}

int
do_smear(string str)
{
   object corpse, *items;
   int i;

   NF("Smear what?\n");
   if(!strlen(str))
        return 0;

   NF("Smear what?\n");
   if(str != "axe" && str != "blade")
        return 0;

   corpse = present("corpse", ENV(query_wielded()));

   NF("There is no corpse here!\n");
   if(!corpse)
	return 0; 

   write("You rip the corpse apart thoroughly smearing the blade with "+
        "blood.\n");
   say(QCTNAME(query_wielded())+" smears "+POS(query_wielded())+
        " runed axe with blood from the corpse.\nThere is nothing left "+
        "of the corpse.\n", query_wielded());
   items = all_inventory(corpse);
   for (i=0 ; i<sizeof(items) ; i++) {
      if (items[i]) {
         items[i]->move(environment(corpse));
        }
   }
   corpse->remove_object();
   if(smeared <= 6) 
         smeared++;
   else {
         smeared = 0;
         power_on = 1;
   }
   return 1;
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
        query_wielded()->catch_msg("The axe swings so close to "+
           QCTNAME(enemy)+"'s head that "+enemy->query_pronoun()+" gulps "+
                "in fright.\n");
        enemy->catch_msg("The axe swings so close to your head that "+
           "you gulp in fright.\n");
        tell_watcher(QCTNAME(query_wielded())+"'s axe swings so close to "+
           QCTNAME(enemy)+"'s head that "+QCTNAME(enemy)+" gulps in "+
           "fright.\n", enemy);
        return 0;
    }
    if (phurt == 0)
    {
        query_wielded()->catch_msg("You grin evilly as your feel your axe "+
           "thump solidly into " + QTNAME(enemy) + ".\n");
        enemy->catch_msg(QCTNAME(query_wielded())+"'s axe thumps solidly "+
           "into you.\n");
        tell_watcher(QCTNAME(query_wielded())+" grins evilly as "+
           POS(query_wielded())+" axe thumps solidly into "+QTNAME(enemy)
           +".\n",enemy);
    }
    else
    {
        if(ran == 1 && power_on)
        {
           query_wielded()->catch_msg("The runed axe discharges a blast "+
                "of static as it gouges deeply into "+QCTNAME(enemy)+".\n");
           enemy->catch_msg("A blast of static rips into you from the "+
                "runed axe.\n");
           tell_watcher(QCTNAME(query_wielded())+"'s runed axe discharges "+
                "a blast of static as it gouges into "+QTNAME(enemy)+".\n",
enemy);
           enemy->heal_hp(200 + (query_wielded()->query_skill(SS_SPELLCRAFT)) -
                (enemy->query_skill(SS_ELEMENT_AIR)) + 
                (query_wielded()->query_stat(SS_STR)));
           if(enemy->query_hp() <= 0)
                enemy->do_die(query_wielded());
           power_on = 0;
           smeared = 0;
           return 1;
        }
        if (ran == 2 && power_on)
        {
           query_wielded()->catch_msg("Your runed axe warms as it slices "+
                "straight through "+QCTNAME(enemy)+"'s side.\n");
           enemy->catch_msg("You scream as "+QCTNAME(query_wielded())+"'s "+
                "runed axe slices into your side.\n");
           tell_watcher(QCTNAME(query_wielded())+"'s runed axe glows red "+
                "as it slices into "+QCTNAME(enemy)+"'s side.\n",enemy);
           enemy->heal_hp(100 + (query_wielded()->query_skill(SS_SPELLCRAFT)) -
                (enemy->query_skill(SS_ELEMENT_AIR)) +
                (query_wielded()->query_stat(SS_STR)));
           enemy->command("scream");
           if(enemy->query_hp() <= 0)
                enemy->do_die(query_wielded());
           power_on = 0;
           smeared = 0;
           return 1;
        }
        return 0;
    }
}

