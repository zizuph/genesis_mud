/*
 * This is climber used in MISTY_DIR room p18.c
 * 
 * Made by Milan *giggle*
 * 
 */

inherit "/std/monster";
#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>

string *list_introduced = ({ });

create_monster()
{
    set_name("mimo");
    set_race_name("human"); 
    set_living_name("_climber_");
    set_adj("desperate");
    add_adj("stout");
    set_title("Professional Climber");
    add_prop(CONT_I_WEIGHT,73000);   /* 73 Kg */
    add_prop(CONT_I_HEIGHT,178);      /* 178 cm */

    add_prop(DO_I_TELL_RUMOURS, 1);

    set_stats(({ 65, 70, 50, 30, 40, 34}));

    refresh_mobile(); /* full hp, mana, fatigue */

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_CLIMB, 30);

    set_scar(3);
    set_alignment(500);

    set_act_time(5); 
    add_act(({"emote studies the rock carefully.", "climb rock"})); 
    add_act(({"say Have you found the Climbers guild?", "smile knowingly", 
              "say Lots of XP only for climbing anything :)", "poke all"})); 
    add_act(({"say DAMNED LAG :(", "sigh"})); 
    add_act(({"say I am a professional climber.", 
              "say I must climb up every rock I find.", "climb rock"}));

   trig_new("%w 'introduces' %s", "react_introduce");
   trig_new("%w 'starts' 'to' 'climb' 'the' 'rock.\n'", "react_start");
   trig_new("%w 'made' 'it!!!\n'", "react_made");
   trig_new("%w 'shouts:' 'AAAAAAAaaaaaaaaa.....' %s", "react_happy");
   trig_new("'You' 'look' 'up' 'and' 'see' 'how' %w 'jumps' %s", "react_crazy");
}

query_knight_prestige(){return -200;}

int
react_introduce(string who, string dummy) 
{
  who = TP->query_real_name();
  dummy = explode(dummy, " ")[0];
  if((dummy == "himself") || (dummy == "herself") || (dummy == "itself"))
    if(member_array(who, list_introduced) == -1)
      list_introduced += ({ who });
  call_out("return_introduce", 4);
}
void
return_introduce() {
 object *in_room;
 int i, met_me;
  in_room=FILTER_LIVE(all_inventory(environment()));
  met_me=1;
  for (i = 0; i < sizeof(in_room); i++) 
    if (!in_room[i]->query_met(TO->query_real_name())) met_me=0;
  if (!met_me) {
     command("introduce me");
     command("bow");
  }
}
int
query_introduced(object who)
{
  if(member_array(who->query_real_name(), list_introduced) == -1)
    return 0;
  return 1;
}

int
react_start(string who) 
{
   if (who) 
   {
      who = lower_case(who);
      call_out("return_start", 4, find_living(who));
      return 1;
   }
}
void
return_start(object who) 
{
  if(who)
  {
    if(query_introduced(who))
      command("shout Good luck "+who->query_name()+".");
    else
      command("shout Good luck "+who->query_nonmet_name()+".");
    command("giggle");
  }
}

int
react_made(string who) {
   if (who) {
      call_out("return_made", 4, who);
      return 1;
   }
}
void
return_made(string who) {
     command("say Only I am so clumsy...");
     command("cry");
}

int
react_happy(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      call_out("return_happy", 4, who);
      return 1;
   }
}
void
return_happy(string who) {
   object obj;
   if (obj = present(who, environment())) {
     command("ponder another clumsy climber.");
     command("poke "+who);
     command("bounce");
   }
}

int
react_crazy(string who) {
   if (who) {
      who = lower_case(who);
      call_out("return_crazy", 4, who);
      return 1;
   }
}
void
return_crazy(string who, string dummy) {
   object obj;
   if (obj = present(who, environment())) {
     command("say Going mad???");
     command("peer at "+who);
     command("pat "+who);
   }
}
