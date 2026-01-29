#pragma strict_types
/*
    This is the final room in the Zodiac quest. It handles the
	quest reward. It was coded by Dust during the time he
	was coding the Zodiac quest, around late 1992.

    Modified: 13 June 2003, by Bleys
	- Updated to use modern Terel defs
	- Now logging to the correct quest log
	- Changed damage done to be lethal in every case. Before it
	    did max_hp/2 + 500 damage, which would only kill
	    relatively small mortals. It's now equal opportunity,
	    and will kill regardless of size. I think "all the
	    power of heaven and hell" justifies that kind of
	    potency, not to mention the very high rewards for
	    this quest.
	- Also added logging for the failure case, just for fun.

    Modified: 20 Aug 2003, by Bleys
	- Updated logging for failure to include mortal hit points.

    Modified: 18 Apr 2007, by Lucius
        - Updated to add a reminder and some cleanups.

    Modified: 16 Jul 2009, by Petros
        - Fixed runtime in pressing buttons when 7th button is hit.
          We now properly call clear_buffer
*/

#include "/d/Terel/include/Terel.h"

inherit STDROOM;

#include <macros.h>
#include <math.h>
#include "/d/Terel/include/quest_bits.h"

#include "/d/Terel/include/zodiac.h"

#define PORDIR (MANSION + "porcia/")
#define DOOR   (DUST_DIR + "secret_door")


/*
 * This room contains the secret door
 */

private object door;          /* The door */
private object last_player;   /* The last player who pressed a key */
private int   *seq_pressed;   /* The buttons already pressed */
private int    pressed;       /* The number of buttons already pressed */
private int    clear_buff_id;

private mapping zod_bits = ([
    0 : ({ QUEST_DEATH_GROUP, QUEST_DEATH_BIT }),
    1 : ({  QUEST_FIRE_GROUP, QUEST_FIRE_BIT  }),
    2 : ({   QUEST_POR_GROUP, QUEST_POR_BIT   }),
    3 : ({   QUEST_BAL_GROUP, QUEST_BAL_BIT   }),
    4 : ({   QUEST_CHI_GROUP, QUEST_CHI_BIT   }),
    5 : ({  QUEST_MAZE_GROUP, QUEST_MAZE_BIT  }),
]);

public void
create_room(void)
{
    setuid();
    seteuid(getuid());

    set_long("@@long_desc");
    set_short("door room");

    add_item("rainbow", "It's the picture of a rainbow " +
      "shimmering in the rainbow colors red, orange, yellow, " +
      "green, blue and violet.\n");
    add_item("picture", "It's the picture of a rainbow " +
      "shimmering in the rainbow colors red, orange, yellow, " +
      "green, blue and violet.\n");
    add_item(({"zodiac","circle","sign","signs","button","buttons"}),
      "The circle consists of twelve buttons, each " +
      "marked with one of the twelve zodiac signs. You can probably " +
      "press the buttons. A faint smudge, like that of a handprint, "+
      "lies in the center of the circle.\n");
    add_item(({"smudge","handprint","center"}), "It looks to be a smudged "+
	"palm print. A tingling sensation runs along your fingers as your "+
	"eyes linger upon it, seeming to invite you to touch it.\n");
    add_item("smoke", "@@my_smoke");
    add_item("aries","\n" +
      "  **       **\n" +
      " *  *     *  *\n" +
      "     *   *\n" +
      "      * *\n" +
      "      ***\n" +
      "       *\n" +
      "       *\n\n");
    add_item("taurus","\n" +
      " *         *\n" +
      " **       **\n" +
      "  ***   ***\n" +
      "    *****\n" +
      "   *     *\n" +
      "   *     *\n" +
      "    *****\n\n");
    add_item("gemini","\n" +
      " ***       ***\n" +
      "   *********\n" +
      "     *   *\n" +
      "     *   *\n" +
      "     *   *\n" +
      "   *********\n" +
      " ***       ***\n\n");
    add_item("cancer","\n" +
      "    ******\n" +
      "  ***    ****\n" +
      " ** **\n" +
      "  ***    ***\n" +
      "        ** **\n" +
      " ****    ***\n" +
      "    ******\n\n");
    add_item("leo","\n" +
      "    ******\n" +
      "  ***    ***\n" +
      " **        **\n" +
      " *          *\n" +
      " **        **\n" +
      "  ***    ***\n" +
      " ** **  **\n" +
      "  ***    ***\n\n");
    add_item("virgo","\n" +
      "  ** ** ** **\n" +
      " *  *  *  *  *\n" +
      "    *  *  *  *\n" +
      "    *  *  * **\n" +
      "    *  *  * *\n" +
      "    *  *  * *\n" +
      "    *  *  *\n\n");
    add_item("libra","\n" +
      "      ***\n" +
      "    *** ***\n" +
      "    *     *\n" +
      " ** **   ** **\n" +
      "  ****   ****\n" +
      "\n" +
      "  ***********\n\n");
    add_item("scorpio","\n" +
      "  ** ** **\n" +
      " *  *  *  *\n" +
      "    *  *  *\n" +
      "    *  *  *\n" +
      "    *  *  *\n" +
      "    *  *  ** **\n" +
      "           ***\n\n");
    add_item("sagittarius","\n" +
      " **    ********\n" +
      "  ***     *** *\n" +
      "    *** ***   *\n" +
      "      ***     *\n" +
      "    *** ***\n" +
      "  ***     ***\n" +
      " **         ***\n\n");
    add_item("capricorn","\n" +
      "   ********\n" +
      "       ***\n" +
      "     ***\n" +
      "   *** ***\n" +
      " ***     **\n" +
      " **       *\n" +
      "  ***   ***\n" +
      "    *****\n\n");
    add_item("aquarius","\n" +
      "    ****  ****\n" +
      " ****  ****  ****\n" +
      "\n" +
      "    ****  ****\n" +
      " ****  ****  ****\n\n");
    add_item("pisces","\n" +
      " *           *\n" +
      " **         **\n" +
      "  *         *\n" +
      "  **       **\n" +
      "  ***********\n" +
      "  **       **\n" +
      "  *         *\n" +
      " **         **\n" +
      " *           *\n\n");

    add_exit(PORDIR + "tunnel", "south", 0, 0);
    add_exit(MANSION + "tri4", "north", 0, 0);

    /* The secret door leads west */
    door = clone_object(DOOR);
    door->move(TO);

    /* The door lock has buttons... */
    /* We add a command for each button that can be pressed */
    for (pressed = 0; pressed< NBR_SIGS; pressed++)
	add_cmd_item(SIGS[pressed], "press", "@@do_press|"+ pressed +"@@");

    /* The handprint that gives out a review / hint. */
    add_cmd_item(({"smudge","handprint","center","circle","door",}),
	({"touch","press"}), "@@do_touch");

    pressed = 0;
    last_player = 0;
    seq_pressed = allocate(SEQ_LEN);
}

