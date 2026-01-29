/* Stephen MarKenin, Knight of the Crown by Morrigan
Made to defend the helpless and innocent bard that
is being killed by undesirables in the Keep. He
comes upon Celeste being attacked, and leaves when
she is safe once again. *grin*
10/12/96
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
   
   set_name("stephen");
   set_living_name("stephen");
   set_race_name("Solamnian");
   set_title("MarKenin, the Knight of the Crown");
   set_gender(0);
   set_introduce(1);
   set_long("This young, but stern, looking man is a "+set_my_title()+
      ". His moustache, though not as grand as many, is impressive. "+
      "His armour is resplendant, and he is apparently from a wealthy "+
      "family. Golden brown hair flows over his shoulders, and cool "+
      "hawkish green eyes study the surroundings intently.\n"+
      "He is a "+subtitle+".\n");
   set_stats(({180, 180, 180, 140, 140, 140}));
   set_adj("young");
   add_adj("stern");
   set_act_time(3);
   add_act("@@name_attacker");
   set_alignment(800);
   set_knight_prestige(-500);
   set_skill(67533, 100);
   set_skill(SS_WEP_SWORD, 100);
   set_skill(SS_PARRY, 90);
   set_skill(SS_DEFENCE, 70);
   set_skill(SS_AWARENESS, 75);
   set_skill(SS_2H_COMBAT, 90);
   add_prop(NPC_I_NO_RUN_AWAY, 1);
   MONEY_MAKE_GC(random(15) + 5)->move(TO);
   soul_id = set_alarm(0.5, 0.0, &get_me_soul());
   set_alarm(1.0,0.0,"arm_me");
   set_alarm(3.0, 0.0, "defend_celeste");
   trig_new("%w 'fail' %s", "retry_rescue");
   trig_new("%w 'attacks' %s", "rescue_celeste");
}

string
name_attacker()
{
   if (!attacker)
      return "say I am here to protect the fair Celeste from any "+
   "that may do her harm.";
   else
      return "say It's a good thing I was here to defend Celeste from that "+
   "cowardly "+attacker->query_nonmet_name()+".";
}

void
get_me_soul()
{
   TO->add_cmdsoul("/d/Krynn/solamn/guild/obj/solamnian_soul");
   TO->update_hooks();
   remove_alarm(soul_id);
}

void
rescue_celeste()
{
   set_alarm(2.0, 0.0, "command","rescue celeste");
   set_alarm(2.5, 0.0, "define_attacker");
   set_alarm(3.0, 0.0, "do_block");
}

define_attacker()
{
   attacker = TO->query_attack();
}

retry_rescue()
{
   set_alarm(1.0, 0.0, "command", "rescue celeste");
}

void
defend_celeste()
{
   command("emote comes running into the room!");
   command("kassist celeste");
   set_alarm(1.0, 0.0, "command", "rescue celeste");
   set_alarm(2.0, 0.0, "define_attacker");
   set_alarm(3.0, 0.0, "command", "say Attacking a defenseless one "+
      "such as this lady is inexcusable! You have thrown away the "+
      "defence afforded you by the Measure, and shall be dealt with "+
      "accordingly.");
   set_alarm(3.5, 0.0, "do_block");
}
do_block()
{
   attacker = TO->query_attack();
   if (attacker->query_average_stat() >= 120)
      command("block south");
}

void
arm_me()
{
   seteuid(geteuid(this_object()));
   clone_object("/d/Krynn/solamn/palan/obj/sol_sword")->move(TO);
   clone_object("/d/Krynn/solamn/palan/obj/sol_armour")->move(TO);
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

