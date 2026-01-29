/*
 * Hammerhand shadow file
 * TAPAKAH, 10/2005
 */

#pragma strict_types

inherit "/std/guild/guild_lay_sh";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "hh_guild.h"
#include "../hhands.h"
#include "../../daenbraigh.h"

inherit "hh_common";

#define SW shadow_who

int
is_hammerhand()
{
  return 1;
}

string
query_guild_style_lay()
{
    return GUILD_STYLE;
}

int
query_guild_tax_lay()
{
  return HHANDS_TAX;
}

int
query_guild_name_lay()
{
  return HHANDS_NAME;
}

int
query_guild_keep_player(object player)
{
}

int
query_guild_not_allow_join_lay(
			       object player,
			       string type,
			       string style,
			       string name,
			       )
{
  if(::query_guild_not_allow_join_lay(player, type, style, name))
    return 1;

  if(style == "cleric" || style == "magic") {
    player->catch_tell("The Hammerhands do not like all this occult business!\n");
    return 1;
  }

  return 0;
}

int
query_guild_level_lay()
{
  return MIN(HHANDS_MAXLEVEL,sqrt(query_shadow_who()->query_stat(SS_LAYMAN)+1) / 10);
}

int
query_def_post()
{
  if (this_player()->query_default_start_location() == HHANDS_STARTLOC) 
    return HHANDS_POST;
    
  return query_shadow_who()->query_def_post();
}

string
query_guild_title_lay()
{
  return HHANDS_TITLE[query_guild_level_lay()];
}

mixed
query_guild_trainer_lay()
{
  return HH_TRAIN;
}

void
hh_greeting()
{
  object who,tattoo;
  who = query_shadow_who();
  
  setuid();
  seteuid(getuid());

  if(get_wep_skill(SW) < HH_SKILL) {
    tell_object(SW,
		BSN("You are no longer skilled enough with a bludgeon to "+
		    "be considered a HammerHand. Your tattoo fades away.")
		);
    log_file(HH_LOG,
	     ctime(time()) + SW->query_name() + " expelled skill\n"
	     );
    remove_lay_member();
    return;
  }
  if(SW->query_alignment() > 0) {
    tell_object(SW,
		BSN("You are too good in your soul to be good with your weapon. "+
		    "You feel an itch on your arm and then the tattoo is gone.")
		);
    log_file(HH_LOG,
	     ctime(time()) + SW->query_name() + " expelled alignment\n"
	     );
    remove_lay_member();
    return;
  }
  tell_object("Your Hammerhand tattoo glows faintly.\n");
  if(!present(HHANDS_ID,SW)) 
    if(tattoo = clone_object(HHANDS_TATTOO))
      tattoo->move(who,1);
  SW->add_subloc(HHANDS_SUBLOC);

  SW->add_cmdsoul(HHANDS_SOUL);
  SW->update_hooks();

}

int
set_skill(int skill, int val)
{
  if (get_alarm(skill_alarm))
    remove_alarm(skill_alarm);
  skill_alarm = set_alarm(1.0, 0.0,
			  &hh_greeting(1));
  return SW->set_skill(skill, val);
}

void
init_lay_shadow(string str)
{
  ::init_lay_shadow(str);
  greet_alarm = set_alarm(2.0, 0.0, hh_greeting);
}

void
start_player()
{
  SW->start_player();
  init_guild_member();
}

int
add_lay_shadow(object who)
{
  int ret = shadow_me(who, "layman", HHANDS_STYLE, HHANDS_NAME);
  
  if (ret == 1) {
    init_guild_member();
  }

  return ret;
}

string
show_subloc(string subloc, object me, object for_obj)
{
  string str;
  
  if (subloc != HHANDS_SUBLOC) 
    return me->show_subloc(subloc, me, for_obj);
    
  if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) 
    return "";
    
  if (for_obj == me)
    str = "You have a ";
  else
    str = capitalize(me->query_pronoun()) + " has a ";
  
  return str + " tattoo of two crossed clubs on his forehead.\n";
}   

void
remove_lay_member()
{
  object tattoo, who = query_shadow_who();
  
  who->clear_guild_stat(SS_LAYMAN);

  while (tattoo = present(HHANDS_TATTOO, who))
    tattoo->remove_object();

  if (who->query_default_start_location() == HHANDS_STARTLOC)
    who->set_default_start_location(who->query_def_start());
  
  who->remove_cmdsoul(HHANDS_CMDSOUL);
  who->update_hooks();

  remove_guild_lay();
  remove_shadow();
}

