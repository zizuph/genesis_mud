/*
 * /d/Gondor/mordor/obj/balance_colour.c
 *
 * This is a quest-item. The quest consists of six balls in three colours,
 * two red, two white and two blue. Each colour comes in a light and a
 * heavy one. The three heavier ones are equally heavy and the three
 * lighter ones are equally light. The task is to find out which are the
 * light ones and which are the heavy ones in only two separate weighs.
 *
 * /Mercade, 5 June 1994
 *
 * Revision history:
 */

#pragma no_inherit   /* no messing with a quest object */
#pragma strict_types /* you should be tidy             */

inherit "/std/object";

#include <filter_funs.h>
#include <language.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/mordor/ungol/tower_quest.h"

#define LIGHT          1   /* identify a light ball */
#define HEAVY          2   /* identify a heavy ball */
#define NUM_BALLS      3   /* == number of colours  */
#define MAX_TRIES      2   /* if more... no show... */
#define SHUFFLE_TIME 300.0 /* before it resets.     */
#define COLOURS      ({ "red", "white", "blue" })

/* Global variables, they are secure.
 */
static object  player       = 0;
static int    *balls        = allocate(6);
static int     tries        = 0;
static int     player_alarm = 0;

/*
 * Function name: create_object
 * Description  : Called to create and define the object.
 */
nomask void
create_object()
{
    set_name("balance");
    set_pname("balances");

    set_adj("wooden");
    set_adj("old");

    set_short("old wooden balance");
    set_pshort("old wooden balances"); /* should never happen. */
    set_long(BSN("It is an old wooden balance. It has two scales that can " +
	"be used to weigh the balls with that lie in the bowl at the foot " +
	"of the balance. If you want to play with the balance, you should " +
	"read the instructions first."));

    add_item( ({ "instructions" }),
	BSN("If you can read English you can read them."));
    add_item( ({ "scale", "scales", "left scale", "right scales" }),
	BSN("The scales are made of metal and with a few chains they are " +
	"attached to the arms of the balance. In the balance, balls can " +
	"be put to weigh them against eachother."));
    add_item( ({ "bowl" }),
	BSN("On the foot of the balance is a bowl in which all six balls " +
	"are placed when they are not being weighed. The two red balls are " +
	"called one and two, the two white balls are called three and four " +
	"and the two blue balls are called five and six."));
    add_cmd_item( ({ "instructions" }), ({ "read" }),
	BSN("In the bowl at the foot of the balance you will find six ball, " +
	"two red ones, two white ones and two blue ones. The red ones are " +
	"called one and two, the white ones are called three and four and " +
	"the blue balls are called five and six. Apart from their colour, " +
	"all balls look the same. For each colour there is a light ball and " +
	"a slightly heavier ball. The light balls (one red, one white and " +
	"one blue) are equally heavy and heavier balls (also one red, one " +
	"white and one blue) are also equally heavy.") +
	BSN("Your task is to distinguish which three balls are the light " +
	"balls using one two weighs. To weigh balls, you can use the " +
	"following syntax (example):") +
	BSN("    \"weigh 1 against 2\"") +
	BSN("    \"weigh 1, 2 against 3, 4\"") +
	BSN("    \"weigh 1, 2, 3 against 4, 5, 6\"") +
	BSN("Once you think you know the solution, you can use the " +
	"following syntax to make that known. Note that you always have " +
	"to name one red ball, one blue ball and one white ball (example):") +
	BSN("    \"solution 1, 3, 5\"") +
	BSN("In order to shuffle the balls and start over again, you can " +
	"always do \"shuffle\"."));

    add_prop(OBJ_I_VALUE,     187);
    add_prop(OBJ_I_VOLUME,  10976);
    add_prop(OBJ_I_WEIGHT,  18743);
    add_prop(OBJ_M_NO_STEAL,    1);
    add_prop(OBJ_M_NO_TELEPORT, 1);
    add_prop(OBJ_M_NO_GET,
	BSN("You decide to leave the balance here for future players."));
    add_prop(OBJ_M_NO_SELL,
	BSN("The balance is too old to be sold. It is useless."));
    add_prop(OBJ_S_WIZINFO,
	BSN("This balance is a quest-item. Just examine it to get the " +
	"information."));

    FIX_EUID;

    set_alarm(0.0, 0.0, "shuffle_balls");
}

