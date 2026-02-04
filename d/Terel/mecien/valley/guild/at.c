/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/d/Terel/std/mystic";
inherit "/d/Terel/std/teacher";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define NF(str)        notify_fail(str)
#define TO             this_object()
#define TP             this_player()

public void set_up_skills();

public void
create_monster()
{
   ::create_monster();
   
   set_name("nallasar");
   add_name("man");
   add_name("master");
   add_name("teacher");
   set_adj("aged");
   add_adj("blue-eyed");
   set_race_name("human");
   set_living_name("nallasar");
   set_title("Sky Keeper");

   set_long("Covered head to toe in a robe and mantle of azure, this " +
            "aged man stands like a monument to wisdom and mystery. " +
            "His hair is long, as is his beard, of startling white. " +
            "Piercing blue eyes leap from beneath his cowl, seaching " +
            "deeply everything. His face withered and worn, like the " +
            "rocks on the shore beaten down by the ageless winds and " +
            "waters.\n");

   add_prop("no_show_title", 1);

   set_stats(({ 67, 102, 89, 112, 123, 103 }));

   set_chat_time(15);
   add_chat("So when the sky became as dark as pitch then I knew the " +
            "time had come...");
   add_chat("Believe all ye, I know the hour");

   set_hp(9999);
   set_all_hitloc_unarmed(85);
   
   set_rank(MYSTIC_EXARCH);
   set_alignment(700);
   set_blessed(1);
   set_skill(SS_FORM_DIVINATION, 100);
   set_skill(SS_ELEMENT_AIR, 90);
   set_skill(SS_DEFENCE, 100);
   
   enable_intro();
   enable_auto_hail();

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

   me = "call the storms and skies"; ot = me;
   sk_add_train(SS_ELEMENT_AIR,  ({me, ot}), 0, 0, MYSTIC_MAX_AIR);
}

public int
sk_improve(string str)
{
   string name;

   name = lower_case(TP->query_name());
   if (!MEMBER(TP)) {
      command("point at " + name);
      command("say You are not worthy to be taught.");
      return 1;
   }
   return ::sk_improve(str);
}

public void
poof_me()
{
   tell_room(environment(TO), "The " + short() + " fades away.\n");
   remove_object();
}

void
set_duration(int t)
{
   set_alarm(itof(2+t), 0.0, poof_me);
}

public void
add_introduced(string name)
{
   ::add_introduced(name);
   
   command("whisper " + lower_case(name) + " Touch the stone and you " +
           "will find your way back.");
}
