/*
This NPC has been placed in the private directory
because it contains a quest-riddle thats answer should
be kept away from as many people as possible *grin*

-Arman
*/
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <wa_types.h>


inherit AM_FILE


EMOTE_HOOK

public void do_nod(object actor, string adverb);
void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("guardian");
    set_adj("stone");
    set_short("stone guardian");
    set_gender("G_MALE");
    set_long("Before you stands a great stone monolith in " +
      "the shape of a large solemn male human. He stares " +
      "west out into the mist as if looking for something " +
      "you cannot see. He also stands before the entrance " +
      "of the temple in a vigil that will probably last " +
      "for eternity.\n");

    set_stats(({160,119,170,89,89,110}));
    set_hp(query_max_hp());
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);
    add_prop(OBJ_M_NO_ATTACK,"How do you plan to kill " +
      "something made of stone?\n");

    set_alignment(100);
    set_knight_prestige(-1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_default_answer("The stone guardian magically " +
      "begins to talk: Throughout the Ages, I have guarded " +
      "this entrance. Only those who complete the Test of " +
      "Wisdom may pass me.\n");


    add_ask(({"test","test of wisdom","Test of Wisdom"}),
      VBFC_ME("test_of_wisdom"));

    add_emote_hook("nod",2.0,do_nod);

}

init_living()
{
    add_action("enter_temple","state");
}

int
enter_temple(string str)
{
    if(str == "e")
    {
	write("You state your" +
	  " answer to the stone guardian.\n");
	say(QCTNAME(TP) + " states " + POSSESSIVE(TP) + 
	  " answer to the stone guardian.\n");
	command("say you have chosen wisely.");
	write("The stone guardian allows you to pass into " +
	  "the temple.\n");
	say("The stone guardian allows " + QTNAME(TP) +
	  " into the temple.\n");
	TP->move_living("M",CROOM + "temp2",1,0);
	return 1;
    }
    if(str == "hourglass")
    {
	write("You state your answer to the stone guardian.\n");
	say(QCTNAME(TP) + " states " + POSSESSIVE(TP) +
	  " his answer to the stone guardian.\n");
	command("say You try and fool me with stolen knowledge? " +
	  "Fool! Feel now the wrath of the gods!");
	write("The clouds open up, and you are struck by " +
	  "lightning!\n");
	say("The clouds open up, and " + QCTNAME(TP) +
	  " is struck by a bolt of lightning!\n");
	TP->set_hp(0);
	TP->heal_hp(-200);
	TP->do_die(TO);
	say("The clouds rumble ominously.\n");
	return 1;
    }
    else
	write("You state your answer to the stone guardian.\n");
    say(QCTNAME(TP) + " states " + POSSESSIVE(TP) +
      " answer to the stone guardian.\n");
    command("say You have chosen poorly.");
    return 1;
}

string
test_of_wisdom()
{
    command("emote magically says: To complete the Test of " +
      "Wisdom, you must answer my riddle.");
    command("emote magically says: But be warned! You must answer " +
      "one of many riddles correctly. Incorrect answers I mostly " +
      "dismiss, but if you answer incorrectly the answer to another " +
      "riddle, I will destroy you.");
    command("emote magically says: 'The beginning of eternity. " +
      "The end of time and space. The start of every end, " +
      "and the end of every place. What am I?'.\nState " +
      "your answer when an answer you come by. Seek not the " +
      "wisdom of others, or the gods will judge you accordingly.");

    return "";
}

public void
do_nod(object actor, string adverb)
{
    command("nod");
    return;
}

