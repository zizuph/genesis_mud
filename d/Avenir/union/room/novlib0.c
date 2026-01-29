/*
 * File:     novlib0.c
 * Created:  Lilith, May 2004
 * Purpose:  Library for the Novice members
 */
#pragma strict_types
#include "../defs.h"
#include "../lib/skills.h"

inherit NOVLIB;
inherit "/lib/skill_raise";

#include <ss_types.h>
#include <stdproperties.h>

/* global vars */
public object librarian;

/* prototypes */
public void set_up_skills(void);


/*
 * Function name: south_exit_block
 * Description:   Check to see if the player is carrying a library
 *                book.  This is meant to be used as a block function
 *                for exits from the library so that books cannot be
 *                removed.
 * Returns:       1/0 - book carried/not carried
 */
public int
south_exit_block(void)
{
    /* See if the player is carrying a book */
    if (::library_exit_block())
    {
	/* A book was found.  Give a warning and return 1 to block the exit */
	write("You cannot leave with a library book!\n");
	return 1;
    }

    /* No book present.  Return 0 to allow the player to exit */
    write("The roiling mists part to let you pass.\n");
    return 0;
}

/*
 * Function name: east_exit_block
 * Description:   Check to see if the player is carrying a library
 *                book.  This is meant to be used as a block function
 *                for exits from the library so that books cannot be
 *                removed.
 * Returns:       1/0 - book carried/not carried
 */
public int
east_exit_block(void)
{
    /* See if the player is carrying a book */
    if (::library_exit_block())
    {
	/* A book was found.  Give a warning and return 1 to block the exit */
	write("You cannot leave with a library book!\n");
	return 1;
    }

    /* No book present.  Return 0 to allow the player to exit */
    write("The shadows part to let you pass, seeming to kiss the "+
	"back of your neck as you leave, closing the gap behind you.\n");
    return 0;
}

/*
 * Function name: mist_exit_block
 * Description:   Check to see if the player is carrying a library
 *                book.  This is meant to be used as a block function
 *                for exits from the library so that books cannot be
 *                removed.
 * Returns:       1/0 - book carried/not carried
 */
public int
mist_exit_block(void)
{
    /* See if the player is carrying a book */
    if (::library_exit_block())
    {
	/* A book was found.  Give a warning and return 1 to block the exit */
	write("You cannot leave with a library book!\n");
	return 1;
    }

    /* Deny inactive Warriors */
    switch(SPHERE(TP))
    {
    case SPH_DUTY:
    case SPH_TRAINING:
    case SPH_ISOLATION:
	write("Such authority does not yet lie within you, that you "+
	  "can command the shadows and mists to let you pass.\n");
	return 1;
    }

    /* Allow the rest. */
    write("The shadows and mists open to your approach then swiftly "+
	"sweep closed after you pass.\n");
    return 0;
}

public int
down_exit_block(void)
{
    if (present(SWAY_ID_ALL, TP))
    {
	write("You attempt to descend, but find the way closed "+
	    "off by rather solid seeming shadows.\n");
	return 1;
    }

    write("You descend into shadow...\n");
    return 0;
}

public void
union_room(void)
{
    set_short("novice library");
    set_long("This is the library for the Novices of the Shadow Union. "+
      "The walls and high ceiling of this room are made of stone of "+
      "the deepest black, and draw most of the light from the room. "+
      "It is a spartan room whose only concession to comfort is the "+
      "group of flat grey cushions placed around the base of the "+
      "reading table. A small staircase leads upward into the "+
      "darkness. A narrow set of shelves leans against the north "+
      "wall.@@library_table_desc@@ Mist and shadows cling to the walls "+
      "and ceiling.\n");

    add_item(({"mist", "shadow", "west", "west wall"}),
      "You feel certain that there is something beyond the "+
      "shadows and mist that dance up the west wall toward "+
      "the ceiling.\n");
    add_item(({"south", "south wall"}),
      "Though your eyes cannot penetrate the mists and shadows, "+
      "you know that the pendentive lies beyond them, to the "+
      "south.\n");

    /* Wiz info for stat_object */
    add_prop(OBJ_S_WIZINFO, "This is one of the training halls "
      +"for the Union of the Warriors of Shadow. If a problem "
      +"occurs and you find it necessary to shut down the "
      +"guild, do 'Call /d/Avenir/union/list close_guild' (NOT "
      +"Call here close_guild). Note that this will shut down "
      +"ALL of the training rooms in the guild, and it will "
      +"remain so until someone calls open_guild (ie, it will "
      +"last through reboots). In other words, make sure you "
      +"have a good reason for doing it!\n");

    add_exit("pendentive", "south", south_exit_block);
    add_exit("hall_n2", "east", east_exit_block);
    add_exit("novlib1", "up", up_exit_block);
    add_exit("mist", "west", mist_exit_block, 1, 1);
    add_exit("shadow", "down", down_exit_block);

    phrases = ({
	"Seek the Sway, for within it lies Vision.",
	"Begin by attaining purity of body and soul.",
	"Allow these walls of black obsidian to induce creativity "+
	    "in all your endeavors.",
	"The matter of this stone has been transformed by Jazur to "+
	    "create its present beauty. May this knowledge help to "+
	    "calm your fears and maintain your balance during your "+
	    "impending times of change.",
	"Let it be known to you that your first task is to find "+
	"the meeting room and sign the agreement therein, producing "+
	    "a copy to show to your Mentor.",
	"When you encounter a Warrior, remember to ask: How may I "+
	    "serve thee, that I may learn the ways of the Shadow Union?",
	"At this level of your training, you shall be known as "+
	    "a Trainee of Shadow. Use <utitle> to adjust it accordingly.",
    });

    /* Setup training */
    create_skill_raise();
    set_up_skills();

    /* Setup library */
    add_book_shelf(({ "welcome"}));
    union_library(0);

    add_npc(NPC + "jarisi");
}

