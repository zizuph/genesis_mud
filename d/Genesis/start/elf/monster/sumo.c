/*
 * A sumo-wrestler ogre
 */

#include "../stddefs.h"
#include "../tefyma.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>

#pragma save_binary

inherit "/std/monster";
inherit STRINGLIB;
inherit MISCLIB;

#define IND_NAME "sumo"		/* Names have to be lowercase. Sigh. */
#define RACE "ogre"

#define OUT "east"

#define LONG \
  "It is an enormous ogre. He doesn't get any smaller from being grossly "+\
  "overweight, not to mention having lots of muscles under all that fat. He "+\
  "is dressed only in an odd-looking, small loincloth with a thick, "+\
  "padded belt, and his shiny, black hair is tied into an elaborate knot "+\
  "at the top of his head.\n"

create_monster() {
  if (IS_CLONE) {
    set_name(IND_NAME);
    set_race_name(RACE);
    set_adj("enormous");
    set_long(WRAP(LONG));

    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_WEIGHT, 170 KG);
    add_prop(CONT_I_HEIGHT, 240 CM);
    add_prop(CONT_I_VOLUME, 170 LITRES);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 80);
    
    set_base_stat(SS_STR, 55);
    set_base_stat(SS_DEX, 40);
    set_base_stat(SS_CON, 60);
    set_base_stat(SS_INT, 20);
    set_base_stat(SS_WIS, 20);
    set_base_stat(SS_DIS, 50);

    set_alignment(70);
    set_appearance(65);
    set_aggressive(0);
    set_attack_chance(0);

    trig_new("%s 'says:' %s",  "react_speech");
    

    refresh_mobile();
  }
}

init_living()
{
  if (interactive(this_player()))
    set_heart_beat(1);

  ::init_living();
}


void check_shutdown()
{
  object *inv;
  int i;
  
  if (environment() && (inv = all_inventory(environment())) != 0)
    for (i = 0; i < sizeof(inv); i++)
      if (interactive(inv[i]))
	return;

  set_heart_beat(0);
}


void heart_beat()
{
  check_shutdown();

  ::heart_beat();
}


object find_exit(string cmd) 
{
  object env;
  string room;
  int i;

  if ((env = environment()) != 0 &&
      (i = member_array(cmd, env->query_exit_cmds())) >= 0) {

    if ((room = env->query_exit_rooms()[i]) != 0) {
      load_object(room);
      return find_object(room);
    }
  }
  return 0;
}

react_speech(string name, string str)
{
  
  if (word_in("fat",       str) ||
      word_in("fatty",     str) ||
      word_in("stout",     str) ||
      word_in("corpulent", str) ||
      word_in("obese",     str)) {
    call_out("react_fat_1", 0, lower_case(name));
  }
  return 1;
}


react_fat_1(string name) 
{
  command("emote gets furiously red in the face.");
  command("say don't use that word!");
  call_out("react_fat_2", 1, name);
}

react_fat_2(string name) 
{
  object person;
  object where;

  command("steam");
  
  if ((person = present(name, environment())) != 0 &&
      (where  = find_exit(OUT)) != 0 ) {
    tell_room(environment(person),
	      QCTNAME(this_object()) + " throws " + 
	      QTNAME(person) + " out.\n", person);
    person->catch_msg(QCTNAME(this_object()) + " throws you out.\n");
    person->move(where);

    tell_room(environment(person),
	      QCTNAME(person) +  "on the ground with a loud crunch.\n", 
	      person);
    person->catch_msg("The ground hits you with a bone-crunching sound.\n");
    call_out("react_fat_3", 1, person);
  }
}


react_fat_3(object person) 
{
  if (person)
    person->catch_msg("Fortunately it only seems " +
		      "to have been gravel that crunched.\n");
}
