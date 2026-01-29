inherit "/std/monster";
inherit "/std/act/action";

#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
	set_name("puck");
	set_race_name("dwarf");
	add_adj("jovial");
	add_adj("big");
	set_short("big jovial dwarf");
	set_long("This dwarf is clearly insane. His rantings "+
	   "are enough to drive anyone to do something rash.\n");

	set_stats(({ 100, 100, 250, 50, 50, 100 }));
	set_skill(SS_DEFENCE, 40);
	set_skill(SS_WEP_AXE, 40);
	set_skill(SS_PARRY, 20);
	set_skill(SS_2H_COMBAT, 40);

	set_alignment(0);

	refresh_mobile();

	set_chat_time(1);
	add_chat("You're doing that wrong!");
	add_chat("I'll sell you my pocket lint for 300 "+
	   "platinum coins, okay?");
	add_chat("You are stupid. I am smart.");
	add_chat("I am SO great.");
	add_chat("No one is better than me.");
	add_chat("Anything you can do, I can do better.");
	add_chat("I have the best ideas but no one will listen "+
	   "to me.");
	add_chat("I want everything my way and there will be no "+
	   "compromises.");
	add_chat("I am the coolest thing to ever hit this universe.");
	add_chat("Wanna play a game? I'll win.");
	add_chat("People are out to get me because I am so good and I "+
	   "am never wrong and they are just always jealous of me "+
	   "because I am so perfect and good looking and incredible.");

	set_act_time(2);
	add_act("fart");
	add_act("burp the");
	add_act("puke");
	add_act("blush lou");
	add_act("burp polit");
	add_act("emote screams seductively");
	add_act("shout I AM BETTER THAN EVERYONE!!!");
	add_act("primps with himself.");
	add_act("throws a temper tantrum because you aren't kissing "+
	   "his feet.");


	set_cchat_time(1);
	add_cchat("I am not wrong!!");
	add_cchat("You aren't doing that right!");
	add_cchat("You WILL listen to me!");
	add_cchat("You are a wimp!");
	add_cchat("I WILL get my title back! You can't stop me!");
	add_cchat("I'm telling!");
	add_cchat("If you beat me it's only because you cheated!");
	add_cchat("You can't do this! It's HARRASSMENT! That's "+
	   "illegal!");
	add_cchat("You're just mad because I beat you!");
	add_cchat("You need to stop letting other people talk you "+
	   "into these things.");
	add_cchat("I know someone put you up to this!!");


	set_cact_time(2);
	add_cact("wiggle noi");
	add_cact("twinkle dang");
	add_cact("emote tries to tell you what to do.");
	add_cact("emote acts like he's the king's son.");
	add_cact("emote tickles himself silly.");
	add_cact("jump theo");
	add_cact("shout What do you mean you won't buy my pocket "+
	   "lint!!?");

	set_alarm(1.0, 0.0, "arm_me");
}
arm_me()
{
	seteuid(getuid(TO));
	clone_object(A_WEP_D +"axe2")->move(TO);
	clone_object(A_WEP_D +"rustyaxe")->move(TO);
	clone_object(A_ARM_D +"burlap")->move(TO);
	clone_object(A_ARM_D +"dirtyrobe")->move(TO);
	clone_object(A_ARM_D +"lhat")->move(TO);

	command("wear all");
	command("wield all");
}

query_knight_prestige(){return 20;}