/*
 * Function name: shuffle_balls
 * Description  : This function is called to assign values to the balls.
 *                For each colour there will be a light ball and a heavy
 *                ball.
 */
nomask void
shuffle_balls()
{
    int index;
    int weight;

    if (player_alarm)
    {
	remove_alarm(player_alarm);
    }

    player_alarm = 0;
    player       = 0;
    tries        = 0;

    for (index = 0; index < NUM_BALLS; index++)
    {
	weight = random(2);

	balls[(index * 2)]     = LIGHT + weight;
	balls[(index * 2) + 1] = HEAVY - weight;
    }
}

/*
 * Function name: reset_object
 * Description  : Reset the object after some time if no interactice player
 *                is present.
 */
nomask void
reset_object()
{
    /* Only reset if no players are in the room.
     */
    if (sizeof(FILTER_PLAYERS(all_inventory(environment()))))
    {
	return;
    }

    shuffle_balls();
}

/*
 * Function name: reset_player
 * Description  : After a player has used the balance to weigh some balls,
 *                s/he has SHUFFLE_TIME seconds to weigh again or enter a
 *                solution before the balls auto-shuffle.
 */
nomask void
reset_player()
{
    shuffle_balls();

    tell_room(ENV(), BSN("Suddenly the balls in the bowl at the foot of " +
	"the balance start to move and it appears they shuffle themselves."));
}

/*
 * Function name: init
 * Description  : Adds the necessary commands to the player if s/he enters
 *                the room the balance is in.
 */
nomask void
init()
{
    ::init();

    add_action("shuffle",  "shuffle");
    add_action("solution", "solution");
    add_action("weigh",    "weigh");
}

/*
 * Function name: try_to_reward_player
 * Description  : When a player solves the quest, s/he might be rewarded.
 */
void
try_to_reward_player()
{
    object tp = TP;

    /* Give the player a hint after solving the problem.
     */
    WRITE("After finding the solution, you pick up one of the balls " +
	"and read the characters \"" +
	BALANCE_RWB_GROUP[NAME2NUM(tp->query_real_name(),
	    sizeof(BALANCE_RWB_HINTS), BALANCE_RWB_CODE)] +
	"\" written on it. You decide to put the ball back in the bowl.");

    /* The player apparently solved the quest before.
     */
    if (tp->test_bit(DOMAIN_NAME, BALANCE_RWB_GROUP, BALANCE_RWB_BIT))
    {
/*
	write_file(QUEST_LOG, BALANCE_RWB_NAME + " RE-Solved by " +
	    CAP(tp->query_real_name()) + " (" + tp->query_average_stat() +
	    ") on " + ctime(time()) + " without exp.\n");
*/
	WRITE("You feel that your experience on solving these types of " +
	    "problems is confirmed by solving this particular problem again.");

	return;
    }

    /* if possible, check whether the solution can be logically computed
     * from the weighs by the player.
     */
/*
    write_file(QUEST_LOG, BALANCE_RWB_NAME + " Solved by " +
	CAP(tp->query_real_name()) + " (" + tp->query_average_stat() +
	") on " + ctime(time()) + " for " + BALANCE_RWB_EXP + " exp.\n");
*/
    WRITE("You feel more experienced.");
    SAYBB(" smiles like " + PRONOUN(tp) + " just became more experienced.");

    tp->add_exp(BALANCE_RWB_EXP, 0); /* Yi-HAAA! */
    tp->set_bit(BALANCE_RWB_GROUP, BALANCE_RWB_BIT);
}

/*
 * Function name: shuffle
 * Description  : The command used to reset the balance if the player wants
 *                to re-shuffle the balls.
 * Arguments    : string - the command line argument.
 * Returns      : 1/0    - success/failure.
 */
