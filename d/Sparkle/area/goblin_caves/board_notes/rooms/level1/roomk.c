/*
 * nw training cave
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
    set_short("Training cave");
    set_long("You are standing in the northwest corner of the training area. " +
             "You see what appear to be some extremely heavy sand-filled " +
             "sacks here. A number of goblins are training, using the sacks " +
             "for lifting exercises." +
             "\n\n");

    add_item(({"sacks", "sack", "sand"}),
             "There are some very heavy sacks on the floor of the cave. " +
             "Goblin fighters are training their strength by grabbing them " +
             "and carrying them around. You hear them bragging about an " +
             "upcoming competition in which they will be competing to " +
             "see who can carry them the farthest." +
             "\n");
    add_item(({"area", "training area", "training cave"}),
             "In this part of the training cave fighters can " +
             "<practice carrying sacks>.\n");

    add_exit ("rooml","east");
    add_exit ("roomi","south");
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
    notify_fail("Practice what? Carrying sacks?\n");
    if(s!="" && s!="carrying sacks")
        return 0;

	int coef = this_player()->query_stat(SS_STR)
	         + this_player()->query_stat(SS_CON) + random(10);
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
			return "You approach one sack in the corner and grab it. " +
			"Your face turns purple from the effort but the sack " +
			"doesn't move.";
		case 81..160:
			return "You grab one sack but your knees are bending " +
			"and you put it where you took it.";
		case 161..240:
			return "You come to one sack and try to push it. " +
			"You fall exhausted after a few inches.";
		case 241..320:
			return "Sack looks heavy but you succeeded to raise it. " +
			"You stepped about ten steps and put it. You need to " +
			"rest.";
		case 321..400:
			return "You take one sack. It is heavy but not that heavy. " +
			"You carrying over twenty steps and put it on the " +
			"ground. You swept sweat from your forehead.";
		case 401..1000:
			return "You take two sacks and walk around juggling them. " +
			"You see jeleous faces.";
		default: 		return INCORRECT_PRACTICE_MSG;
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
			return "approaches one sack in the corner and grabs it. " +
			capitalize(this_player()->query_possessive()) + " face turns " +
			" purple from the effort but sack doesn't move.";
		case 81..160:
			return "grabs one sack but " + this_player()->query_possessive() +
			" knees are bending and " + this_player()->query_name() +
			" puts it where you took it.";
		case 161..240:
			return "comes to one sack and tries to push it. " +
			capitalize(this_player()->query_pronoun()) +
			" fall exhausted after a few inches.";
		case 241..320:
			return "succeeded to raise a sack. " +
			capitalize(this_player()->query_pronoun()) +
			" stepped about ten steps and put it. ";
		case 321..400:
			return "takes one sack carries it over twenty steps and puts it " +
			"on the ground. " + capitalize(this_player()->query_pronoun()) +
			" swept sweat from " + this_player()->query_possessive() +
			" forehead.";
		case 401..1000:
			return "takes two sacks and walks around juggling them. " +
			"You see jeleous faces.";
		default:
			return INCORRECT_PRACTICE_MSG;
	}
	return INCORRECT_PRACTICE_MSG;
} /* practice_result_others */