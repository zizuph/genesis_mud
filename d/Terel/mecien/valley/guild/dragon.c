/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include "/d/Terel/common/teacher.h"

#define NF(str)        notify_fail(str)
#define BS(xxx)        break_string(xxx,70)
#define TO             this_object()
#define TP             this_player()
#define GUILD          "The Ancient Mystic Order"
#define MEMBER(xx)     xx->query_guild_member(GUILD)

#define A_BITE 0
#define A_CLAW 1
#define A_TAIL 2
#define A_HORN 3
#define A_CLAW2 4

#define H_BODY 0
#define H_HEAD 1

void set_up_skills();

void
create_creature() { 
set_race_name("dragon");
set_adj("arcane");
add_adj("white");
set_name("arinosticarus");
add_name("master");
add_name("teacher");

  set_stats(({ 123, 145, 142, 112, 144, 133 }));
  set_skill(SS_FORM_DIVINATION, 100);
  set_skill(SS_ELEMENT_DEATH, 100);
  set_skill(SS_DEFENCE, 100);

set_chat_time(75);
set_act_time(34);

   set_hp(9999);
   set_mana(9999);
   
  set_attack_unarmed(A_BITE, 100, 100, W_IMPALE, 50, "jaws");
  set_attack_unarmed(A_CLAW,  75,  70, W_SLASH,  50, "right claw");
  set_attack_unarmed(A_TAIL,  60,  68, W_BLUDGEON, 25, "tail");
  set_attack_unarmed(A_HORN,  73,  78, W_IMPALE, 20, "horns");
  set_attack_unarmed(A_CLAW2, 71, 67, W_SLASH, 40, "left claw");

  set_hitloc_unarmed(H_BODY, ({ 80, 87, 89, 90}), 85, "torso");
  set_hitloc_unarmed(H_HEAD, ({ 73, 72, 70, 78}), 15, "head");

  create_skill_raise();
  set_up_skills();
}


void
init_living()
{
   ::init_living();
   init_skill_raise();
}


void
set_up_skills()
{
   string me, ot;

   me = "master the powers of life"; ot = me;
   sk_add_train(SS_ELEMENT_LIFE,  ({me, ot}), 0, 0, 80);
}

int
sk_improve(string str)
{
   string name;

   name = lower_case(TP->query_name());
   if (!MEMBER(TP)) {
      TO->command("stare at " + name);
      return 1;
   }
   return ::sk_improve(str);
}
