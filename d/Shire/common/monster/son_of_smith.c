/*
 * Cloned by ~Shire/common/hobbiton/forge
 */

inherit "/std/monster";

#include "defs.h"
#include <stdproperties.h>
#include "tobacco.h"

void react_introduce(string person, string who);
void introduce_me();
void re_intro();

int intro_alarm, alarm_id,reintro_alarm;

int not_intro;

create_monster()
{
  set_race_name("hobbit");
  set_name("hany");
  set_living_name("hany");
  set_adj(({"small", "slim", "bold"}));
  set_long("@@our_long");
  add_prop(CONT_I_WEIGHT, 45000);
  add_prop(CONT_I_VOLUME, 40000);

  default_config_npc(10);
  set_monster_home("/d/Shire/eastroad/western/forge");
   set_restrain_path("/d/Shire/eastroad/");
  set_random_move(1);
  clone_tobacco();

  set_chat_time(5);
  add_chat("My father is the blacksmith.");
  add_chat("I don't want to be a blacksmith.");
  add_chat("If I find Gorges house, he'll make me his apprentice.");
  add_chat("Do you know where Gorges house is?");
  add_chat("I already know a lot about Gorges potions.");
  add_chat("If you want I can try to identify potions for you.");
  add_chat("I would rather be an alchemist than a blacksmith.\n");

  trig_new("%w 'introduces' %s", "react_introduce");

}

init_living()
{
   ::init_living();
  add_action("do_id","id");
}

void
react_introduce(string person, string who)
{
	if (not_intro)
	return;
	if (!intro_alarm)
		intro_alarm = set_alarm(4.0,0.0, &introduce_me());
}

void
introduce_me()
{
	remove_alarm(intro_alarm);
    command("introduce me");
	not_intro = 1;

	if (!reintro_alarm)
		reintro_alarm = set_alarm(15.0,0.0, &re_intro());
}

void
re_intro()
{
	remove_alarm(reintro_alarm);
	not_intro = 0;
}

our_long() {
  string str;
 
  str = "He looks like any ordinary young hobbit.\n";
  str += "He is trying to get a place as Gorges apprentice.\n";
  str += "If you type 'id <potion name>' he might be able to.\n";
  str += "identify your potions.\n";

  return str;

}

/*
do_id This tries to identify a potion
*/

do_id(string str) {
  object ob;
  string result;

  if(!parse_command(str, this_player(), "%o", ob)) {
    notify_fail("This is not a potion!\n");
    return 0;
  }

  ob->set_identified(1);
  result = ob->potion_long();
  if(!result) {
    notify_fail("Sorry, but this potion is unknown to me.\n");
    return 0;
  }


  tell_room(environment(), "The young hobbit examines the vial.\n");
  tell_room(environment(), "Then he opens the vial an sniffs at the fumes.\n");
  command("cough");
  command("smile");
  command("say This is not easy.");
  command("say But I think it is...");
  command("say Yes!");
  command("say " + result);
    
  write(result);

  return 1;

}
  
/* This is for the solamnian Knights */

query_knight_prestige() { return(-2); }
