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
    
    set_name("aliyandar");
    add_name("master");
    add_name("teacher");
    set_adj("luminous");
    add_adj("peaceful");
    set_race_name("human");

    set_long("An aged man, lithe and austere, silent and brooding. He " +
             "stands tall and proud. His eyes deep and searching, deep " +
             "green like the sea itself. He is garbed in a simple gray " +
             "robe, covered by a pale mantle of white.\n");

    set_rank(MYSTIC_EXARCH);
    set_blessed(1);
    set_alignment(681);
    set_stats(({ 67, 102, 89, 112, 123, 103 }));
    set_skill(SS_FORM_DIVINATION, 100);
    set_skill(SS_ELEMENT_LIFE, 90);
    set_skill(SS_DEFENCE, 100);

    set_chat_time(15);
    add_chat("Let peace come upon all peoples.");
    add_chat("My ways are the ways of the living.");
    
    enable_intro();
    enable_auto_salute();

    set_hp(9999);
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

   me = "master the powers of life"; ot = me;
   sk_add_train(SS_ELEMENT_LIFE,  ({me, ot}), 0, 0, MYSTIC_MAX_LIFE);
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
   }
   return ::sk_improve(str);
}
