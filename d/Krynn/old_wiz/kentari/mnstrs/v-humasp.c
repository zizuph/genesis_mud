/* Material Spirit of Huma Dragonbane, Knight of the Crown
		 by Kentari
Made to defend the vault guard that is being
killed by undesirables in Kentari's vault.
11/26/96
Modified version of Stephen, guard to Celeste of VK.
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/guild/guild.h"
#include "/d/Krynn/solamn/guild/local.h"
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
inherit "/std/act/action";
inherit "/d/Krynn/common/monster/knight_base";
inherit M_FILE

int sublevel, level, soul_id;
string subtitle, title;
void get_me_soul();
object attacker;

string
set_my_title()
{
   level = 3;
   sublevel = 10;
   subtitle = CROWN_TITLES[sublevel];
   return "Knight of the Crown";
}

create_krynn_monster()
{
   int i;
   
   set_name("huma");
   set_living_name("huma");
   set_race_name("Solamnian-Spirit");
   set_title("Dragonbane, the Knight of the Crown");
   set_gender(0);
   set_introduce(1);
   set_long("This young looking, soft-visaged man is a "+set_my_title()+
      ". His moustache, though not as grand as many, is dignified. "+
      "His armour is fairly plain, though of good make, and you can "+
      "tell that he knows how to use his sword.  With the elite training "+
      "of the Solamnic Knights obvious in his movements, you feel " +
      "wary of rousing his anger.  He seems to possess an inner glow of " +
      "warmth and compassion that gives life to this materialized spirit.\n");
   set_stats(({350, 325, 350, 300, 300, 325}));
   set_adj("holy");
   add_adj("guardian");
   set_act_time(3);
   add_act("@@name_attacker");
   set_alignment(1200);
   set_knight_prestige(-2000);
   set_skill(67533, 100);
   set_skill(SS_WEP_SWORD, 150);
   set_skill(SS_PARRY, 130);
   set_skill(SS_DEFENCE, 120);
   set_skill(SS_AWARENESS, 125);
   set_skill(SS_2H_COMBAT, 100);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   MONEY_MAKE_SC(random(15) + 5)->move(TO);
   soul_id = set_alarm(0.5, 0.0, &get_me_soul());
   set_alarm(1.0,0.0,"arm_me");
   set_alarm(3.0, 0.0, "defend_guard");
   trig_new("%w 'fail' %s", "retry_rescue");
   trig_new("%w 'attacks' %s", "rescue_guard");
}

string
name_attacker()
{
   if (!attacker)
      return "say I am here to protect the guardian of the Vault from any "+
   "that may attempt to cause him harm.";
   else
      return "say It's a good thing I was here to help defend the Vault " +
   "from that mischievous "+attacker->query_nonmet_name()+".";
}

void
get_me_soul()
{
   TO->add_cmdsoul("/d/Krynn/solamn/guild/obj/solamnian_soul");
   TO->update_hooks();
   remove_alarm(soul_id);
}

void
rescue_fizzy()
{
   set_alarm(2.0, 0.0, "command","rescue guard");
   set_alarm(2.5, 0.0, "define_attacker");
   set_alarm(3.0, 0.0, "do_block");
}

define_attacker()
{
   attacker = TO->query_attack();
}

retry_rescue()
{
   set_alarm(1.0, 0.0, "command", "rescue guard");
}

void
defend_guard()
{
   command("emote materializes before you to help defend the Vault!");
   command("kassist guard");
   command("introduce myself");
   set_alarm(1.0, 0.0, "command", "rescue fizzy");
   set_alarm(2.0, 0.0, "define_attacker");
   set_alarm(3.0, 0.0, "command", "say Attacking this dutiful guardian " +
      "for material desires is inexcusable! You have thrown away the "+
      "defence afforded you by the Measure, and shall be dealt with "+
      "accordingly.");
   set_alarm(3.5, 0.0, "do_block");
}
do_block()
{
   attacker = TO->query_attack();
   if (attacker->query_average_stat() >= 100)
      command("block out");
}

void
arm_me()
{
   seteuid(geteuid(this_object()));
   clone_object("/d/Krynn/solamn/palan/obj/sol_sword")->move(TO);
 clone_object("/d/Ansalon/flotsam_forest/obj/armour/vin_armour.c")->move(TO);
   clone_object("/d/Krynn/solamn/palan/obj/sol_boots")->move(TO);
   command("wield swords");
   command("wear armours");
}

/*
This guy has the Knight special attacks bash and ckick, too!
*/

int
do_bash(object enemy)
{
   object  me = this_object();
   mixed *hitresult;
   string  how;
   
   if (E(TO) == E(enemy))
      {
      say(QCTNAME(me) + " looks at " + QTNAME(enemy) + " with murder " +
         "in " + me->query_possessive() + " eyes.\n", enemy);
      enemy->catch_msg(QCTNAME(TO) + " looks at you with murder in " +
         TO->query_possessive() + " eyes.\n");
      
      hitresult = enemy->hit_me(100 + random(150), W_BLUDGEON, me, -1);
      
      enemy->catch_msg(QCTNAME(me)+" sends you sprawling with" +
         " a wonderful bash!\n");
      say(QCTNAME(me)+" sends "+QTNAME(enemy)+" sprawling with" +
         " a wonderful bash!\n",enemy);
      
      if(enemy->query_hp() <=0)
         
      enemy->do_die(me);
      return 1;
   }
}

int
do_ckick(object enemy)
{
   object  me = this_object();
   mixed *hitresult;
   string  how;
   
   if (E(TO) == E(enemy))
      {
      say(QCTNAME(me) + " looks at " + QTNAME(enemy) + " with rage " +
         "in " + me->query_possessive() + " face.\n", enemy);
      enemy->catch_msg(QCTNAME(TO) + " looks at you with rage in " +
         TO->query_possessive() + " face.\n");
      
      hitresult = enemy->hit_me(75 + random(100), W_BLUDGEON, me, -1);
      
      enemy->catch_msg(QCTNAME(me)+" kicks you hard! You can hear" +
         " your bones crunch!\n");
      say(QCTNAME(me)+" kicks "+QTNAME(enemy)+" with a bonecrushing" +
         " sound!\n",enemy);
      
      if(enemy->query_hp() <=0)
         enemy->do_die(me);
      return 1;
   }
}

int
special_attack(object enemy)
{
   int i;
   
   if(random(3))
      return 0;
   
   switch(random(2))
   {
      case 0:
      do_bash(enemy);
      break;
      case 1:
      do_ckick(enemy);
      break;
   }
   return 0;
}

int
query_knight_level() { set_my_title(); return level; }

int
query_knight_sublevel() { return sublevel; }

