/*
 * Riders of Last Soul
 * /d/Terel/guilds/riders/rider_soul.c
 *
 * Tomas -- April 2000
 *
 * Modification Log:
 *
 */


inherit "/cmd/std/command_driver";

#pragma save_binary
#include <const.h>
#include <adverbs.h>
#include <language.h>
#include <filter_funs.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "include/guild.h"
#include "include/rider_emotes.h"

/********************************************************************
 * The following include entries are the special abilities
 ********************************************************************/
// #include "include/rlattack.h"

/********************************************************************
 * Soul identifying and autoloading
 ********************************************************************/
public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Rider of Last"; }

/********************************************************************
 * The list of verbs and functions. 
 *******************************************************************/
public mapping
query_cmdlist()
{
    seteuid(getuid());
    return ([
        "rol"       : "rol",
        "rlhelp"    : "rol_help",
        "rlaccept"  : "rol_bow",
        "rlretire"  : "rol_retire",
        "rlwho"     : "rol_who",
        "rlhair"    : "rol_hair",
       
           ]);
}                   



public int
spur_check(object ob)
{
    return (ob->id(RIDER_GUILD_EMBLEM) && ob->query_adj() == "worn");
}        



/*****************************************************************
 *  Club emotes are in ../include/rider_emotes.h                 *
 *****************************************************************/

/*
 *      rlhelp  Rider Guild help file
 */ 
public int
rol_help(string str)
{
    string filename, subject, text;

    if (!str)   
        subject = "list";

    else if (sscanf(str, "%s", subject) != 1)
    {
        notify_fail("There is no help section for that subject.\n");
        return 0;
    }
    filename = RIDER_HELP_DIR + subject;
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
 * Function name: rol
 * Description  : By prefixing "rol" to the command, players can always execute
 *                the Dragon Order  command, even if the name conflicts with
 *                that of another guild. Copied verbatum from Mercade's Rockfriend
 *                soul.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
rol(string str)
{
    string *words;
 
    if (!strlen(str))
    {
        notify_fail("Perform which Riders of Last command? " +
            "Syntax: rol <command> [<arguments>]\n");
        return 0;
    }
 
    words = explode(str, " ");
    if (!stringp(cmdlist[words[0]]))
    {
        notify_fail("The command " + words[0] +
            " is not a known Riders of Last command.\n");
        return 0;
    }
 
    str = ((sizeof(words) > 1) ? implode(words[1..], " ") : "");
    return call_other(this_object(), cmdlist[words[0]], str);
}



