/*
 * death_room.c
 *
 * The place where Mascarvin grants rebirth to Sybarites.
 *
 *   Lucius, May 25, 2007
 *
 * Based on original design by:
 * Khail, Nov. 15/96
 * Mrpr 901119
 * Tintin 911031
 * Nick 920211
 */
#pragma no_clone
#pragma no_shadow
#pragma strict_types

#include "death.h"
#include <stdproperties.h>

inherit "/std/room";

/* Global vars */
private static object death;
private static mapping deaths = ([]);

#define HOUR	3600
#define DAY	(24 * HOUR)
#define DC	death->command

public void
create_room(void)
{
    set_short("Mascarvin's Realm");
    set_long("You are hovering in cloistered blackness. "+
	"Faint, reddish light pulses with parturience from "+
	"veins in what seem to be thick walls, themselves "+
	"seeming to pulse but a half-second behind. This space, "+
	"while feeling close with intimacy, begets feelings of "+
	"infinite spaciousness as well, such that the true measure "+
	"of its limits are incalculable. The lagged, twin-pulses "+
	"steal your sense of time, pulling you into complacency.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
}

/*
 * Function name: test_reincarnate
 * Description  : Simply ensures that 'who' is no longer a
 *                valid object pointer. It should have been
 *                destroyed by the reincarnate() function. If
 *                it still exists, try again with a new 
 *                death mark.
 * Arguments    : object who - Object pointer to test for
 *                             existance.
 */
private void
test_reincarnate(object who)
{
    if (objectp(who))
	clone_object(DEATH_MARK)->move(who, 1);
}

/*
 * Function name: reincarnate_me
 * Description  : Starts the actual reincarnation process for
 *                the player.
 * Arguments    : object who - Object pointer to the player to
 *                             send to the bodies room.
 */
private void
reincarnate_me(object who)
{
    object mark;

    if (!who || !query_interactive(who) || !who->query_ghost())
	return;

    /* Remove the player's death mark. */
    while(mark = present(DEATH_MARK_ID, who))
	mark->remove_object();

    /* Add the player's name & number of deaths this
     * login to the 'deaths' mapping.
     */
    deaths[who->query_real_name()] = time();

    /* A little backup system. If 'who' still exists
     * after reincarnate() is called, something's wrong,
     * so call test_reincarnate for confirmation in 1 sec.
     */
    set_alarm(1.0, 0.0, &test_reincarnate(who));

    /* Ok, let's try to reincarnate. This should destroy the
     * player's normal body, give him a ghost body,
     * /d/Genesis/login/ghost_player.c, and move him to the
     * bodies room, and we're done with him.
     */
    who->reincarnate();
}

/*
 * Function name: create_death
 * Description  : Clones mascarvin into the room, if she's not already
 *                present.
 */
private void
create_death(void)
{
    if (!death)
	death = clone_object(DEATH);

    if (!present(death, this_object()))
	death->move(this_object());
}

/*
 * Function name: test_for_player
 * Description  : A little security to make sure the player
 *                doesn't go LD or slip out of the room somehow
 *                during the death sequence.
 * Arguments    : object who - The player to test.
 * Returns      : 0 - The player is not longer valid for death.
 *                1 - The player is still listening, keep talking.
 */
private int
test_for_player(object who)
{
    if (!who || !objectp(who))
	return 0;

    /* If 'who' is non-interactive, try to make them quit. */
    if (!query_interactive(who))
    {
	/* Make sure they've got a death mark before quitting them. */
	if (!present(DEATH_MARK_ID, who))
	    clone_object(DEATH_MARK)->move(who, 1);

	who->command("$quit");
	return 0;
    }

    /* If the player is no longer in the room and is still a ghost
     * bring them back.
     */
    if (environment(who) != this_object())
    {
	if (who->query_ghost())
	{
	    tell_object(who, "You hear Mascarvin whisper: " +
		"Only I may grant your rebirth!\n\n");

	    who->move_living("X", this_object(), 1, 0);
	    return 1;
	}

	return 0;
    }

    return 1;
}

/*
 * The messages of death, messages1 handles deaths that haven't occured
 * for awhile.
 */
private void
messages1(int count, object who)
{
    /* Make sure player's still here. */
    if (!test_for_player(who))
	return;

    switch(++count)
    {
    case 1:
	tell_object(who, "Vision slowly returns and you make out a "+
	    "tall, pale female before you, her posture "+
	    "lending itself to an expression of sadness.\n\n");
	break;
    case 2:
	tell_object(who, "Mascarvin mournfully breathes: "+
	    "And so another sybarite falls.\n\nHer arms spread "+
	    "open into a welcoming embrace.\n\n");
	    
	break;
    case 3:
	tell_object(who, "You don't recall taking the steps, but "+
	    "find yourself within Mascarvin's arms, the strength of "+
	    "her hold soothing as she holds you to her bosom.\n\n");
	break;
    case 4:
	tell_object(who, "Time unremarked flows past neither slow "+
	    "nor fast as you recuperate, suckling at Mascarvin's "+
	    "breast.\n\nHer essence fills you with soothing fluidity, "+
	    "nourishing the remnants of your soul.\n\n");
	break;
    case 5:
	tell_object(who, "All too soon you are gently disengaged and "+
	    "feel yourself petted in a warm and soft embrace.\n\n"+
	    "Mascarvin breathes: It is not yet your time to serve me "+
	    "and I see in you the seeds of things left undone.\n\n");
	break;
    case 6:
	tell_object(who, "Mascarvin continues to breathe words "+
	    "of sympathy, but you are already lulled, your senses "+
	    "dulled and drifting towards catatonia.\n\n");
	break;
    case 7:
	tell_object(who, "Suddenly your senses return and you find "+
	    "yourself alone, adrift...\n\nYou hear Mascarvin whisper: "+
	    "It is arranged, your rebirth is assured. Go now.\n\n"+
	    "From one blink to the next, you find yourself in a "+
	    "new place...\n");
	break;
    }

    /* If final count, reincarnate. */
    if (count >= 7)
	reincarnate_me(who);
    else
	set_alarm(itof(5 + random(11)), 0.0, &messages1(count, who));
}

/*
 * The messages of death, messages2 handles repeated deaths within
 * a certain amount of time.
 */
private void
messages2(int count, object who)
{
    /* Make sure player's still here. */
    if (!test_for_player(who))
	return;

    switch(++count)
    {
    case 1:
	tell_object(who, "Vision slowly returns and you make out a "+
	    "tall, pale female before you, her posture "+
	    "lending itself to an expression of sadness.\n\n");
	break;
    case 2:
	tell_object(who, "Mascarvin mournfully breathes: "+
	    "And so anoth...\n\nHer pale hands settle on her hips as " +
	    "she regards you closer, scrutinizing your presence.\n\n");
	break;
    case 3:
	tell_object(who, "Her lips slowly transform into a "+
	    "disgusted sneer.\n\nMascarvin breathes: Truly, I had "+
	    "not expected to see you again so soon.\n\n");
	break;
    case 4:
	tell_object(who, "Mascarvin breathes: I will grant you "+
	    "another rebirth, but know that you try my patience.\n\n");
	break;
    case 5:
	tell_object(who, "In silence, her gaze hinting at a "+
	    "malevolent future, Mascarvin snaps her fingers "+
	    "and once more you find yourself in a familiar place...\n");
	break;
    }

    /* If final count, reincarnate. */
    if (count >= 5)
	reincarnate_me(who);
    else
	set_alarm(itof(5 + random(11)), 0.0, &messages2(count, who));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!ob || !living(ob) || ob->query_npc())
	return;

    if (!ob->query_ghost())
    {
	tell_object(ob, "You feel that your presence is unwelcome "+
	    "here and are transferred elsewhere.\n");
	ob->move_living("X", ob->query_default_start_location());
	return;
    }

    create_death(); 

    int last = time() - deaths[ob->query_real_name()];

    if (last < (DAY * 2))
	messages2(0, ob);
    else
	messages1(0, ob);
}

/*
 * Function name: all_cmd
 * Description  : Evaluates a command a player attempted 
 *                to use. If it's one of a very small list
 *                of basic commands, allow it. Otherwise,
 *                block it.
 * Arguments    : string str - Arguments to the command the
 *                player attempted.
 * Returns      : 0 - failure, keep threading.
 *                1 - success, halt execution.
 */
public int
all_cmd(string str)
{
    /* For anyone not a wizard, thread halts here. */
    if (this_player()->query_wiz_level())
	return 0;

    switch(query_verb())
    {
    case "quit":
    case "exa":
    case "look":
    case "l":
    case "help":
    case "bug":
    case "typo":
    case "idea":
    case "praise":
    case "sysbug":
	return 0;
    }

    /* Anything not in the switch we're going to block. */
    write("That is impossible in your immaterial state.\n");
    return 1;
}

public void
init(void)
{
    ::init();
    add_action(all_cmd, "", 1);
}
