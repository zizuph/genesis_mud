#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "guild.h"

inherit "/cmd/std/command_driver";
inherit (GUILD_DIR + "commands");

#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include "emotes.h"

/********************************************************************
 * Soul identifying and autoloading
 ********************************************************************/
public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "khalclans"; }

/********************************************************************
 * The list of verbs and functions.
 *******************************************************************/
public mapping
query_cmdlist()
{
    return ([
      "cl"       : "cl",
      "classist" : "cl_assist",
      "clbrand"  : "cl_brand",
      "clbye"    : "cl_bye",
      "clcross"  : "cl_cross",
      "clcurse"   : "cl_curse",
      "clenjoy"  : "cl_enjoy",
      "cldare"   : "cl_dare",
      "clhelp"   : "cl_help",
      "clgreet"  : "cl_greet",
      "clhand"   : "cl_handshake",
      "clintro"  : "cl_intro",
      "cljig"    : "cl_jig",
      "cllaugh"  : "cl_laugh",
      "clmock"   : "cl_mock",
      "clmutter" : "cl_mutter",
      "clpray"   : "cl_pray",
      "clraise"  : "cl_raise",
      "clrub"    : "cl_rub",
      "clsalute" : "cl_salute",
      "clsay"    : "cl_say",
      "clscan"   : "cl_scan",
      "clscratch" : "cl_scratch",
      "clsearch" : "cl_search",
      "clslap"   : "cl_slap",
      "clsong"   : "cl_song",
      "clthrust" : "cl_thrust",
      "cltight"  : "cl_tight",
      "cltrace"  : "cl_trace",
      "clvictory" : "cl_victory",
      "clwipe"   : "cl_wipe",
      "clwarcry" : "cl_warcry",
      "clyawn"   : "cl_yawn",
    ]);
}

public void
using_soul(object live)
{
    if (!objectp(live))
        return;

    live->add_subloc(GUILD_SUBLOC, this_object());
}

/*  Not sure I want a sub loc yet or not
public string
show_subloc(string subloc, object on, object who)
{
    string str, clan, color;

    if (subloc != GUILD_SUBLOC)
        return "";

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (clan = SERVER->query_clan(on->query_real_name()))
    {
        color =  COMPOSITE_WORDS(CLANS[clan][CLAN_CLRS]);
    }

    if (on != who)
    {
        str = capitalize(on->query_pronoun()) + " face is " +
        "painted with the markings of a member of the " +
        GUILD_NAME + ".\n";

        if (color)
        {
            str += capitalize(on->query_pronoun()) + " wears the " + 
                color + " colours of " + (IS_MEMBER(who) ? 
                    "Clan " + clan : "Clan") + ".\n";
        }
    }
    
    return str;
}

*/


/*****************************************************************
 *  Emotes are in emotes.h                                       *
 *****************************************************************/

/*
 *      clhelp   = Clan of Khalakhor Help command
 */
public int
cl_help(string str)
{
    string filename, subject, text;

    if (!str)
    {
        subject = "index";
    }
    else if (sscanf(str, "%s", subject) != 1)
    {
        notify_fail("There is no help section for that subject.\n");
        return 0;
    }

    filename = HELP + subject;

    if (file_size(filename) > 0)
    {
        setuid();
        seteuid(getuid());
        text = read_file(filename);
        this_player()->more(text);
        return 1;
    }
    notify_fail("There is no help section for that subject.\n");
    return 0;
}

/*
 * Function name: cl
 * Description  : By prefixing "cl" to the command, players can always execute
 *                the Racial Guild command, even if the name conflicts with
 *                that of another guild. Copied verbatum from Mercade's Rockfriend
 *                soul.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
cl(string str)
{
    string *words;

    if (!strlen(str))
    {
        notify_fail("Perform which Clan command? " +
          "Syntax: cl <command> [<arguments>]\n");
        return 0;
    }

    words = explode(str, " ");
    if (!stringp(cmdlist[words[0]]))
    {
        notify_fail("The command " + words[0] +
          " is not a known Clan of Khalakhor command.\n");
        return 0;
    }

    str = ((sizeof(words) > 1) ? implode(words[1..], " ") : "");
    return call_other(this_object(), cmdlist[words[0]], str);
}