static void
update_vars(void)
{
    ::update_vars();
    librarian = present("jarisi");
}

/* Skill functions and hooks */
public void
set_up_skills(void)
{
    sk_add_train(SS_LANGUAGE,              /* sknum         */
      "speak and understand other tongues", /* desc*/
      0,                        /* skname        */
      2,                        /* cost factor   */
      MAX_LANGUAGE,             /* max skill     */
      SS_INT,                   /* limiting stat */
      50 );
}

/*
 * Function name: sk_improve
 * Description:   Function called when player tries to do the improve command
 * Arguments:	  str - The rest of the command player made
 * Returns:	  1/0
 */
public int
sk_improve(string str)
{
    if (GUILD_CLOSED)
    {
	write("The Union has been shut down due to problems, so "+
	    "training is impossible.\nTry back later.\n");
	return 1;
    }

    if (!present(librarian))
	return 0;

    if (!IS_MEMBER(TP))
    {
	librarian->command("eyebrow . "+ TP->query_real_name());
	librarian->command("say I think not.");
	return 1;
    }

    if (U_IS_PUNISHED(TP, U_PUNISHED_NOTRAIN))
    {
	librarian->command("us I have been told that you "+
	    "are to be denied instruction.");
	librarian->command("smile sadly");
	return 1;
    }

    if (!STATE)
    {
	librarian->command("us You have let the flame go out. I "+
	    "will teach you nothing.\n");
	return 1;
    }

    if (IS_MEMBER(TP) && ENEMY(TP))
    {
	librarian->command("us Traitor and fool! Do you honestly "+
	    "think I will teach you after your actions?");
	librarian->command("shout Begone before I slay you!");
	return 1;
    }

    return ::sk_improve(str);
}

public varargs int
sk_query_max(int sknum, int silent)
{
    int max;

    switch(sknum)
    {
    case SS_LANGUAGE:   max = TP->query_stat(SS_INT);     break;
    default:            max = TP->query_stat(SS_INT);     break;
    }

    /* Players that are trainees will not be able to train very high */
    if (TP->query_skill(OCC_LEVEL) < NORMAL)
	max = 50;

    return min(max, ::sk_query_max(sknum, silent));
}

/*
 * Function name: sk_hook_cant_train
 * Description:   Player can't train that skill that high for some reason
 * Arguments:	  skill  - The skill
 *		  to_lev - The level to wich the player wanted training
 * Returns:	  0
 */
public int
sk_hook_cant_train(string skill, int to_lev)
{
    write("You fail to adopt what "+ librarian->query_the_name(TP) +
	" attempts to teach you.\n");
    librarian->command("emote looks disappointed.");
    return 1;
}

/*
 * Function name: sk_hook_learn_known
 * Description:	  Player wants to learn an already known skill
 * Arguments:	  skill - The skill
 * Returns:	  0
 */
public int
sk_hook_learn_known(string skill)
{
    notify_fail("You already know that skill, try to practice it.\n");
    return 0;
}

/*
 * Function name: sk_hook_no_list_learn
 * Description:   No more unknown skills for the player in this guild
 * Returns:       1
 */
public int
sk_hook_no_list_learn(void)
{
    write("For you there are no unknown skills here. You might want to "+
	"practice those you already know.\n");
    return 1;
}

public void
init(void)
{
    ::init();

    if (!IS_MEMBER(TP))
	return;

    add_action(sk_improve, "learn");
    add_action(sk_improve, "train");
    add_action(sk_improve, "improve");
}
