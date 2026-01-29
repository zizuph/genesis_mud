/*
 * /d/Gondor/common/dwarf_guild/obj/die.c
 *
 * Copyright (C) Stas van der Schaaf - September 20 1995
 *               Mercade @ Genesis
 *
 * This is a die, roll it or toss it. ;-)
 *
 * To allow for a more general implementation of dice-games, this die can
 * call a function in the a game linked to this die. Therefore the function
 * set_game_link(object game_link) must be called before the die is rolled.
 * As a result, the following function is called:
 *
 * game_link->dice_rolled(int *results);
 *
 * where int *results is an array of int with the numbers being rolled. This
 * array is not sorted in any way, i.e. ({ 3, 2, 6 }).
 *
 * It is also possible to cheat with this die ;-) All you have to do is
 * call the function roll() with a second argument, i.e. the exact results
 * you want to have, i.e. ({ 3, 2, 6 }) and this will make sure that exactly
 * that result appears. Note that the function roll is dependant on
 * this_player() so that object must point to the npc rolling the dice.
 *
 * Note that the value of this die must be the same as the value that is
 * displayed at the pricelist at the pub in the Rockfriend Guild.
 */

#pragma save_binary

inherit "/std/object";
inherit "/lib/keep";

#include "/d/Gondor/defs.h"
#include "../dwarf.h"
#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#define DIE_ID  (DWARVEN_RACE_GUILD_PREFIX + "die")
#define DIE_PID (DWARVEN_RACE_GUILD_PREFIX + "dice")
#define DIE_MAX (6)
#define VALUE   (57)
#define NUM_S   (3)
#define TEMP_ROCKFRIEND_DIE_CHECKED ("_temp_rockfriend_die_checked")
#define SIDES ( ({ ({ "   ", " * ", "   " }), \
		   ({ " * ", "   ", " * " }), \
		   ({ "  *", " * ", "*  " }), \
		   ({ "* *", "   ", "* *" }), \
		   ({ "* *", " * ", "* *" }), \
		   ({ "* *", "* *", "* *" }) }) )

/*
 * Global variable.
 */
static private object game_link = 0;

/*
 * Prototype.
 */
string flip(string str);
string roll(string str, int *cheat_results);

void
create_object()
{
    set_name("die");
    add_name("cube");
    add_name(DIE_ID);

    set_adj("ivory");
    add_adj("white");
    add_adj("small");

    set_pname("dice");
    add_pname("cubes");
    add_pname("ivories");
    add_pname(DIE_PID);

    set_short("ivory die");
    set_pshort("ivory dice");
    set_long(BSN("It is a small, ivory die, polished to an almost perfect " +
	"cube, though with rounded edges. On each side a number from one " +
	"to six is punched. A die can be rolled or tossed in the air."));

    add_item( ({ "ivory" }),
	BSN("The die is made of ivory, carved out of the trunk of an " +
	"oliphaunt. It is a rather rare material that is hard, yet not " +
	"as hard as iron. The dots forming the numbers have been stamped " +
	"into the ivory with great force. The ivory has been polished " +
	"and it very smooth. In it you see a complex structure of shades " +
	"of white."));
    add_item( ({ "side", "sides" }),
	BSN("On the different sides of the die different patterns of dots " +
	"can be seen."));
    add_item( ({ "pattern", "patterns", "dot", "dots" }),
	BSN("You carefully examine the patterns of dots on the different " +
	"sides of the ivory die and find the following configuration of " +
	"dots on them.") +
"    +-----+    +-----+    +-----+    +-----+    +-----+    +-----+\n" +
"    |     |    |  *  |    |   * |    | * * |    | * * |    | * * |\n" +
"    |  *  |    |     |    |  *  |    |     |    |  *  |    | * * |\n" +
"    |     |    |  *  |    | *   |    | * * |    | * * |    | * * |\n" +
"    +-----+    +-----+    +-----+    +-----+    +-----+    +-----+\n");

    add_prop(OBJ_I_VALUE,  VALUE);
    add_prop(OBJ_I_VOLUME,  1);
    add_prop(OBJ_I_WEIGHT, 10);
}

void
init()
{
    ::init();

    add_action(flip, "flip");
    add_action(roll, "roll");
    add_action(roll, "throw");
    add_action(flip, "toss");
}

/*
 * Function name: parse_die
 * Description  : This function checks whether the command line argument is
 *                valid and if so, parses the dice the player wants to
 *                manipulate.
 * Arguments    : string str - the command line argument.
 * Returns      : int - the number of dice the player wants to handle.
 */
private int
parse_die(string str)
{
    object *oblist;
    object *tmpoblist;

    if (!strlen(str))
    {
	NFN0(CAP(query_verb()) + " what?");
    }

    parse_command(LOW(str), ENV(TP), "[the] %i", oblist);
    oblist = NORMAL_ACCESS(oblist, 0, 0);

    if (!sizeof(oblist))
    {
	NFN0(CAP(query_verb()) + " what?");
    }

    tmpoblist = filter(oblist,
	&operator(==)(MASTER) @ &function_exists("create_object"));

    if (sizeof(tmpoblist) != sizeof(oblist))
    {
	NFN0("You can only " + query_verb() + " dice.");
    }

    oblist = filter(oblist, &operator(==)(TP) @ environment);

    if (!sizeof(oblist))
    {
	NFN0("You can only " + query_verb() + " dice you carry.");
    }

    if (sizeof(oblist) > 6)
    {
	NFN0("Don't " + query_verb() + " more than six dice at a time.");
    }

    return sizeof(oblist);
}

