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

public void
create_monster()
{
  ::create_monster();
  
  set_name("iyeriru");
  add_name("teacher");
  set_adj("ancient");
  add_adj("golden-haired");
  set_race_name("half-elf");

  set_title("Holy Preceptor");
  
  set_long("An ancient half-elf. He has long golden hair and his " +
           "stern look makes you feel small.\n");

  set_stats(({ 56, 91, 100, 118, 156, 187 }));
  set_alignment(712);
  set_skill(SS_FORM_DIVINATION, 100);
  set_skill(SS_DEFENCE, 100);
  set_skill(SS_CHANNELING, 100);
  
  set_rank(MYSTIC_CANTOR);
  set_piety(790);
  set_blessed(1);
  
  enable_intro();
  enable_auto_hail();

  set_all_hitloc_unarmed(100);

  set_chat_time(2);
  add_chat("Raise your hand in glory to Antiquity");
  add_chat("Three living Elders stand in glory");
  add_chat("Time and space are no obstacles to us");
  add_chat("Light to Darkness, Darkness to Light");

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

   me = "transmit power through time and space"; ot = me;
   sk_add_train(SS_CHANNELING, ({me, ot}), "channeling",
                50, MYSTIC_MAX_CHANNELING);
}

public int
sk_improve(string str)
{
   string name;

   name = lower_case(TP->query_name());
   if (!MEMBER(TP)) {
      command("whisper " + name + " You are unknown to me...");
      return 1;
   }
   return ::sk_improve(str);
}
