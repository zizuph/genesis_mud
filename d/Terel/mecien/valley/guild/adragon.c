/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/act/attack";
inherit "/std/act/asking";
inherit "/d/Terel/std/teacher";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO             this_object()
#define TP             this_player()
#define ETO            environment(TO)

#define A_BITE  0
#define A_CLAW  1
#define A_TAIL  2
#define A_HORN  3
#define A_CLAW2 4

#define H_BODY 0
#define H_HEAD 1

void set_up_skills();

public void
create_creature()
{
   set_name("arinosticarus");
   add_name("master");
   add_name("teacher");
   add_name("ancient_dragon");
   set_adj("arcane");
   add_adj("white");
   set_race_name("dragon");
   set_living_name("arinosticarus");

   set_stats(({ 256, 302, 309, 112, 144, 133 }));
   set_skill(SS_FORM_DIVINATION, 100);
   set_skill(SS_ELEMENT_DEATH, 100);
   set_skill(SS_ELEMENT_LIFE, 100);
   set_skill(SS_DEFENCE, 100);

   set_chat_time(75);
   set_act_time(34);

   set_hp(9999);
   set_mana(9999);

   set_aggressive("@@check");
   set_attack_unarmed(A_BITE, 132, 128, W_IMPALE,   75, "jaws");
   set_attack_unarmed(A_CLAW,  92,  70, W_SLASH,    66, "right claw");
   set_attack_unarmed(A_TAIL, 110,  99, W_BLUDGEON, 65, "tail");
   set_attack_unarmed(A_HORN,  73,  78, W_IMPALE,   20, "horns");
   set_attack_unarmed(A_CLAW2, 89,  88, W_SLASH,    70, "left claw");

   set_hitloc_unarmed(H_BODY, ({ 117, 133, 89, 90}), 85, "torso");
   set_hitloc_unarmed(H_HEAD, ({  73,  72, 70, 78}), 15, "head");

   set_alignment(903);
   create_skill_raise();
   set_up_skills();
   add_ask("for signet", "@@signet", 1);

   set_act_time(5);
   add_act("emote stretches out its claws.");
   add_act("emote lets loose a snuff of fiery discharge.");
   add_act("emote gazes all about, searching intently.");
}

aggressive_attack(object ob){
  if(ob->query_alignment() > 100) return 0;

::aggressive_attack(ob);
}

check(){
   if(!query_prop("defending")) return 0;

   return 1;
}

public void
warn2(object who)
{
   if (MEMBER(who)) {
      who->catch_msg(QCTNAME(TO) + " speaks to you with a mystic " +
                     "voice saying: Someone has entered my dominion.\n");
   }
}

public void
warn()
{
   map(users(), warn2);
}

public string
signet()
{
   object sig;

   if (TP->query_mystic_office() != OFFICE_SEAL ||
       present(MYSTIC_SIGNET, TP)) {
       return "emote gets a fierce look in its eyes.";
   }
   seteuid(getuid());
   sig = clone_object(GUILD_DIR + "obj/signet");
   TP->catch_msg("You sense a tingling in your hand.\n");
   if (sig->move(TP)) {
       sig->move(ETO);
       write("You drop " + LANG_ADDART(sig->short()) + ".\n");
       say(QCTNAME(TP) + " drops " + LANG_ADDART(sig->short()) + ".\n");
   }
   return "emote rises up and a mysterious glow emanates from its eyes.";
}

public int
special_attack(object enemy)
{
   mixed *hitresult;
   string how;

   if (random(5)) return 0;

   hitresult = enemy->hit_me(105+random(75), MAGIC_DT, TO, -1);
   how = "misses";
   if (hitresult[0] >  0) how = "singes";
   if (hitresult[0] > 25) how = "burns";
   if (hitresult[0] > 40) how = "engulfs";

   TO->catch_msg("You blast forth fire.\n");
   enemy->catch_msg(QCTNAME(TO) + " " + how +
                    " you with a spout of white fire.\n");
   tell_watcher(QCTNAME(TO) + " spews forth a blast of white fire and " +
                how + " " + QTNAME(enemy) + ".\n", enemy);

   if (enemy->query_hp() <= 0) enemy->do_die(TO);
   return 1;
}

public void
init_living()
{
   ::init_living();
   init_skill_raise();
}


public void
set_up_skills()
{
   string me, ot;

   me = "master the powers of life"; ot = me;
   sk_add_train(SS_ELEMENT_LIFE,  ({me, ot}), 0, 0, MYSTIC_MAX_LIFE);
}

public int
sk_improve(string str)
{
   string name = lower_case(TP->query_name());

   if (!MEMBER(TP)) {
      command("stare at " + name);
      return 1;
   }
   return ::sk_improve(str);
}