int
flip(string str)
{
    int size;
    int multi;

    if (TP->query_prop(TEMP_ROCKFRIEND_DIE_CHECKED))
    {
	return 0;
    }

    size = parse_die(str);
    if (!size)
    {
	object tp = TP;
	tp->add_prop(TEMP_ROCKFRIEND_DIE_CHECKED, 1);
	set_alarm(0.1, 0.0, &tp->remove_prop(TEMP_ROCKFRIEND_DIE_CHECKED));

	return 0;
    }

    multi = (size > 1);
    WRITE("You " + query_verb() + " " +
	(multi ? (LANG_WNUM(size) + " ivory dice") : "an ivory die") +
	" in the air and then catch " + (multi ? "them" : "it") + " again.");
    SAY(((query_verb() == "flip") ? " flips " : " tosses ") +
	(multi ? (LANG_WNUM(size) + " ivory dice") : "an ivory die") +
	" in the air and then " + PRONOUN(TP) + " catches " +
	(multi ? "them" : "it") + " again.");
    return 1;
}

/*
 * Function name: roll
 * Description  : This function is called when the player executes the
 *                'roll' command. If you want to cheat, you can call this
 *                function with a second argument that contains the values
 *                for the dice to turn up.
 * Arguments    : string str         - the command line argument.
 *                int *cheat_results - the values to pre-set.
 * Returns      : int 1/0 - success/failure.
 */
varargs int
roll(string str, int *cheat_results)
{
    int size;
    int index;
    int index2;
    int *results = ({ });

    if (TP->query_prop(TEMP_ROCKFRIEND_DIE_CHECKED))
    {
	return 0;
    }

    /* Cheat! Heh, let the guy pay! */
    if (pointerp(cheat_results))
    {
	size = sizeof(cheat_results);
	index = -1;
	while(++index < size)
	{
	    results += ({ --cheat_results[index] });
	}
    }
    else
    {
	if (!(size = parse_die(str)))
	{
	    object tp = TP;
	    tp->add_prop(TEMP_ROCKFRIEND_DIE_CHECKED, 1);
	    set_alarm(0.1, 0.0, &tp->remove_prop(TEMP_ROCKFRIEND_DIE_CHECKED));
	    return 0;
	}

	/* If we don't cheat, we have to be true and generate the results. */
	index = -1;
	while(++index < size)
	{
	    results += ({ random(DIE_MAX) });
	}
    }

    /* Print the top of the die/dice. */
    str = "";
    index = -1;
    while(++index < size)
    {
	str += "    +-----+";
    }

    /* Print the values of the die/dice. */
    str += "\n";
    index = -1;
    while(++index < NUM_S)
    {
    	index2 = -1;
    	while(++index2 < size)
    	{
	    str += "    | " + SIDES[results[index2]][index] + " |";
	}
	str += "\n";
    }

    /* Print the bottom of the die/dice and raise the result by one in
     * order to give a 'normal' result to the linked game.
     */
    index = -1;
    while(++index < size)
    {
	str += "    +-----+";
	results[index]++;
    }

    size = (size > 1);
    write(BSN("You shuffle " + (size ? ("some dice") : "a die") +
	" in your hand and roll " + (size ? "them" : "it") +
	". Before picking " + (size ? "them" : "it") +
	" up again, you see the following number" + (size ? "s" : "") +
	" displayed:") + str + "\n");
    SAY(" shuffles " + (size ? "some dice" : "a die") + " in " +
	POSSESSIVE(TP) + " hand and roll " + (size ? "them" : "it") +
	". Before " + PRONOUN(TP) + " picks " + (size ? "them" : "it") +
	" up again, you see the following number" + (size ? "s" : "") +
	" displayed:");
    say(str + "\n");

    /* This function call is the interface between the dice and the game
     * the player is playing the dice are being rolled. This way the game
     * can allow for some result based on the dice being rolled.
     */
    game_link->dice_rolled(results);
    return 1;
}

/*
 * Function name: set_game_link
 * Description  : This function should be called by the game the player is
 *                playing to allow the dice to pass the results of a throw
 *                to the game being played.
 * Arguments    : object obj - the link to the game.
 */
void
set_game_link(object obj)
{
    game_link = obj;
}

/*
 * Function name: query_game_link
 * Description  : Where there is a set function, there must be a query
 *                function too to return the objectpointer to the game that
 *                these dice are linked to.
 * Returns      : object - the objectpointer to the game.
 */
object
query_game_link()
{
    return game_link;
}

/*
 * Function name: query_recover
 * Description  : This function returns the recover string to make this die
 *                recover.
 * Returns      : string - the recover string.
 */
string
query_recover()
{
    return (MASTER + ":" + query_keep_recover());
}

/*
 * Function name: init_recover
 * Description  : This function is called when the object recovers to set
 *                the keep protection back in place.
 * Arguments    : string - the recovery argument.
 */
void
init_recover(string arg)
{
    init_keep_recover(arg);
}