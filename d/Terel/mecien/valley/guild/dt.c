/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";
inherit "/d/Terel/std/teacher";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define NF(str)        notify_fail(str)
#define TO             this_object()
#define TP             this_player()

public void set_up_skills();
public void set_duration(int t);

public void
create_monster()
{
  ::create_monster();
  
  set_name("ghuindar");
  add_name("master");
  add_name("teacher");
  add_name("man");
  set_adj("old");
  set_race_name("human");

  set_title("the Master of the Dead");
  set_long(
    "A very old and ghostlike man. From the expression of his face you " +
    "get the ambiguous feeling of both harshness and softness. " +
    "His gaze looks almost grim as a contrast to his " +
    "gentle smile. Wrapped around his thin body is a dark cloak made of " +
    "finest silk.\n");

  set_rank(MYSTIC_EXARCH);
  set_stats(({ 67, 102, 89, 112, 123, 103 }));
  set_skill(SS_FORM_DIVINATION, 100);
  set_skill(SS_ELEMENT_DEATH, 90);
  set_skill(SS_DEFENCE, 100);
  set_ghost(1);
  add_prop(CONT_I_LIGHT, 2);
  add_prop(LIVE_I_ALWAYSKNOWN, 1);

  set_chat_time(15);
  add_chat("Use violence only as a last resort.\n");
  add_chat("My ways are the ways of death. Follow me only if you must!\n");
  
  enable_auto_hail();

  set_hp(9999);
  set_mana(9999);
  set_all_hitloc_unarmed(85);

  create_skill_raise();
  set_up_skills();
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

   me = "master the powers of death"; ot = me;
   sk_add_train(SS_ELEMENT_DEATH,  ({me, ot}), 0, 0, MYSTIC_MAX_DEATH);
}

public int
sk_improve(string str)
{
   string name;

   name = lower_case(TP->query_name());
   if (!MEMBER(TP)) {
      command("point at " + name);
      command("say You are not worthy to be teached.");
      return 1;
   } else if (query_prop("summoner") != TP->query_name()) {
      command("stare at " + name);
      command("say You did not summon me.");
      return 1;
   }
   return ::sk_improve(str);
}

public void
poof_me()
{
    tell_room(environment(TO), "The "+short()+" fades away.\n");
    remove_object();
}

public void
set_duration(int t)
{
    set_alarm(itof(2+t), -1.0, poof_me);
}
