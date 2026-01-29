
 /* Firewalkers soul                 */
 /* August 28th, 1997                */
 /* Jaacar                           */
 /* Modified by Bishop, August 1999. */

#pragma strict_types
#pragma save_binary

inherit "/cmd/std/command_driver";
inherit "/d/Calia/guilds/colleges/specials/general_emote_module";

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

#define SOULDESC(x) (TP->add_prop(LIVE_S_SOULEXTRA, x))


string
get_soul_id()
{
    seteuid(getuid());
    return "College of Fire Magic";
}

int
query_cmd_soul()
{
    seteuid(getuid());
    return 1;
}


int
cmd_list()
{
    write("You can use the following emotes:\n" +
    "fberate <how> <player(s)> - berate someone for their <how> behaviour.\n" +
    "fcontrol                  - attempt to gain control over your anger.\n" +
    "fflare                    - your eyes flare up in anger.\n" +
    "fhypo [what]              - hypothesize something.\n" +
    "fnarrow [player(s)]       - display animosity towards someone.\n" +
    "fsmile <how> <player(s)>  - smile <how> at someone.\n" +
    "cadmonish [player(s)}     - admonish someone to be wary.\n" +
    "camused                   - express amusement with what's happening.\n" +
    "ccongrat [player(s)]      - congratulate someone.\n" +
    "cconsider                 - consider the issue at hand.\n" +
    "cdismiss <player>         - dismiss an idea/a player's idea. \n" +
    "cdistract                 - appear distracted. \n" +
    "chush <how> [player(s)]   - bid someone to hush.\n" +
    "cinterest <how> <player>  - express interest in an idea.\n" +
    "cjourney [player]         - wish someone an interesting journey.\n" +
    "cperplex                  - you are perplexed by this problem.\n" +
    "cscrutin <how> [object]   - scrutinize an object or player <how>.\n" +
    "csigh [player(s)]         - express frustration over someone.\n" +
    "cunimp [player(s)]        - you're unimpressed by someone's arguments.\n"+
    "cweigh <how>              - weigh the alternatives.\n" +
    "\n" +
    "\n" +
    "You can also use the following commands:\n"+
    "cmembers                  - get a list of members in the Realms.\n"+
    "spells                    - get a list of your current spells.\n"+
    "ctoggle [on/off]          - toggles simple title on or off.\n" +
    "\n" +
    "<> denotes an optional argument, [] an obligatory one.\n");
    return 1;
}


int
fnarrow(string str)
{
    object *oblist;

    oblist = parse_this(str, "%l");

    if (!sizeof(oblist))
    {
        NF("Narrow your eyes at who?\n");
        return 0;
    }

    actor("Your eyes narrow at",oblist," in a restrained but smoldering" +
        " display of animosity.");
    all2act(" narrows " + TP->query_possessive() + " eyes at",oblist,
        " in a restrained but smoldering display of animosity.");
    target(" narrows " + TP->query_possessive() + " eyes at you, in a" +
        " restrained but smoldering display of animosity.", oblist);   
    return 1; 
}


int
fcontrol(string str)
{
    write("You close your eyes and try to calm yourself with a meditation" +
        " technique, in an effort not to lose control and destroy everyone" +
        " and everything around you. As you open your eyes again, your" +
        " burning anger is no longer threatening to overwhelm you.\n");
    all(" closes " + TP->query_possessive() + " eyes and clenches " +
        TP->query_possessive() + " fists. "+ capitalize(TP->query_possessive())
        + " eyes snap open, the pupils flashing red for a moment before" +
        " fading back to normal, the anger apparently under control.");
    return 1;
}

int
fflare(string str)
{
    int i;
    object *oblist;

    oblist = FILTER_LIVE(all_inventory(environment(TP)));
    i = 0;
 
    oblist -= ({TP});

    while(i < sizeof(oblist))
    {
        if (!CAN_SEE(TP, oblist[i]) || !CAN_SEE_IN_ROOM(TP))
        {
            oblist -= ({oblist[i]});
        }
        else
        {
            i++;
        }
    }

    if (!sizeof(oblist))
    {
        NF("Your eyes flare up as you struggle to control your anger.\n");
        return 0;
    }
    else
    {
        actor("Your eyes flare up with barely controlled anger, making",
            oblist," take an involuntary step backwards.");
        all("'s eyes flare up with barely controlled anger. You take an" +
            " involuntary step backwards.");
        return 1;
    }
}


