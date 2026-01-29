/*
 * NE training cave
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L1_BASE_ROOM;

string practice_result(int coef);
string practice_result_others(int coef);

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
    ::create_room();
	object door;
    set_short("Training cave");
    set_long("You are standing in the northeast corner of the training area. " +
             "You see a wooden dummy for practicing unarmed combat. " +
             "\n\n");

    add_item(({"dummy", "wooden dummy"}),
             "This is a wooden column with wooden sticks. " +
             "Unarmed fighters practice different types of strikes and blocks. " +
             "\n");
    add_item(({"warrior", "warriors", "unarmed warriors"}),
             "Some goblin fighters hitting dummies trying to avoid been hit." +
             "\n");
    add_item(({"wooden column", "column"}),
             "The wooden column is main part of dummy. It rotates in " +
             "both directions. Some wooden sticks are inserted into column. \n");
    add_item(({"wooden sticks", "sticks", "stick"}),
             "The wooden sticks are inserted into wooden column on different " +
             "levels. When the column rotates these sticks may hit people" +
             " standing too close to the column. \n");
    add_item(({"area", "training area", "training cave"}),
             "In this part of the training cave fighters can " +
             "<practice unarmed combat>.\n");
    add_cmd_item( ({"column", "wooden column", "dummy", "wooden dummy"}),
                  "rotate",
                  "You slowly rotate wooden dummy. Wooden sticks are flying " +
             	  "around. You avoid being hit by stick on eye level but feel " +
                  "slight impact with your knee. Now you understand how " +
                  "dummy works.\n");

    add_exit ("roomk","west");
    add_exit ("roomj","south");
    add_npc(NPCS_DIR + "goblin1_2", 3, &->arm_me());

    door = clone_object(DOORS_DIR + "recruiter_w");
	door->move(this_object());

} /* create_room */

/*
 * Function name:		init
 * Description  :		on init hook
 */
void
init()
{
    ::init();
    add_action("practice", "practice", 0);
} /* init */

/*
 * Function name:		practice
 * Description  :		initiates practice
 */
int
practice(string s)
{
    notify_fail("Practice what? Unarmed combat?\n");
    if(s!="" && s!="unarmed combat")
        return 0;

	int coef = this_player()->query_stat(SS_CON)
	         + this_player()->query_skill(SS_UNARM_COMBAT) + random(10);
	string result = practice_result(coef);

	write(result + "\n");
	result = practice_result_others(coef);
	say(this_player()->query_name() + " " + result + "\n");
    return 1;
} /* practice */

/*
 * Function name:		practice_result
 * Description  :		returns result of practice visible by player
 */
string
practice_result(int coef)
{
	switch(coef)
	{
		case 0..80: 	return "You approach the wooden dummy and try to " +
		                       "punch it. Sadly, your fists cannot even seem to find " +
		                       "even an immobile log. You hear some laughs.";
		case 81..160: 	return "You approach wooden dummy and try to punch it. " +
		                       "You hit it once causing dummy to spin left. " +
		                       "Suddenly you feel painful hit from the right.";
		case 161..230: 	return "You hit dummy, block it and hit again. Then " +
		                       "you step back scratching sore hands.";
		case 231..300: 	return "You make quick set of kicks, punches and blocks. " +
		                       "You are satisfied with your speed and accuracy.";
		case 301..1000: return "You perfectly perform combination of hits. " +
		                       "You are real guru of martial arts.";
		default: 		return INCORRECT_PRACTICE_MSG;
	}
	return INCORRECT_PRACTICE_MSG;
} /* practice_result */

/*
 * Function name:		practice_result_others
 * Description  :		returns result of practice visible by others
 */
string
practice_result_others(int coef)
{
	switch(coef)
	{
		case 0..80: 	return "approaches wooden dummy and tries to punch it. " +
		                       "But " + this_player()->query_possessive() +
		                       " fists cannot find even immobile log. " +
		                       "You hear some laughs.";
		case 81..160: 	return "approaches wooden dummy and try to punch it. " +
		                       capitalize(this_player()->query_pronoun()) +
		                       " hits it once causing dummy to spin left. " +
		                       "Dummy turns and hits from " +
		                       this_player()->query_objective() +
		                       " the right.";
		case 161..230: 	return "hits dummy, block it and hit again. Then " +
		                       " steps back scratching sore hands.";
		case 231..300: 	return "makes quick set of kicks, punches and blocks. " +
		                       "You see satisfaction on " +
		                       this_player()->query_possessive()+ " face.";
		case 301..1000: return "perfectly performs combination of hits. " +
		                       "What a masterpiece of martial arts.";
		default: 		return INCORRECT_PRACTICE_MSG;
	}
	return INCORRECT_PRACTICE_MSG;
} /* practice_result_others */