public string
long_desc(void)
{
    return "A shiver goes through your entire body as you enter " +
      "this room. Everything looks rotten, and cobwebs are hanging " +
      "from the ceiling. However, to the west you can see a door made " +
      "of silver, which is completely free of dust and cobwebs. Above " +
      "the door you can read the words 'Something Wicked This Way " +
      "Comes'. Over the north exit you can see the picture of " +
      "a rainbow.\n" + ((pressed + 1) == SEQ_LEN ?
	  "You notice some purple, stinking smoke near the door.\n" : "");
}

public string
my_smoke(void)
{
    if ((pressed + 1) == SEQ_LEN)
    {
	return "The purple smoke smells very strong. It's a smell that " +
	    "reminds you of ozone. An inner voice tells you to be " +
	    "very careful!\n";
    }
    else
    {
	return "You don't see any smoke. However, you vaguely smell "+
	    "something.\n";
    }
}

/*
 * clear_buffer just sets pressed to 0 (and so empties the
 * internal buffer of already pressed buttons). It is called
 * a minute after no key was pressed. Also, last_player is emptied.
 */
private void
clear_buffer(void)
{
    /* Give a hint to the players about the reset */
    if (last_player)
    {
	tell_room(TO,
	  "The silver door flickers for a second. " +
	  "You don't know why, but somehow you now feel safer " +
	  "than you felt just a second ago.\n");
    }

    pressed = 0;
    last_player = 0;
    clear_buff_id = 0;
    seq_pressed = allocate(SEQ_LEN);
}

/* Test each of the 6 quest bits to see if they have actually done it.
 * Pass 'group' to check if any have been done.
 * Pass 'group' & 'bit' to check specific.
 */
public varargs int
check_bits(object who, int group = -1, int bit = -1)
{
    int val;

    if (!objectp(who))
	who = this_player();

    if ((group >= 0) && (bit >= 0))
	return who->test_bit("Terel", group, bit);

    foreach(int key, int *data : zod_bits)
    {
	if (!who->test_bit("Terel", data[0], data[1]))
	    return 0;

	if (group >= 0)
	    return 1;

	val++;
    }

    return val;
}

/*
 * The following function handle the pressing of buttons
 */

