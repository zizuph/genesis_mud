#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
#include "../guild.h"

inherit AA_DIR+"npc/shield_guard";

static object *glasses = ({ });
static int    alarm;
static mapping tipped = ([ ]);


void
create_monster()
{
  ::create_monster();
  set_name(({"morncki","bartender"}));
  set_guard_race("human");
  set_guard_base_stat(90+random(30));
  set_long("This is the shopkeeper.\n");
  set_alarm(0.0, 0.0, "update_guard");
  remove_prop(LIVE_I_NEVERKNOWN);
  remove_prop(NPC_M_NO_ACCEPT_GIVE);

  set_act_time(1); 
  add_act("say Hello! Fancy a drink?"); 
  add_act("say What would you like?"); 
  add_act("emote polishes some glasses."); 
  add_act("shout Spirits!!!  Wines!!!  Beers!!!"); 
  add_act("say I have excellent apple cider.");
  add_act("smile all"); 
  add_act("say Just tell me what would you like."); 
  add_act("emote cleans the counter."); 
  add_act("stretch"); 
  add_act("emote checks content of the barrels."); 
  add_act("say I have the strongest rum around!"); 
  add_act("say Do you prefer white or red wine?"); 
  add_act("say Brandy is excellent this year.");
  add_act("say I will never be short of supply!"); 
  add_act("emote lines the bottles on the shelf."); 
  add_act("emote changes the water in the sink."); 
  add_act("say Everything must be clean."); 
  add_act("say Have you had a hangover yesterday?"); 
  add_act("say My ale can clear your head."); 
  add_act("say Little tip is always welcome."); 

  add_ask(({"guru","club","worthy"}),VBFC_ME("my_answer"));
  set_dont_answer_unseen(1);
  set_default_answer(VBFC_ME("my_default"));
}

void
return_intro(object ob)
{
    if(!present(ob, E(TO)))
    {
	return;
    }
    command("introduce me to "+ob->query_real_name());
}

void
add_introduced(string str)
{
  object ob = find_player(lower_case(str));
  if(ob && !ob->query_met(TO))
  {
	set_alarm(3.0, 0.0, &return_intro(ob));
  }
} 

void
init_attack()
{
  return;
}

void 
attacked_by(object ob)
{
  ::attacked_by(ob);
  command("shout Help!!! A "+ob->query_nonmet_name()+" wants to kill me!");
  set_alarm(2.0, 0.0, "second_life", ob);
  set_alarm(5.0, 0.0, "second_life", ob);
  set_alarm(10.0, 0.0, "second_life", ob);
  set_alarm(15.0, 0.0, "second_life", ob);
}

void
enter_inv(object ob, object from)
{
  string who;
  int a;

  ::enter_inv(ob, from);
  if(member_array("_a_p_g_",ob->query_names()) != -1)
  {
    glasses += ({ ob });
    if(!alarm)
    {
      set_alarm(itof(10+random(10)), 0.0, "wash_glasses");
      alarm = 1;
    }
  }
  else if((a = ob->query_prop(OBJ_I_VALUE)) && living(from))
  {
    set_alarm(2.0, 0.0, "command", "say Thank you "+
					from->query_nonmet_name()+"!");
    set_alarm(3.0, 0.0, "command", "say I like it when I get a tip.");

    who = from->query_real_name();
    if(member_array(who, m_indices(tipped)) == -1)
      tipped += ([ who : a ]);
    else
      tipped[who] += a;
  }
}

void
wash_glasses()
{
  int i;
  string what;

  command("emote washes "+COMPOSITE_DEAD(glasses)+" in the sink, polishes "+
	(what = (sizeof(glasses)>1 ? "them":"it"))+" and puts "+what+
	" back onto the shelf.");
  for(i=0; i<sizeof(glasses); i++)
    glasses[i]->remove_object();
  glasses = ({ });
  alarm = 0;
}

string
my_answer()
{
  string who = TP->query_real_name();

  if(member_array(who, m_indices(tipped)) == -1)
  {
    command("emote seems to be totally deaf.");
    return "";
  }
  if(tipped[who] < 12)
  {
    TP->catch_msg(QCTNAME(TO)+" looks at you for a moment but then goes "+
			"about his own bussiness.\n");
    tell_room(ENV(TO), QCTNAME(TO)+" looks at "+QTNAME(TP)+
		" for a moment but then goes about his own bussiness.\n", TP);
    return "";
  }
  if(tipped[who] < 144)
  {
    command("emote clears his ears.");
    command("say Sorry, but somehow I don't hear well.");
    return "";
  }
  if(tipped[who] < 1728)
  {
    command("hmm");
    command("scratch");
    command("say I think I have heard something...");
    command("ponder poor memory");
    return "";
  }
  command("say Yes! Now I remember!");
  command("smile at "+who);
  command("whisper "+who+" Some time ago there was one that could be worthy...");
  command("whisper "+who+" He definitelly knew how to use club!");
  command("whisper "+who+" Everything he had was connected with clubs...");
  command("whisper "+who+" He even had a brooch that looked like one!");
  command("whisper "+who+" But it is long time since he went to the mountains...");
  command("whisper "+who+" Noone has seen him since.");
  command("sigh");
  return "";
 
}

string
my_default()
{
  string who = TP->query_real_name();

  if(member_array(who, m_indices(tipped)) == -1)
  {
    command("emote seems to be totally deaf.");
    return "";
  }
  if(tipped[who] < 12)
  {
    TP->catch_msg(QCTNAME(TO)+" looks at you for a moment but then goes "+
			"about his own bussiness.\n");
    tell_room(ENV(TO), QCTNAME(TO)+" looks at "+QTNAME(TP)+
		" for a moment but then goes about his own bussiness.\n", TP);
    return "";
  }
  if(tipped[who] < 144)
  {
    command("emote clears his ears.");
    command("say Sorry, but somehow I don't hear well.");
    return "";
  }
  command("say Ohhh... I am afraid I dont know anything about it.");
  command("comfort "+who);
  return "";
}
