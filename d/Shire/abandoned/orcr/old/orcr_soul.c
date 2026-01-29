/* This file is /d/Shire/guilds/orcr_soul.c 
 *
 * Modified from the Adventuresome Hobbits soul.
 * Special thanks for Elessar of Gondor for allowing us to 
 * reuse his code.
 * /Finwe October 2000
 */

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
#include <macros.h>
#include <formulas.h>
#include "orcr.h"
#include <stdproperties.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"
//#include "hsing.h"
#include "olist.h"

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
//#define S_RIDDLE_ANSWER "s_riddle_answer"
//#define PIPE  "_hobbit_race_guild_pipe_"
//#define IS_SMOKING  query_pipe_is_smoking()
//#define FLAVOUR     query_pipe_flavour()
#define MORE(x)   this_player()->more(read_file(x,2))

int alarm_id;

string
get_soul_id()
{
    return "Orcs of Middle-earth";
}

int
query_cmd_soul()
{
    return 1;
}

mapping
query_cmdlist()
{

    setuid();
    seteuid(getuid());

    return ([
/*
      "help"       :   "do_help",
      "hbow"       :   "hbow",
      "hflip"      :   "e_hflip",
      "hchew"      :   "hchew",
      "hcheer"     :   "hcheer",
      "hcringe"    :   "hcringe",
      "hdance"     :   "hdance",
      "hdemand"    :   "hdemand",
      "hempty"     :   "hempty",
      "hfidget"    :   "hfidget",
      "hglint"     :   "hglint",
      "hhanky"     :   "hhanky",
      "hinform"    :   "hinform",
      "hinquire"   :   "hinquire",
      "hjump"      :   "hjump",
      "hkick"      :   "hkick",
      "hlaugh"     :   "hlaugh",
      "hlist"      :   "list_active_hobbits",
      "hlook"      :   "hlook",
      "hmourn"     :   "hmourn",
      "hnap"       :   "hnap",
      "hobbitlist" :   "list_active_hobbits",
      "hpick"      :   "hpick",
      "hpuff"      :   "hpuff",
      "hregard"    :   "hregard",
      "hriddle"    :   "hriddle",
      "hrumble"    :   "hrumble",
      "hshout"     :   "hshout",
      "hskip"      :   "hskip",
      "hsing"      :   "hsing",
      "hsmile"     :   "hsmile",
      "hspin"      :   "hspin",
      "hstretch"   :   "hstretch",
      "hthink"     :   "hthink",
      "htummy"     :   "htummy",
      "htwirl"     :   "htwirl",
      "hsit"       :   "hsit",
      "hbelt"      :   "hbelt",
      "hsift"      :   "hsift",
      "hrock"      :   "hrock",
      "hhug"       :   "hhug",
      "hrage"      :   "hrage",
      "hstance"    :   "hstance",
      "hpride"     :   "hpride"
*/
    ]);

    /* The above are in the form: command : function */

}

int
do_help(string str)
{
    setuid(); seteuid(getuid());
    if(str == "orcs of middle-earth")
    {
	MORE(ORCR_HELP+"general");
	write("Report any problems you may encounter "+
	  "with the orcs to "+
	  COMPOSITE_WORDS(map(ORCR_RACE_GUILD_MASTER, capitalize)) + ".\n");
	return 1;
    }

    if(str == "orc emotions")
    {
	MORE(ORCR_HELP+"emotes");
	return 1;
    }

    if(str == "orc tribe")
    {
	MORE(ORCR_HELP+"tribe");
	return 1;
    }
    if (str == "orc news")
    {
	MORE(ORCR_NEWS);
	return 1;
    }
    return 0;
}
