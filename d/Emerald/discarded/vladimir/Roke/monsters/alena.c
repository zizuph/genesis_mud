#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"
inherit "/d/Roke/common/monster";

int has_introduced=0;
int cat;
string long;

void
create_monster()
{	
  set_name("alena");
  set_living_name("alena");
  set_race_name("human");
  set_long("Her eyes are all puffy and she is crying.\n");
  set_adj("crying");
  set_gender(1);
  add_name("rokealena");


default_config_npc(15);
set_random_move(20);
set_restrain_path(ATUAN);

set_hp(10000);

set_skill(SS_DEFENCE, 40);

add_act("emote sobs.");
add_act("emote tugs on your arm and cries.");
add_act("emote wipes her nose on her sleeve.");
add_act("emote sniffles.");

add_chat("Waaaaaaahh!");
add_chat("I want my kitty!");


add_cchat("I'll tell my mommy!");


set_act_time(20);
set_chat_time(50);

set_default_answer("I want my kitty!\n");



::create_monster();

      if (IS_CLONE)
              call_out("arm_me", 1);

  trig_new("%w 'introduces' %s","react_introduce");

}

void
arm_me()
{
      seteuid(geteuid(this_object()));

      clone_object(ATUAN + "obj/red_dress")->move(TO);

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
cat = 1;
}