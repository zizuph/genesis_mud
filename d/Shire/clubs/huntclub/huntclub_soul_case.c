/*
 * /d/Shire/clubs/huntclub/huntclub_soul.c 
 *
 * The Hunter/Huntresse's Club Soul
 *
 * Special thanks to Carnak for doing the heavy lifting!
 * Tomas - November 2017
 *
 * Modification log:
 */
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/help.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "huntclub.h"
#include "/d/Shire/sys/defs.h"

/* Prototypes */
public int tally(string name);


string
query_auto_load()
{
   seteuid(getuid());
   return MASTER_OB(TO);
}

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Hunters Huntress Club"; }


/*
 * Function name: query_cmdlist
 * Description  : Get the commands available on this soul and their
 *                corresponding function names.
 * Returns      : mapping - a mapping that maps command names to
 *                function names
 */
public mapping
query_cmdlist()
{
    return ([
                  "tally"   : "tally",
                  "hchelp"  : "hchelp"
         ]) + help_cmdlist();
}


/*
  Carnak's awesome tally code:
*/

/* 
 * Function name:       tally
 * Description  :       Looks up the option and returns it
 * Arguments    :       option - name of option to check
 *                      player - name of the player query
 * Returns      :       the value of the option or 0
 * Modifications : 		Thanks to Carnak for writing the tally code!
 *                      Thanks to Gorboth for developing the race elf : elves check
 */

public int
tally(string race)
{
    mapping tally_list;
    int     tally;
    string  message = "";

	tally = HUNTCLUB_MANAGER_FILE->query_hunter_kills(this_player(), race);

	if (tally == 1) {
		write("You count " + tally + " " + race +
			" on your tallystick.\n");
		return 1;
	} else if (tally > 1) {
		if (strlen(race))
		{
		
			switch (race)
			{
/* blank race template. replace XXX with race name and XXXp wtih plural 
				case "XXX":
					  write("You count " + tally + " "
					  + ((race == "XXX") ? "XXXp" : (race))
					  + " on your tallystick.\n");
					return 1;
*/

/*elves */
				case "drow":
					  write("You count " + tally + " "
					  + ((race == "drow") ? "drow" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "elf":
					  write("You count " + tally + " "
					  + ((race == "elf") ? "elves" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "half-elf":
					  write("You count " + tally + " "
					  + ((race == "half-elf") ? "half-elves" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "shadow-elf":
					  write("You count " + tally + " "
					  + ((race == "shadow-elf") ? "shadow-elves" : (race))
					  + " on your tallystick.\n");
					return 1;
/*end elves */

				case "dwarf":
					  write("You count " + tally + " "
					  + ((race == "dwarf") ? "dwarves" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "fox":
					  write("You count " + tally + " "
					  + ((race == "fox") ? "foxes" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "hill dwarf":
					  write("You count " + tally + " "
					  + ((race == "hill dwarf") ? "hill dwarves" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "gully dwarf":
					  write("You count " + tally + " "
					  + ((race == "gully dwarf") ? "gully dwarves" : (race))
					  + " on your tallystick.\n");
					return 1;

				case "lizardman":
					  write("You count " + tally + " "
					  + ((race == "lizardman") ? "lizardmen" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "mouse":
					  write("You count " + tally + " "
					  + ((race == "mouse") ? "mice" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "rat-man":
					  write("You count " + tally + " "
					  + ((race == "rat-man") ? "rat-men" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "sentry":
					  write("You count " + tally + " "
					  + ((race == "sentry") ? "sentries" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "uruk-hai":
					  write("You count " + tally + " "
					  + ((race == "uruk-hai") ? "uruk-hai" : (race))
					  + " on your tallystick.\n");
					return 1;
				case "wolf":
					  write("You count " + tally + " "
					  + ((race == "wolf") ? "wolves" : (race))
					  + " on your tallystick.\n");
					return 1;





				default:
					write("You count " + tally + " " + race +
						 "s on your tallystick.\n");
					return 1;
					break;
			}
		}
    } else if (tally < 0) {
    	 notify_fail("You have hunted nothing matching the category "
         	+ race + ".\n");
         return 0;
    }
    
    tally_list = HUNTCLUB_MANAGER_FILE->query_option("kills",
                   this_player()->query_real_name());
    tally = HUNTCLUB_MANAGER_FILE->query_hunter_kills(this_player());
    
    write("You tally up the complex method of scratches on your tally"
      + " stick and determine the following:\n\n");
        message +="\t+---------------------+\n";
    foreach(string category, int value: tally_list)
    {
        message += sprintf("\t| %-11s | %5d |", CAP(category), value) + "\n";
    }
    this_player()->catch_msg(message + sprintf(
        "\t| Total: %-4s   %5d |", " ", tally) + "\n" +
        "\t+---------------------+\n");
    return 1;
}

int
hchelp()
{
   write("The possible commands for The Hunter's/Huntress' Club are:\n"+
   "==========================================================\n"+
   "   tally :  Tally your kills by typing, 'tally', or by race, 'tally <race>'.\n" +
   "   hchelp:  This help command.\n");
 
    return 1;
}