int
fsmile(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "broadly", 0);

    if (!stringp(how[0]))
    {
        write("You smile"+how[1]+", confident in your abilities.\n");
        all(" smiles"+how[1]+", confidence and a trace of challenge" +
            " apparent in " + TP->query_possessive() + " expression."
            ,how[1]);
        SOULDESC("smiling"+how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Smile [how] at whom?\n");
        return 0;
    }

    actor("You smile"+how[1]+" at", oblist, ", confident in your abilities.");
    all2act(" smiles"+how[1]+" at",oblist,", confidence and a trace of" +
        " challenge apparent in " + TP->query_possessive() + " expression."
        ,how[1]);
    target(" smiles"+how[1]+" at you, confidence and a trace of challenge" +
        " apparent in " + TP->query_possessive() + " expression."
        ,oblist,how[1]);
    SOULDESC("smiling"+how[1]);
    return 1;
}

int
fberate(string str)
{ 
    int i;
    string *how;
    object *oblist;

    how = parse_adverb_with_space(str, "foolishly", 0);

    if (!stringp(how[0]))
    {
        oblist = FILTER_LIVE(all_inventory(environment(TP)));
        i = 0;
 
        oblist -= ({TP});

        while(i < sizeof(oblist))
        {
            if (!CAN_SEE(TP, oblist[i]) || !CAN_SEE_IN_ROOM(TP))
            {
                oblist -= ({oblist[i]});
            }
            else
            {
                i++;
            }
        }

        if (!sizeof(oblist))
        {
            NF("You can't see anyone to vent your anger on.\n");
            return 0;
        }
        else
        {
            actor("You cannot contain your temper any longer and berate"
                ,oblist," for acting so" + how[1] + ".");
            all2act("cannot contain " + TP->query_possessive() + " temper" +
                " any longer and berates",oblist," for acting so" +
                how[1] + ".", how[1]);
            target(" cannot contain " + TP->query_possessive() + " temper" +
                " any longer and berates you for acting so" + how[1] + ".",
                oblist);
            return 1;
        }
    }

    oblist = parse_this(how[0],"%l");

    if (!sizeof(oblist))
    {
        NF("Who do you wish to berate?\n");
        return 0;
    }

    actor("You cannot contain your temper any longer and berate"
        ,oblist," for acting so" + how[1] + ".");
    all2act("cannot contain " + TP->query_possessive() + " temper" +
        " temper any longer and berates",oblist," for acting so" +
        how[1] + ".", how[1]);
    target(" cannot contain " + TP->query_possessive() + " temper" +
        " any longer and berates you for acting so" + how[1] + ".",
        oblist);
    return 1;

}

int
fhypo(string str)
{

    if (!str || str == "")
    {
       NF("Hypothesize what?\n");
       return 0;
    }
    
    SOULDESC("looking inspired");
    
    write("Your eyes flare with a sudden burst of inspiration as" +
        " you hypothesize that " + str + ".\n");
    all("'s eyes flare with a sudden burst of inspiration as " +
        TP->query_pronoun() + " hypothesizes that " + str + ".");
    return 1;
}

int
f_help(string str)
{
    if (!str)
        return 0;

    if (str == "fire college" || str == "fire")
    {
        write("You may get help on the following:\n\n"+
            "    help fire commands - a list of commands you can use.\n"+
            "    help fire          - this list.\n"+
            "For any other information, study in the guild library.\n");
        return 1;
    }
 
    if (str == "fire commands")
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
    "fflare" : "fflare",
    "fsmile" : "fsmile",
    "fcontrol" : "fcontrol",
    "fnarrow" : "fnarrow",
    "fberate" : "fberate",
    "fhypo" : "fhypo",
    "help" : "f_help",
    "cmembers" : "list_members",
    "ctoggle" : "toggle_simple_title",
    "ccongrat" : "wcongrat",
    "cconsider" : "wconsider",
    "csigh" : "wsigh",
    "cunimp" : "wunimp",
    "cdistract" : "wdistract",
    "camused" : "wamused",
    "cperplex" : "wperplex",
    "cjourney" : "wjourney",
    "cadmonish" : "wadmonish",
    "cdismiss" : "wdismiss",
    "chush" : "whush",
    "cscrutin" : "wscrutin",
    "cweigh" : "wweigh",
    "cinterest" : "winterest",
    ]);
}

