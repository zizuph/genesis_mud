/*
 * Level 2 bartender - darts quest
 * Boreaulam, Sep 2014
 */
#pragma save_binary
#pragma strict_types


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "defs.h"

inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

/*
 * Function name:        create_monster
 * Description  :        constructor for the object
 */
void
create_monster()
{
    set_adj("drunk");
    set_adj("shaking");
    set_name("leighton");
    set_short("drunk shaking goblin");
    set_race_name("goblin");

    set_long("The drunk shaking goblin is the bartender of the local pub. " +
			 "A quick glance is enough to guess that this goblin probably " +
			 "drinks more of his stock than his customers do! His shaking " +
             "hands are holding some sharp looking darts." +
             "\n");

    add_prop(OBJ_M_NO_ATTACK, "You do not think it would be a good idea " +
        "to attack the drunk goblin. Those darts do look pretty sharp, " +
        "and it looks like he has practice hitting the bullseye.\n");
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 0);
	set_base_stat(SS_STR, 90 + random(10));
	set_base_stat(SS_DEX, 80 + random(10));
	set_base_stat(SS_CON, 90 + random(10));
	set_base_stat(SS_INT, 40 + random(10));
	set_base_stat(SS_WIS, 60 + random(10));
	set_base_stat(SS_DIS, 40 + random(10));
    set_skill(SS_WEP_KNIFE, 90 + random(10));
    set_skill(SS_PARRY, 90 + random(10));
    set_skill(SS_DEFENCE, 90 + random(10));
    set_skill(SS_UNARM_COMBAT, 90 + random(10));
    set_skill(SS_BLIND_COMBAT, 90 + random(10));
    set_skill(SS_AWARENESS, 80 + random(10));

	add_ask( ({ "task", "help", "quest"}),
	        "@@ask_help@@", 1);
	add_ask( ({ "darts", "game", "darts board", "board"}),
	        "@@ask_darts@@", 1);
	set_default_answer("@@ask_default");

	add_chat("Darts is a game for real warriors!");
	add_chat("Can you hit a board with these?");
    set_chat_time(40);
} /* create_monster */

/*
 * Function name:        ask_help
 * Description  :        result for ask "help"
 */
string
ask_help()
{
	if(this_player()->test_bit("Sparkle",
	GOBLIN_DARTS_GROUP,
	GOBLIN_DARTS_BIT2)) {
		return "say There is nothing you can do to help. Thanks.";
	} else {
		command("sips some beer and points at a darts board.");
		command("say Amuse me, show me your skill in a game of darts.");
		return "smile";
   }
} /* ask_help */

/*
 * Function name:        ask_default
 * Description  :        result for ask for unknown asks
 */
string
ask_default()
{	return "The goblin bartender says: I cannot help you with that.\n";
} /* ask_default */

/*
 * Function name:        ask_darts
 * Description  :        result for ask "darts"
 */
string
ask_darts()
{
	if(!this_player()->test_bit("Sparkle",
	GOBLIN_DARTS_GROUP,
	GOBLIN_DARTS_BIT1)) {
		command("sigh sadly");
		return "say Try to finish the game within " + LEVEL2_DARTS_LIMIT +
			" attempts. But if you want to show me that you are really " +
            "good, you need to finish within nine attempts. Maybe then I " +
            "can give you an even better reward?";
    }
	if(!this_player()->test_bit("Sparkle",
	GOBLIN_DARTS_GROUP,
	GOBLIN_DARTS_BIT2)) {
		command("sigh sadly");
		return "say You showed some skill. But if you want to show me " +
            "that you are really good, you need to finish within nine " +
            "attempts. Maybe then I can give you an even better reward?";
    }
	return "say I remember you! You have mastered the game of darts! I " +
        "don't have a reward for you today, but I certainly enjoy watching " +
        "how you play.";
	

} /* ask_darts */

