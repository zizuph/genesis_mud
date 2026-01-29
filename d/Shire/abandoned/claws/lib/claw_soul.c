/* 
 * This is the command soul for the Black Claw Guild.
 * All emotes, special attack commands and such will be placed in this
 * file.
 * Turgon 2 september '98
 *
 * Modification log:
 *
 *
 */
#pragma strict_types

inherit "/cmd/std/command_driver";

#include "/d/Shire/guild/claws/claw_defs.h"
#include <macros.h>
#include "/d/Shire/defs.h"

#define MAXEMOTES 6
/* 
 * Function:	get_soul_id
 * Desc:	Give a name for this soul
 * Returns:	string - the soul's id
 */
string 
get_soul_id()
{
	return GUILD_NAME + " soul";
}

/*
 * Function:	query_cmd_soul
 * Desc:		identify this to be a valid commandsoul
 * Returns:		1
 */
int
query_cmd_soul()
{
	return 1;
}

/*
 * Function:	query_cmdlist
 * Desc:		Get the commands available for the soul and the
 *				functions which belong to each of them.
 * Usage:		command name : Function name
 * Returns:		mapping - a mapping that maps the command names
 *				to function names.
 */
mapping
query_cmdlist()
{
	return 
		([
			"cspeak"	: "cspeak", //Talking the orcish language.
			"cyell"		: "cyell",  //Yell in an orcish manner.
			"cwarn"		: "cwarn",  //Way of warning someone.
			"cswear"	: "cswear", //Swear upon someone, randomly choosen.
			"claugh"	: "claugh", //Laugh with orcish laughter.
			//"claw"		: "do_claw",
			// To be added later. A special attack.
			"ccurse"	: "ccurse",	//Curse someone disliked.
			"cfrown"	: "cfrown"  //Frown upon something.
/*----------NOTE: ADD NEW EMOTES/SPECIALS BELOW THIS LINE!! ---------------*/
		]);
}
/* 
 * Function Name: ccurse
 * Description:   An emote, where the player can curse someone, or if
 *                no arguments given, curses someone from a list randomly.
 * Arguments:     who - who to curse.
 * Returns:       1 - If successful, 0 - if it fails.
 */
int
ccurse(string str)
{
	object *oblist;
	int i;
	i = random(6);
	
/*If you have an objectpointer 'obj' then living(obj) will*/
/*be true for a living, and false for a non-living.*/

	if (!strlen(str))
	{
	  switch(i)
	  {
		case 1:
		{
		  write("You curse the elves to burn in the dungeons of "+
			"the Dark Lord!\n");
		  all2act(QCTNAME(TP)+" curses the elves to burn in the dungeons "+
			"of the Dark Lord!\n");
		  break;
		}

		case 2:
		{
		  write("You curse the dwarves and their foolish beards!\n");
		  all2act(QCTNAME(TP)+" curses the dwarves and their foolish "+
			"beards!\n");
		  break;
		}
		case 3:
		{
		  write("You curse the name of Durin, the dwarven beggar, "+
			"the headless!\n");
		  all2act(QCTNAME(TP)+" the name of Durin, the beggar, "+
			"the headless!\n");
		  break;
		}

		case 4:
		{
		  write("You curse the Eldar, pompous and cowardly warriors!\n");
		  all2act(QCTNAME(TP)+" curses the Eldar, pompous and cowardly "+
			"warriors!\n");
		  break;
		}

		case 5:
		{
		  write("You curse the Dunedain, hoping they perish in the wrath "+
			"of the One!\n");
		  all2act(QCTNAME(TP)+" curses the Dunedain, hoping they perish "+
			"with the wrath of the One!!\n");
		  break;
		}

		case 6:
		{
		  write("You curse the hobbits, dimwitted, small coward creatures "+
			"as they be!\n");
		  all2act(QCTNAME(TP)+" curses the hobbits, dimwitted, small "+
			"creatures as they be!\n");
		  break;
		}
	  }
	}
	oblist = parse_this(str, "[the] %i");
	if (!sizeof(oblist))
	{
	  write("What do you wish to curse?\n");
	  return 1;
	}

	if (!living(oblist[0]))
	{
	  write("You curse the "+oblist[0]->short())+" for it's total lack of use!.\n");
	  all2act("curses the",oblist," for it's total lack of use!\n");
	  return 1;
	}

	actor("You curse",oblist, " to eternal damnation in the dungeons of "+
		"the Dark Lord!");
	target(" curses you to eternal damnation in the dungeons of "+
		"the Dark Lord!",oblist);
	all2act("curses",oblist, " to eternal damnation in the dungeons of "+
		"the Dark Lord!\n");
	write("You hiss out: Yea be damned! Must thy rot in the chambers of "+
		"torment!\n");
	say(QCTNAME(TP)+" hisses: Yea be damned! Must thy rot in the dark "+
		"chambers of torment!\n");
	return 1;
}

/* 
 * Function Name: cfrown
 * Description:   An emote, where the player simply frowns in his orcish, disgustly
 *                manner.
 * Arguments:     No arguments.
 * Returns:       1 - if success, 0 - if failure
 */
/* 
 * Function Name: claugh
 * Description:   An emote, where the player laughs at someone in an orcish manner,
 *                or if no arguments given, just laughs.
 * Arguments:     Who - who to laugh at
 * Returns:       1 - if success, 0 - if failure.
 */
/* 
 * Function Name: cwarn
 * Description:   An emote, where the player might warn someone specific, by 
 *                showing of his claws.
 * Arguments:     who - who to give your warning to.
 * Returns:       1 - if success, 0 - if failure.
 */
/* 
 * Function Name: cyell
 * Description:   An emote, where the player yells the orcish yell (?), a shriek ?
 *                The power of the yell will be decided by the occup guild stat, also
 *                if the Captain yells in presence of lower ranked members, they will
 *                be terrified.
 * Arguments:     No arguments.
 * Returns:       1.
 */
int
cyell(string str)
{
	object *pl;

	if (strlen(str))
		return 0;

	

	
/* 
 * Function Name: cspeak
 * Description:   This is for the player to communicate with other orcs, in their
 *                own language, so noone else understand what they say. People
 *                with good general language skill might be able to understand.
 * Arguments:     string - what to speak.
 *                who    - who to send the string to.
 * Returns:       1 - if success, 0 - if failure.
 */
/* 
 * Function Name: cswear
 * Description:   An emote, where the player can swear just like good orcs can.
 * Arguments:     No arguments.
 * Returns:       1.
 */