nomask int
shuffle(string str)
{
    object tp = TP;

    if (!parse_command(str, tp, " [the] [wooden] 'balance' "))
    {
	NFN0(CAP(query_verb()) + " what?");
    }

    /* If someone else is in the same environment as the player is, it is
     * not allowed to mess with the balance.
     */
    if (objectp(player) &&
	(player != tp) &&
	(ENV(player) == ENV(tp)))
    {
	WRITE("You cannot shuffle the " + short() + " since " +
	    player->query_the_name(tp) + " is playing with the balance.");
	return 1;
    }

    shuffle_balls();

    WRITE("You put all the balls in the bowl and shuffle them carefully. " +
	"There is no way of telling which ball is which any more.");
    SAY(" puts all the balls in the bowl and shuffles them carefully. " +
	"There is no way of telling which ball is which any more.");

    return 1;
}

/*
 * Function name: scale_to_balls
 * Description  : From the players imput per scale, deduce the balls that
 *                s/he wants to weigh on that scale.
 * Arguments    : string - the player imput for a scale.
 * Returns      : int *  - the numbers of the balls on the scale.
 */
nomask int *
scale_to_balls(string scale)
{
    int     index;
    int    *scale_balls = ({ });
    string *on_scale;

    /* Remove all spaces and explode on comma's.
     */
    on_scale = explode(implode(explode(scale, " "), ""), ",");

    for (index = 0; index < sizeof(on_scale); index++)
    {
	scale_balls += ({ LANG_NUMW(on_scale[index]) });

	if ((scale_balls[index] <= 0) ||
	    (scale_balls[index] > (NUM_BALLS * 2)))
	{
	    return 0;
	}
    }

    return scale_balls;
}

/*
 * Function name: summarize_balls
 * Description  : Take the numbers of the balls and compute their compound
 *                weight.
 * Arguments    : int * - the numbers of the balls.
 * Returns      : int   - their total weight.
 */
nomask int
summarize_balls(int *scale_balls)
{
    int index;
    int sum = 0;

    for (index = 0; index < sizeof(balls); index++)
    {
	sum += balls[(scale_balls[index] + 1)];
    }

    return sum;
}

/*
 * Function name: not_unique
 * Description  : Check whether the balls on one scale are unique.
 * Arguments    : int * - the numbers of the balls.
 * Returns      : int   - 1/0 - not unique/unique
 */
int
not_unique(int *scale_balls)
{
    int index;

    for (index = (sizeof(scale_balls) - 1); index >= 0; index--)
    {
	if (member_array(scale_balls[index], scale_balls) != index)
	{
	    return 1;
	}
    }

    return 0;
}

/*
 * Function name: incorrect_colours
 * Description  : Find out whether the player selected balls of all three
 *                colours when s/he enters a solution.
 * Arguments    : int * - the numbers of the balls.
 * Returns      : int   - 1/0 - incorrect colours/correct colours.
 */
int
incorrect_colours(int *scale_balls)
{
    int  index;
    int *test_balls;

    for (index = 0; index < NUM_BALLS; index++)
    {
	/* Need to typecast for else I get a problem with the types.
	 */
	test_balls = ({ (index * 2), ((index * 2) + 1) });
	if (sizeof(scale_balls & test_balls) != 1)
	{
	    return 1;
	}
    }

    return 0;
}

/*
 * Function name: solution
 * Description  : The command a player uses to enter a solution to the
 *                quest. It tests the solution and tries to assess whether
 *                the player indeed found the solution or guesses.
 * Arguments    : string - the command line argument.
 * Returns      : 1/0    - success/failure.
 */
