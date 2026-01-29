#pragma strict_types
inherit "cmd/std/command_driver";
#include "/d/Kalad/defs.h"
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <living_desc.h>
#include <ss_types.h>
#include <adverbs.h>
#define tpos this_player()->query_possessive()
#define tpro this_player()->query_pronoun()
#define tpob this_player()->query_objective()
 
string
get_soul_id()
{
   return "Drow School";
}

mapping
query_cmdlist()
{
   return([
#include "dcommands.h"
           ]);
}

int
query_cmd_soul()
{
 return 1;
}

public int
e_dwince(string arg)
{
    notify_fail("What?\n");
    if (strlen(arg))
        return 0;

    allbb(" winces in obvious pain, as the sun falls on " + 
        this_player()->query_possessive() + " face.");
    write("You wince in pain as the light of the sun passes over your " +
        "face.\n");
    return 1;
}

public int
e_dlook(string arg)
{
    object *oblist;

    notify_fail("Look what?\n");

    if (!strlen(arg))
    {
        allbb(" looks around the room carefully, as if looking for " +
        "something.");
        write("You look around the room, distrusting every aspect of " +
        "it.\n");
        return 1;
    }

    oblist = parse_this(arg, "[the] %l");
    if (!sizeof(oblist))
        return 0;

    actor("You look at", oblist, " suspiciously, not sure of " + 
        this_player()->query_possessive() + " true intentions.");
    all2actbb(" looks at", oblist, " suspiciously.");
    targetbb(" looks at you with a glimmer of distrust in " + 
        this_player()->query_possessive() + " eye.", oblist);
    return 1;
}