public string
do_press(string str)
{
    int damage;
    int index;
    int solved;
    int exp_to_give;

    /* First, check if it's still the same (or a new) player */
    if (TP != last_player) {
	clear_buffer();
	last_player = TP;
    }

    /* Then transform the text argument (vbfc) to an int */
    sscanf(str, "%d", index);

    /* Unlock door if the user got the right order */
    write("You press the " + SIGS[index] + " button.\n");
    say(QCTNAME(TP) + " presses the " + SIGS[index] + " button.\n");

    // Added a check to make sure that we don't throw a runtime when
    // someone has already pressed all 6 buttons and clear_buffer has
    // not yet been called. 
    if (pressed >= SEQ_LEN)
    {
        return "You hear a voice telling you: Your failure makes you "
            + "unworthy to open the door at this time! Meditate on "
            + "this before trying again!\n";
    }
    
    /* Restart the timeout for resetting the sequence */
    remove_alarm(clear_buff_id);
    clear_buff_id = set_alarm(120.0, 0.0, &clear_buffer());

    /* Store the new button in the queue */
    seq_pressed[pressed] = index;

    /* Check for right solution if sequence is full */
    if (++pressed == SEQ_LEN)
    {
	int i, total;
	for (; i < SEQ_LEN; i++)
	{
	    if (seq_pressed[i] != calc_hint(i))
		break;

	    total++;
	}

	solved = (total == SEQ_LEN);
    }
    
    if (solved)
    {
	/* Check if the player already solved it */
	if (check_bits(TP, QUEST_ZOD_GROUP, QUEST_ZOD_BIT))
	{
	    clear_buffer();
	    return("You hear a voice telling you: Nobody can open this "+
		"door more than once in his life.\n");
	}

	/* Give xp only if the player solved all subquests */
	if (!check_bits(TP))
	{
	    clear_buffer();
	    return ("You hear a voice telling you: You are not considered "+
		"worthy enough to enter this room.\n");
	}

	if (!door->door_solved())
	    return("Sorry, the door is not locked!\n");

	/* Set the quest bit, to indicate they have completed it. */
	TP->set_bit(QUEST_ZOD_GROUP, QUEST_ZOD_BIT);

	/* Now, give the player xp, but only players with total xp larger
	 * than QUEST_ZOD_EXP will get the full amount. */
	exp_to_give = TP->query_exp();
	if (exp_to_give > QUEST_ZOD_EXP)
	    exp_to_give = QUEST_ZOD_EXP;
	TP->add_exp_quest(exp_to_give);

	/*
	// This was the original log entry.   -Bleys
	write_file(QUEST_LOG, TP->query_name() + " solved ZODIAC-quest (" +
			      ctime(time()) + ")\n");
	*/
	write_file(QUEST_LOG, TP->query_name() + " solved " +
	  "the Zodiac quest (ZODIAC-quest) (" + ctime(time()) + ")\n");

	say(QCTNAME(TP) + " looks more experienced.\n");
	return ("Suddenly you feel MUCH more experienced and " +
	  "enlightened than before!\n");
    }

    /* If the player pressed a wrong sequence, damage him */
    if (pressed == SEQ_LEN)
    {
	write("A beam of cosmic energy, bundling all the power " +
	  "of heaven and hell, emerges from the center of " +
	  "the zodiac circle and hits you directly on your " +
	  "forehead. You are thrown back through the room by " +
	  "this enormous power! You don't know if you're " +
	  "alive or dead - Your whole life appears in front " +
	  "of your eyes! You scream!! (Now why didn't you " +
	  "follow your inner voice not to press the last button?\n");
	say("Suddenly, a beam of cosmic energy bundling all the power " +
	  "of the heaven and hell comes out of the center of the " +
	  "zodiac circle and hits " + QTNAME(TP) + " directly on " +
	  TP->query_possessive() + " forehead. Fortunately you " +
	  "can keep out of the beam!\n");

	remove_alarm(clear_buff_id);

	str = TP->query_name() + " tried to open the Zodiac door, "+
	    "but failed. Damage done: " + damage +
	    ". Mortal's hit points: " + TP->query_hp() + " of " +
	    TP->query_max_hp() +". Timestamp: " + ctime(time()) +
	    "\n\tSequence:";

	/* Log what buttons they pressed on failure. */
	foreach(int val : seq_pressed)
	    str += " " + SIGS[val];

	write_file(FAIL_LOG, str + "\n");
	return "";
    }

    /* warn player if next key is the dangerous one */
    if ((pressed + 1) == SEQ_LEN)
    {
	tell_room(TO, "Some small amount of purple and stinking smoke " +
	  "appears from behind the door. It starts to vanish " +
	  "immediately.\n");
	return("Suddenly you wonder what would happen if you pressed " +
	  "another button... But you feel scared and an inner voice " +
	  "tells you not to try it out, but to run away...\n");
    }

    return "";
}

/* Give a hint on what they've accomplished. */
public string
do_touch(void)
{
    /* Print something. */
    write("You raise your hand and press it to the center "+
	"of the Zodiac.\n");
    say(QCTNAME(TP) +" raises "+ TP->query_possessive() +
	" hand and presses it to the center of the Zodiac.\n");

    /* Finished the quest? */
    if (check_bits(TP, QUEST_ZOD_GROUP, QUEST_ZOD_BIT))
	return "Your hand pulses with the sense of past accomplishment.\n";

    /* Didn't do any of the sub-quests? */
    if (!check_bits(TP, 1))
	return "Your fingers tingle for the need of works left undone.\n";

    write("\nAn almost burning sensation creeps from your "+
	"fingertips and up your arm, then filling your mind "+
	"with these images:\n\n");

    foreach(int key, int *data : zod_bits)
    {
	int index;

	if (!check_bits(TP, data[0], data[1]))
	    continue;

	index = calc_hint(key);
	write("\t"+ CAP(LANG_ADDART(HINT[key])) + SIGEQ[index] +".\n");
    }

    return "";
}
