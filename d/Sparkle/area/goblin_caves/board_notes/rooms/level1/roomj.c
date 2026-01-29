/*
 * SE training cave
 * Boreaulam, April 2012
 */
#include "defs.h"
#include <language.h>
#include <composite.h>
#include <stdproperties.h>
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
    set_short("Training cave");
    set_long("You are standing in the southeast corner of the training area. " +
             "You see a stage with sliding blades. " +
             "\n\n");

    add_item(({"stage", "sliding blades", "blades"}),
             "There is set of sliding blades on the stage. " +
             "They are moving with different speeds and intervals. " +
             "You can practice avoiding blades on this stage." +
             "\n");
    add_item(({"area", "training area", "training cave"}),
             "In this part of the training cave fighters can " +
             "<practice avoiding blades>.\n");

    add_exit ("roomi","west");
    add_exit ("rooml","north");
    add_npc(NPCS_DIR + "goblin1_2", 3, &->arm_me());

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
    notify_fail("Practice what? Avoiding blades?\n");
    if(s!="" && s!="avoiding blades")
        return 0;

	int coef = this_player()->query_stat(SS_DEX)
	         + this_player()->query_stat(SS_DIS) + random(10);
	string result = practice_result(coef);

	write(result + "\n");
	result = practice_result_others(coef);
	say(this_player()->query_name() + " " + result + "\n");
    return 1;
}/* practice */

/*
 * Function name:		practice_result
 * Description  :		returns result of practice visible by player
 */
string
practice_result(int coef)
{
	switch(coef)
	{
		case 0..80:
			return "Even looking on these fast moving blades makes shiver.";
		case 81..160:
			return "You get up on stage, getting closer... but with " +
    		"first swing of blade you back away.";
		case 161..240:
			return "You jump on stage ready for challenge. " +
			"Ducking first few blades you get hit by third one " +
			"and fall on the ground.";
		case 241..320:
			return "You analyze tempo of blades and start moving around them. " +
			"You progress well when suddenly big hammer hits you from " +
			"left side and throws you away.";
		case 321..400:
			return "You narrow your concentration, shutting out all reality " +
			"other than the blades before you. Slowly working your way " +
			"forward, stepping back occasionally as a blade comes in at " +
			"an odd angle, you manage to pass this test.";
		case 401..1000:
			return "You easily dance around blades. Crowd applauds.";
		default:
			return INCORRECT_PRACTICE_MSG;
	}
	return INCORRECT_PRACTICE_MSG;
}/* practice_result */

/*
 * Function name:		practice_result_others
 * Description  :		returns result of practice visible by others
 */
string
practice_result_others(int coef)
{
	switch(coef)
	{
		case 0..80:
			return "looks on blades with pale face.";
		case 81..160:
			return "gets up on stage, getting closer... but with " +
			"first swing of blade backs away.";
		case 161..240:
			return "jumps on stage ready for challenge. " +
			"Ducking first few blades " + this_player()->query_name() +
			" gets hit by third one and falls on the ground.";
		case 241..320:
			return "analyzes tempo of blades and starts moving around them. " +
			capitalize(this_player()->query_pronoun()) +
			" progresses well when suddenly " +
			"big hammer hits " + this_player()->query_possessive() +
			" from left side and throws away.";
		case 321..400:
			return "concentrates on only on blades ignoring other reality. " +
			"Going forward slowly, sometimes stepping back helps " +
			this_player()->query_possessive() + " to pass this test.";
		case 401..1000:
			return "easily dances around blades. Crowd around you applauds.";
		default:
			return INCORRECT_PRACTICE_MSG;
	}
	return INCORRECT_PRACTICE_MSG;
} /* practice_result_others */