nomask int
solution(string str)
{
    int *proposal;

    if (!strlen(str))
    {
	NFN0("What solution? Do (for example) \"solution 1, 3, 5\".");
    }

    if (sizeof(proposal = scale_to_balls(str)) != 3)
    {
	NFN0("You should always select three balls for your solution, one " +
	    "red ball, one white ball and one blue ball.");
    }

    if (not_unique(proposal))
    {
	NFN0("Please name each ball only once.");
    }

    if (incorrect_colours(proposal))
    {
	NFN0("You must select one red ball, one white ball and one blue " +
	    "ball for the solution.");
    }

    if (tries > MAX_TRIES)
    {
	WRITE("You have used more than " + MAX_TRIES + " tries and your " +
	    "solution can therefore not be accepted.");

	shuffle_balls();

	return 1;
    }

    /* If you didn't use MAX_TRIES tries, you must have cheated
     * If the weights of the balls don't add up to NUM_BALLS, the solution
     * is not correct.
     */
    if ((tries != MAX_TRIES) ||
	(summarize_balls(proposal) != NUM_BALLS))
    {
	WRITE("Unfortunately that is not the correct solution.");

	shuffle_balls();

	return 1;
    }

    WRITE("Congratulations. That is the correct solution.");

    try_to_reward_player();

    shuffle_balls();

    return 1;
}

/*
 * Function name: weigh
 * Description  : The command players use in order to weigh two or more
 *                balls against eachother.
 * Arguments    : string - the command line argument.
 * Returns      : 1/0    - success/failure.
 */
nomask int
weigh(string str)
{
    object tp = TP;
    string scale_left;
    string scale_right;
    string result;
    int   *balls_left;
    int   *balls_right;
    int    difference;

    if (objectp(player) &&
	(player != tp) &&
	(ENV(tp) == ENV(player)))
    {
	NFN0("You cannot use the balance since " + player->query_the_name(tp) +
	    "is using the scales. You have to wait until " + PRONOUN(tp) +
	    " leaves the room, shuffles the balls or submits a solution.");
    }

    if (!strlen(str))
    {
	NFN0("Weigh what against what?");
    }

    if (sscanf(str, "%s against %s", scale_left, scale_right) != 2)
    {
	NFN0("Weigh what against what?");
    }

    if (sizeof(balls_left = scale_to_balls(scale_left)) == 0)
    {
	NFN0("Incorrect syntax on left scale. See the instructions.");
    }

    if (sizeof(balls_right = scale_to_balls(scale_right)) == 0)
    {
	NFN0("Incorrect syntax on right scale. See the instructions.");
    }

    if (sizeof(balls_left) != sizeof(balls_right))
    {
	NFN0("You must weigh an equal number of balls on either side.");
    }

    if (sizeof(balls_left & balls_right))
    {
	NFN0("Each ball can only be at one side at a time.");
    }

    if ((not_unique(balls_left)) || (not_unique(balls_right)))
    {
	NFN0("Please name each ball only once.");
    }

    if (player_alarm)
    {
	remove_alarm(player_alarm);
    }

    player_alarm = set_alarm(SHUFFLE_TIME, 0.0, "reset_player");

    player = tp;
    tries += 1;
    difference = summarize_balls(balls_left) - summarize_balls(balls_right);

    switch(difference)
    {
    case -10..-1:
	result = "The balance bends to the right.";
	break;

    case       0:
	result = "The scales remain in equilibrium.";
	break;

    case   1..10:
	result = "The balance bends to the left.";
	break;

    default:
	result = "One of the balls rolls of a scale. This should not have " +
	    "happened. Please make a bugreport about this.";
	break;	
    }

    SAYBB(" puts some balls on the scale to weigh them. After examining " +
	"the result, " + PRONOUN(tp) + " puts the balls in the bowl on the " +
	"foot of the balance again.");
    WRITE("You put the balls on the scales and wait to see what happens. " +
	result + " After having examined the result, you take the balls " +
	"from the scales and put the in the bowl on the foot of the balance " +
	"again.");

    return 1;
}

/*
 * Function name: query_prevent_shadow
 * Description  : A safety function to prevent shadowing of this object.
 * Returns      : 1 - always.
 */
nomask int
query_prevent_shadow()
{
    return 1;
}
