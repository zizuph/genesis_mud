
 /* Test Occ  soul   */
 /* April 7th, 1998  */
 /* Jaacar           */

#pragma strict_types
#pragma save_binary

inherit "/cmd/std/command_driver";

#include <stdproperties.h>
#include <macros.h>
#include <adverbs.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <filter_funs.h>
#include "defs.h"

#define MY TP->query_possessive()
#define HIM TP->query_objective()
#define HE TP->query_pronoun()
#define SOULDESC(x) (TP->add_prop(LIVE_S_SOULEXTRA, x))

string
get_soul_id()
{
    seteuid(getuid());
    return "Testsoul ID";
}

int
query_cmd_soul()
{
    seteuid(getuid());
    return 1;
}

int
is_member(object living)
{
    return 1;
}

int
cmd_list()
{
    write("You can use the following emotes:\n" +
    "fspit (<player(s)>)           - spit fire (at <player(s)>).\n" +
    "help members emotes           - this list.\n"+
    "\n"+
    "You can also use the following commands:\n"+
    "members                       - get a list of Members in the Realms.\n"+
    "\n");
    return 1;
}

int
fspit(string str)
{
    object *who;

    SOULDESC("spitting fire on the ground");

    if (!str || str == "")
    {
       write("You spit fire on the ground in disgust.\n");
       all(" spits fire on the ground in disgust.\nIt extinguishes "+
          "itself quickly.");
       return 1;
    }

    who = parse_this(str, "[at] %l");

    if (!sizeof(who))
    {
        NF("Spit fire at whom?\n");
        return 0;
    }

    actor("You spit fire at",who);
    all2act(" spits fire at",who);
    target(" spits fire at you.  You quickly dodge it and it extinguishes "+
       "itself on the ground beside you.",who);
    return 1;
}

int
list_members()
{
    string g_name, g_short;
    int i;
    int cnt = 0;
    object *list;

    write("The following Members are in the Realms:\n");
    list = users();
    for (i=0; i < sizeof(list); i++)
    {
       if (!is_member(list[i]))
          continue;

       g_name = capitalize(list[i]->query_real_name());
       g_short = list[i]->query_title();
       write("- " + g_name + " " + g_short + "\n");
       cnt++;
    }
   
    if (cnt < 2)
    {
        write("There is only one Member in the Realms.\n");
        return 1;
    }
    write("There are now "+cnt+" Members in the Realms.\n");
    return 1;
}

int
m_help(string str)
{
    if (!str)
        return 0;

    if (str == "member emotes")
    {
        cmd_list();
        return 1;
    }
    return 0;
}

mapping
query_cmdlist()
{
    return ([
    "fspit"     : "fspit",
    "members"   : "list_members",
    "help"      : "m_help",
    ]);
}

