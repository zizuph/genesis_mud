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
    
    set_name("ossed");
    add_name("gnome");
    add_name("master");
    add_name("teacher");
    set_adj("wizened");
    add_adj("dark");
    set_race_name("gnome");
    set_short("gnome");

    set_long("An ancient creature, existing from the depths of the " +
             "earth. He stands three feet high, robed and cloaked in " +
             "black. His hands aged and wrinkled like a knotted tree, " +
             "stained with elements. His clothing is encrusted with " +
             "bits of minerals. Wearing gold, silver and platinum " +
             "rings adorned with many jewels, as if to suggest " +
             "something other than a stoic nature. A short, braided " +
             "white beard protrudes from beneath his dark cowl, his " +
             "eyes shimmering with wisdom.\n");

   set_alignment(343);
    set_rank(MYSTIC_EXARCH);
    set_blessed(1);
    set_stats(({ 67, 102, 89, 112, 123, 103 }));
    set_skill(SS_FORM_TRANSMUTATION, 100);
    set_skill(SS_ELEMENT_EARTH, 90);
    set_skill(SS_DEFENCE, 100);
    add_prop(CONT_I_LIGHT, 2);
    
    enable_intro();
    enable_auto_salute();

    set_chat_time(15);
    add_chat("Rock and stone bind all that is...");
    add_chat("Here the earth gives its power to the Shrine of Antiquity.");

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

   me = "control the forms of matter"; ot = me;
   sk_add_train(SS_FORM_TRANSMUTATION, ({me, ot}),
                0, 0, MYSTIC_MAX_TRANSMUTATION);
   me = "master the powers of the earth"; ot = me;
   sk_add_train(SS_ELEMENT_EARTH, ({me, ot}), 0, 0, MYSTIC_MAX_EARTH);
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
    tell_room(environment(TO), "The "+short()+" steps into the stone.\n");
    remove_object();
}

public void
set_duration(int t)
{
    set_alarm(itof(2+t), -1.0, poof_me);
}
