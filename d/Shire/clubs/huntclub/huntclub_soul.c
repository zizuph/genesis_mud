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
#include <language.h>

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
 * Function name:       tally
 * Description  :       Counts how many kills then returns count by race.
 * Arguments    :       tally - total kills by race
 *                      race - race/species object from killed
 * Returns      :       the value of the option or 0
 *
 * Modifications : 		Thanks to Carnak for writing the tally code!
 *                      Thanks to Gorboth for developing the race elf : elves check
 */

string
check_plural(string plural_name)
{
    
    return plural_name;   
}
    
public int
tally(string race)
{
    mapping tally_list;
    int     tally;
    string  message = "";
    string  line = "\t+--------------------------------+\n";
    string  plural_race = "";
    string  pad_chars = "............................................";
    string  race_text = "";
    int     len;
    
    if (strlen(race))
    {
        tally = HUNTCLUB_MANAGER_FILE->query_hunter_kills(this_player(), race);
        
        switch (tally)
        {
            case 0:
                notify_fail("You have hunted nothing matching the category "
                  + race + ".\n");
                return 0;
                break;
            case 1:
                write("You count " + tally + " " + race +
                  " on your tallystick.\n");
                return 1;
            default:
                write("You count " + tally + " " + LANG_PWORD(race)
                  + " on your tallystick.\n");
                return 1;
                break;
        }
    }
    
    string *categories = HUNTCLUB_MANAGER_FILE->query_hunter_categories(this_player()->query_real_name());
    tally = HUNTCLUB_MANAGER_FILE->query_hunter_kills(this_player());
    
   write("You tally up the complex method of scratches on your tally"
      + " stick and determine the following:\n\n");
        message += line;
        message += "\t| Kills                          |\n" + line;

    foreach (string category: categories)
    {
        plural_race = LANG_PWORD(category);
        switch(plural_race)
        {
            case "drows":
                plural_race = "drow";
                break;
        }
        int count = HUNTCLUB_MANAGER_FILE->query_hunter_kills(this_player(), category);
        message += sprintf("\t| %-20s|%9,d |", CAP(plural_race), count) + "\n";
    }
    message += line;
    this_player()->catch_msg(message + sprintf(
        "\t| Total:               %9,d |", tally) + "\n" + line + "\n");
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

