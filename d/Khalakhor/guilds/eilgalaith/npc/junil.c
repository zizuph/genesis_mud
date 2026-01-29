/**********************************************************************
 * - junil.c                                                        - *
 * - Junil major NPC for Eil-Galaith that is in join.c              - *
 * - Created by Damaris 11/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Aligned to the new quest system by Tapakah, 08/2021            - *
 **********************************************************************/
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../guild.h"
// #include "/d/Khalakhor/sw_speir/samorgan/npc/riddler.h"
inherit "/d/Khalakhor/std/npc/elf";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";
inherit "/d/Khalakhor/common/npc/quest-npc";

#define TPQN TP->query_name()

static mapping remembered = ([]), failed = ([]);

string *
my_quests ()
{
  return ({ "Eil-Galaith Entrance" });
}

string
ask_help ()
{
	command("say If you need help here, just read the scroll.");
	command("emote points to the scroll.");
	return "";
}

string
ask_eilgalaith ()
{
	command("say Ahh yes. Eil-Galaith.");
	command("say Please visit the library to learn more. I've "+
          "placed many scrolls there that you may read.");
	command("emote points towards the west.");
	return "";
}

mixed
reward_player (mapping quest)
{
  if (! quest) {
    command("say Something strange happened. "+
            "You should alert the authorities.");
    log_quest(-1, TPQN, "reward out of turn", "error");
    return;
  }
  do_reward_player(quest["new_bit"], quest["new_xp"], "__answered_galaith_riddles");
}

string
ask_reward ()
{
  mapping quest = get_next_quest();
	if (! quest) {
		command("say You already completed that task for "+
            "me. I have nothing else to give you at the moment.\n");
		return "";
	}
	if (TP->query_prop("__answered_galaith_riddles")) {
    command("say Congratulations on solving the "+
            "riddler's questions!\n");
    reward_player(quest);
    return "";
  }
	command("say Hmm, Go see the Riddler in SaMorgan. Perhaps, "+
          "they may have a task for you to do.. By the way, how did "+
          "you get to Sanctuary without speaking to her first? Please "+
          "tell us how by using <bug junil>.\n");
	return "";
}

void
create_khalakhor_elf ()
{
	set_name("junil");
	add_name("story teller");
	set_title("Eilaith of the House Eilaith");
	set_adj("friendly");
	add_adj("wise");
	set_gender(G_MALE);
	set_long("He is the story teller of Eil-Galaith.\n"+
           "He has light olive skin.\n"+
           "He has distant deep blue eyes.\n"+
           "His hair is shoulder length, dark brown and "+
           "greying at the temples.\n"+
           "He has the distinguished mark of the mystic vine of the "+
           "Eil-Galaith.\n"+
           "He wears the saffron and cerulean colours of an elven House "+
           "Eilaith.\n"+
           "He is holding a scroll and a quill.\n"+
           "He is sitting behind a desk.\n");
	set_skill(SS_AWARENESS, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_DEFENCE, 100);
	set_skill(SS_BLIND_COMBAT, 100);
	set_skill(SS_PARRY, 100);
	set_act_time(30);
	set_chat_time(30); /* Interval between chat */
	add_prop(CONT_I_WEIGHT,60000);
	add_prop(CONT_I_HEIGHT,180);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	set_alignment(900);
	//set_exp_factor(10);
	set_stats(({ 150, 150, 150, 150, 150, 150 }));
	clone_object(ARM + "jmantle")->move(TO);
	clone_object(ARM + "doublet")->move(TO);
	clone_object(ARM + "pants")->move(TO);
	clone_object(ARM + "mboots")->move(TO);
	command("wear all");	
	/* This is the message given when someone asks us about 
	 * something we don't know about (anything not defined in
	 * add_ask()) */
	set_default_answer(QCTNAME(TP)+" mumbles: I'm not sure "+
                     "what you are asking.\n");
	add_act("smile thought");
	add_act("clear throat");
	
	command("emote picks up a scroll and begins to scribe.\n");
	command("emote shifts his weight in his chair.\n");
	add_ask("help", ask_help);
	add_ask("eil-galaith", ask_eilgalaith);
	add_ask("reward", ask_reward);
}
/*
 * Function name: hook_return_intro
 * Description  : Called when someone introduces themselves
 *                to us.
 * Arguments    : str - Name of the player introducing.
 * Returns      : 1
 */
int
hook_return_intro (string str)
{
	if (!remembered[str])
    {
      command("say Good day to you, " + capitalize(str) +
              ", I'm " + query_name() + " " + query_title() + 
              ". A pleasure to meet you.");
      command("bow " + str);
      remembered[str] = "nice";
      present(str, environment(TO))->add_introduced("junil");
    }
	else if (remembered[str] == "bad")
    {
      command("growl sof");
      command("say I remember you, so if you would be on "+
              "your way!");
    }
	else
    {
      command("giggle");
      command("say Ahh, yes, of course, I remember you from "+
              "your last visit, " + capitalize(str) + ", I hope "+
              "you are doing well?");
    }
	return 1;
}
