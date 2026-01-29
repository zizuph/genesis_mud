/*
 * Orgulas Brandybug, owner of the Calian Inn.
 * Coder: Deinonychus (code stolen from Maniac)
 * 
 * 30/5/96   trig ---> emote_hook          Maniac
*/



inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <filter_funs.h>
#include "monster.h"
inherit STD_AIDED;

#define ENV environment

void
create_monster() 
{
  if (!IS_CLONE)
    return;
  set_name("orgulas");
  add_name("owner");
  add_name("bartender");
  add_name("innkeeper");
  set_race_name("human");
  set_adj(({"smiling","black-haired"}));
  set_title("Brandybug the Innkeeper");
  set_long("Orgulas Brandybug is a quite tall and strong looking woman "
	   + "with long black hair and a ever smiling face. "
	   + "She has a nice tan and seems to love her job as a "
	   + "bartender.\n");
  default_config_npc(30);
  set_base_stat(SS_CON,75);
  set_hp(5000);
  set_skill(SS_UNARM_COMBAT, random(20) + 55);
  set_skill(SS_DEFENCE, random(10) + 60);
  set_skill(SS_AWARENESS, random(10) + 50);
  set_alignment(50 + random(100));
  set_gender(1);
  add_prop(NPC_M_NO_ACCEPT_GIVE,0);

  set_act_time(12);
  add_act("say You'll nowhere get a better drink than here, I promise!");
  add_act("say Drink as much as you can, you never know when your last "
	   + "minute has come!");
  add_act("say We have the best wine in this region. So don't miss "
	   + "the chance to try a glass of it.");
  add_act("emote cleans the counter with a white towel.");
}


int 
will_keep(object obj)
{

  if (obj->id("glass"))
      return 1;
}

void 
react_give(object obj, object from)
{
  if (!will_keep(obj))  {
    command("say You'd better keep that, "+from->query_nonmet_name()+".");
    command("give "+OB_NAME(obj)+" to "+from->query_real_name());
    if (ENV(obj) == this_object()) 
      command("drop "+OB_NAME(obj));
  }
  else{
    tell_room(environment(this_object()), QCTNAME(this_object()) + " cleans " +
              LANG_THESHORT(obj) + " and puts its back to the shelf.\n");
    obj->remove_object();
    command("smile");
  }
}


void
enter_inv(object obj, object from)
{
  ::enter_inv(obj,from);
  set_alarm(2.0, 0.0, &react_give(obj,from));
}


void
return_introduce() 
{
  object *in_room;
  int i, met_me;
 
  in_room = (FILTER_LIVE(all_inventory(environment())) - ({this_object()}));
  met_me = 1;
  for(i = 0; i < sizeof(in_room); i++) 
      if (!in_room[i]->query_met(query_real_name())) met_me = 0;
  if (!met_me){
      command("introduce me");
      command("bow");
  }
}


void
add_introduced(string who)
{
    set_alarm(2.0, 0.0, return_introduce);
}

