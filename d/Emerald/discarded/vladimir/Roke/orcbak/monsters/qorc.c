#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"
inherit "/d/Roke/common/monster";
int has_introduced=0;
int figure;


string long;

void
create_monster()
{
  set_name("skeezle");
  set_living_name("skeezle");
  set_race_name("orc");
  set_long("She looks very upset about something.\n");

  set_adj("upset");
  set_gender(1);
  add_name("genorc");


default_config_npc(15);
set_random_move(20);
set_restrain_path(ATUAN);

set_hp(10000);

set_skill(SS_DEFENCE, 40);

add_act("emote sobs.");
add_act("sigh");
add_act("emote smiles grimly.");
add_act("sniff");

add_chat("Find me my figurine!");
add_chat("Have you seen it?!");


add_cchat("My son will eat you!");


set_act_time(20);
set_chat_time(50);

set_default_answer("Give me my figurine back!!!!\n");



::create_monster();
      if (IS_CLONE)
              call_out("arm_me", 1);

  trig_new("%w 'introduces' %s","react_introduce");

}

void
arm_me()
{
      seteuid(geteuid(this_object()));

      clone_object("/d/Roke/vladimir/orc/obj/shirt")->move(TO);

      command("wear all");
      seteuid(getuid(TO));

}

void
react_introduce(string person,string who)
{
    if (!has_introduced)
      {
        call_out("introduce_me",6);
        has_introduced=1;
        call_out("remove_int",30);
      }
}

void
introduce_me()
{
    command("introduce myself");
}

void
remove_int()
{
    has_introduced=0;
}

kitty_return()
{
figure = 1;
}

