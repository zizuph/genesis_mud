/*
 * File: /d/Avenir/cirion/emote_soul.c
 * Created: Cirion, Tue Nov 17 06:26:44 1998
 * Purpose: Command soul
 * Note: This file was auto-created by Cirion's Soulmaker tool
 *     (/d/Avenir/tools/emote_maker)
 */
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
inherit "/cmd/std/command_driver";

/* Commands */
mapping query_cmdlist()
{
    return ([
        "discern" : "discern_emote",

    ]);

}

/* Id and autoload */
string get_soul_id() 
{ 
    return "Generic Emotion Soul";
}

/* It is a real command soul */
int query_cmd_soul() 
{ 
    return 1; 
}

// emotion "discern" added by
// Cirion's Soulmaker on Tue Nov 17 06:26:44 1998
public int
discern_emote(string arg)
{
    object *oblist;
    string *how, adverb;

    how = parse_adverb_with_space(arg, " quietly" , 0);
    adverb = how[1];

    if (!stringp(how[0]))
    {
        write("You discern " + adverb + " the deeper meaning involved here.\n");
        allbb(" seems to " + adverb + " discern some deep meaning", adverb);
        return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Discern [how] [who/what]?\n");
        return 0;
    }

    actor("You discern " + adverb + " the deeper meanings implied by ", oblist, ".");
    target(" seems to be discerning the meaning of what you say.", oblist, adverb);
    all2act("  " + adverb + " discerns the deeper meaning implied by ", oblist, "", adverb);
    return 1;
}
