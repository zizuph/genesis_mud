/*
 * SW training cave
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L1_BASE_ROOM;

string practice_result(int coef);

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
    ::create_room();
    set_short("Training cave");
    set_long("You are standing in the southwest corner of the training area. " +
             "There are some mannequins for training in throwing knives. " +
             "You can see an opening in the western wall." +
             "\n\n");

    add_item(({"knives", "throwing knives", "table"}),
             "You can see some throwing knives on the table." +
             "\n");
    add_item(({"mannequins", "mannequin", "target", "targets"}),
             "Mannequins have been set up here, many of which are covered " +
             "with puncture wounds. A few have knives sticking out of them, " +
             "probably the result of target practice which takes " +
             "place here.\n");
    add_item(({"area", "training area", "training cave"}),
             "In this part of the training cave fighters can " +
             "<practice throwing knives>.\n");
	add_item(({"opening", "small opening", "western wall"}),
			 "You can see a small opening in the western wall. " +
             "This is the way you got in. Maybe this way you can also " +
             "get back to the main cave.\n");

    add_exit ("roomj","east");
    add_exit ("roomk","north");
    add_npc(NPCS_DIR + "goblin1_2", 3, &->arm_me());

    reset_room();
} /* create_room */

/*
 * Function name:		init
 * Description  :		on init hook
 */
void
init()
{
    ::init();
    add_action("enter", "enter", 0);
    add_action("practice", "practice", 0);
} /* init */

/*
 * Function name:		practice
 * Description  :		initiates practice
 */
int
practice(string s)
{
    notify_fail("Practice what? Throwing knives?\n");
    if(s!="" && s!="throwing" && s!="throwing knives")
        return 0;

	int coef = this_player()->query_stat(SS_DEX)
	         + this_player()->query_stat(SS_STR) + random(10);
	string result = practice_result(coef);

	write("You throw some knives and " + result + ".\n");
	say(this_player()->query_name() + " throws some knives and "
	    + result + ".\n");
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
		case 0..80: return "all of them miss the target";
		case 81..160: return "one of them scratches the mannequin";
		case 161..240: return "one hits right in the center of target and " +
		                      "one hits " +
		                      one_of_list(({"right leg",
		                                    "left leg",
		                                    "right arm",
		                                    "left arm",
		                                    "head"})) +
		                      " with knife handle";
		case 241..320: return "all of them hit mannequin in different places";
		case 321..400: return "all of them hit center of the target";
		case 401..1000: return "one by one blades are shreding mannequin " +
             "into pieces.";
		default: 		return INCORRECT_PRACTICE_MSG;
	}
	return INCORRECT_PRACTICE_MSG;
} /* practice_result */

/*
 * Function name:		enter
 * Description  :		enters into roomg
 */
int
enter(string s)
{
    notify_fail("Enter what?\n");
    if(s!="" && s!="opening")
        return 0;

    set_dircmd("opening");
    TP->move_living("into the opening", ROOMS_DIR + "level1/roomg");
    return 1;
} /* enter */