/* A list of the pipesmoker emotes that look suspiciously like 
 * mariner emotes. Left in as examples.
 */

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <files.h>
#include <options.h>
#include <cmdparse.h>
#include "guild.h"

#define E(ob)        environment(ob)
#define HIS(x)        ((x)->query_possessive())
#define HIM(x)        ((x)->query_objective())
#define HE(x)         ((x)->query_pronoun())

/*
 * Function name: emote_cmdlist
 * Description:   Get the emotes available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
mapping
emote_cmdlist()
{
    return ([
      /* Command name : Function name */

      "help"         : "help",
      "marboard"     : "marboard",
      "marrigging"   : "marrigging",
      "marscorn"     : "marscorn",
      "marstand"     : "marstand",
      "marwhistle"     : "marwhistle",

    ]);
}




int
help(string str)
{
    string subject, filename;

    if(!str)
	return 0;

    if(sscanf(str, "guild %s", subject) != 1)
	if(sscanf(str, "pipesmokers %s", subject) != 1)
	    if(sscanf(str, "pipesmokers %s", subject) != 1)
		return 0;

    filename = HELP_DIR + subject;
    if(file_size(filename) > 0)
    {
	setuid();
	seteuid(getuid());
	cat(filename);
	return 1;
    }

    NF("No help on that subject I'm afraid.\n");
    return 0;
}

int
marboard(string str)
{
    if(!E(TP)->query_ship())
    {
     write("You are not on a ship to board from!\n");
     return 1;
    }

    if(strlen(str))
    {
        return 0;
    }
 
    write("You eagerly prepare to board the neighbouring ship!\n");
    allbb(" eagerly prepares to board the neighbouring ship!");
    return 1;
}


int
marrigging(string str)
{
    if(!E(TP)->query_ship())
    {
     write("You are not on a ship to check the rigging!\n");
     return 1;
    }

    if(strlen(str))
    {
        return 0;
    }
 
    write("You look around you, examining the rigging of the ship.\n");
    allbb(" looks around, examining the rigging with the keen eye of " +
          "an experienced mariner.");
    return 1;
}


int
marscorn(string str)
{
    if(!E(TP)->query_ship())
    {
     write("You are not on a ship!\n");
     return 1;
    }

    if(strlen(str))
    {
        return 0;
    }
 
    write("You scorn the crew of the ship as poor navigators.\n");
    allbb(" scorns the crew of this ship as poor navigators.");
    return 1;
}

int
marstand(string str)
{
    if(!E(TP)->query_ship())
    {
     write("You are not on the deck of a ship!\n");
     return 1;
    }

    if(strlen(str))
    {
        return 0;
    }
 
    write("You cross your arms and stand comfortably on the deck of the " +
          "rolling ship.\n");
    allbb(" crosses " +HIS(TP)+ " arms and stands comfortably on the deck " + 
          "of the rolling ship.");
    return 1;
}

int
marwhistle(string str)
{

    if(!E(TP)->query_ship())
    {
     write("Without a rolling deck beneath you, you cannot find a good " +
       "rhythm to whistle to!\n");
     return 1;
    }

    if(strlen(str))
    {
        return 0;
    }
 
    write("You begin whistling a wordless sea chanty in time with the rhythm " +
          "of the rolling deck.\n");
    allbb(" begins whistling a wordless sea chanty in time with the rhythm " + 
          "of the rolling deck.");
    return 1;
}
