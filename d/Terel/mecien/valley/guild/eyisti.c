/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";
inherit "/d/Terel/std/teacher";

#include <ss_types.h>
#include <language.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP   this_player()

public void set_up_skills();

public void
create_monster()
{
  ::create_monster();
  
  set_name("eyisti");
  add_name("teacher");
  add_name("master");
  set_adj("ancient");
  set_race_name("faerie");
  set_long("An ancient faerie.\n");

  set_rank(MYSTIC_EXARCH);
  set_blessed(1);
  set_stats(({ 8, 91, 8, 108, 114, 92 }));
  set_skill(SS_FORM_DIVINATION, 100);
  set_skill(SS_DEFENCE, 100);

  set_invis(1);
  set_all_hitloc_unarmed(100);
  set_alignment(899);

  set_chat_time(2);
  add_chat("Greetings all ye hallowed friends!");
  add_chat("Glory Glory Glory!");
  add_chat("Vision is the worth of many minds");
  add_chat("My way is Truth, my cloak is Majesty");
  add_chat("If you know me, the I shall know you!");
  
  set_act_time(23);
  add_act("chant");
  add_act("sign");

  create_skill_raise();
  set_up_skills();
}

public void
go_invis(object who)
{
   command("giggle");
   set_invis(1);
}

public int
do_say(string str)
{
  if (str != "show yourself")
      return 0;
  set_invis(0);
  command("giggle");
  set_alarm(13.0, -1.0, &go_invis(TP));
  return 1;
}

public void
init_living()
{
   ::init_living();
   init_skill_raise();
   add_action(do_say, "say");
}

public void
set_up_skills()
{
   string me, ot;

   me = "cast divinations"; ot = me;
   sk_add_train(SS_FORM_DIVINATION, ({me, ot}), 0, 0, MYSTIC_MAX_DIVINATION);
}

public int
sk_improve(string str)
{
   string name;

   if (query_invis()) return 0;

   name = lower_case(TP->query_name());
   if (!MEMBER(TP)) {
      command("whisper "+name+" You are not worthy to be taught.");
      return 1;
   }
   return ::sk_improve(str);
}
