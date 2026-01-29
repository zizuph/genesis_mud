/*
 *
 *  This module contains the code for all the emotes the four Elemental
 *  Colleges have in common, and is inherited in each soul.
 *  Bishop of Calia, August 9th, 99.
 *
 */


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


int
toggle_simple_title(string str)
{
    int skill = TP->query_skill(SS_COLLEGE_BITS);

    if (str == "off")
    {
        if (skill & TITLE_SIMPLE_BIT)
        {
            write("You no longer display the simple title.\n");
            TP->set_skill(SS_COLLEGE_BITS, skill & (~TITLE_SIMPLE_BIT));
            return 1;
        }
        else
        {
            NF("You aren't using the simple title!\n");
            return 0;
        }
    }
    else if (str == "on")
    {
        if (!(skill & TITLE_SIMPLE_BIT))    
        {
            write("You start using the simple title.\n");
            TP->set_skill(SS_COLLEGE_BITS, skill | TITLE_SIMPLE_BIT);
            return 1;
        }
        else
        {
            NF("You're already using the simple title!\n");
            return 0;
        }
    }
    else
    {
        NF("Turn simple title on or off?\n");
        return 0;
    }
}


int
list_members(string str)
{
    string g_name, g_short;
    int i;
    object *list;

    write("The following members are in the Realms:\n");
    list = users();
    for (i=0; i < sizeof(list); i++)
    {
        if (!(list[i]->is_college_member()) || list[i]->query_invis())
            continue;

        g_name = capitalize(list[i]->query_real_name());

        g_short = list[i]->query_college_full_title();
        write("- "+g_name+" the "+g_short+"\n");
    }
    
    return 1;
}

int
wunimp(string str)
{
    object *oblist;

    oblist = parse_this(str, "%l");

    if (!sizeof(oblist))
    {
        NF("Whose arguments are you unimpressed with?\n");
        return 0;
    }

    actor("You are unimpressed by the arguments of",oblist,".");
    all2act(" appears unimpressed by the arguments of",oblist,".");
    target(" appears unimpressed by your arguments.", oblist);
  
    return 1;
}

int
wsigh(string str)
{
    object *oblist;

    oblist = parse_this(str, "%l");

    if (!sizeof(oblist))
    {
        NF("Who do you wish to express frustration with?\n");
        return 0;
    }

    actor("You sigh in frustration over the lack of understanding exhibited" +
        " by",oblist,".");
    all2act(" sighs, obviously frustrated by the lack of understanding" +
        " exhibited by",oblist,".");
    target(" sighs, obviously frustrated by your lack of understanding.", 
        oblist);
    return 1;
}

int
wcongrat(string str)
{
    object *oblist;

    oblist = parse_this(str, "%l");

    if (!sizeof(oblist))
    {
        NF("Congratulate whom?\n");
        return 0;
    }

    if (sizeof(oblist) < 2)
    {
        actor("You congratulate",oblist,", recognizing " + 
            oblist[0]->query_possessive() + " achievements.");
        all2act(" congratulates",oblist,", recognizing " +
            oblist[0]->query_possessive() + " achievements.");
        target(" congratulates you, recognizing your achievements.", oblist);
    }
    else
    {
        actor("You congratulate",oblist,", recognizing their achievements.");
        all2act(" congratulates",oblist,", recognizing their achievements.");
        target(" congratulates you, recognizing your achievements.", oblist);
    }

    return 1;
}

int
wconsider(string str)
{
    write("You consider the issue at hand.\n");
    all(" considers the issue at hand.");
    return 1;
}

int
wdistract(string str)
{
    write("Your mind goes off in an unexpected direction, distracting you" +
        " from the situation at hand.\n");
    all(" looks distracted for a moment, as if thinking about something else" +
        " entirely.");
    return 1;
}

int
wamused(string str)
{
    write("You are amused by this turn of events.\n");
    all(" looks amused by this turn of events.");
    return 1;
}

int
wperplex(string str)
{
    write("You are perplexed by this problem.\n");
    all(" seems perplexed by this problem.");
    return 1;
}

int
wjourney(string str)
{
    object *oblist;

    oblist = parse_this(str, "%l");

    if (!sizeof(oblist))
    {
        NF("Who do you wish to bid farewell to?\n");
        return 0;
    }

    actor("You wish",oblist," an interesting journey.");
    all2act(" wishes",oblist," an interesting journey.");
    target(" wishes you an interesting journey.", oblist);
  
    return 1;
}

int
wadmonish(string str)
{
    object *oblist;

    oblist = parse_this(str, "%l");

    if (!sizeof(oblist))
    {
        NF("Who do wish to admonish to be wary?\n");
        return 0;
    }

    if (sizeof(oblist) < 2)
    {
        actor("You admonish",oblist," to be wary, for powers far beyond " +
            oblist[0]->query_possessive() + " comprehension are at work" +
            " here.");
        all2act(" admonishes",oblist," to be wary, for powers far beyond " +
            oblist[0]->query_possessive() + " comprehension are at work" +
            " here.");
        target(" admonishes you to be wary, for powers far beyond your" +
            " comprehension are at work here.", oblist);
    }
    else
    {
        actor("You admonish",oblist," to be wary, for powers far beyond" +
            " their comprehension are at work here.");
        all2act(" admonishes",oblist," to be wary, for powers far beyond" +
            " their comprehension are at work here.");
        target(" admonishes you to be wary, for powers far beyond your" +
            " comprehension are at work here.", oblist);
    }

    return 1;
}


int
wdismiss(string str)
{
    object *oblist;

    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist) || sizeof(oblist) > 1)
    {
        write("You dismiss the idea with a nonchalant wave of your hand.\n");
        all(" dismisses the idea with a nonchalant wave of " +
            TP->query_possessive() + " hand.");
    }
    else
    {
        actor("You dismiss the idea of",oblist," with a nonchalant wave of" +
            " your hand.");
        all2act(" dismisses the idea of",oblist," with a nonchalant wave of " +
            TP->query_possessive() + " hand.");
        target(" dismisses your idea with a nonchalant wave of " +
            TP->query_possessive() + " hand.", oblist);
    }

    return 1;
}


int
whush(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "discreetly", 0);


    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        NF("Bid whom to hush?\n");
        return 0;
    }
    else
    if (sizeof(oblist) < 2)
    {
        actor("You"+how[1]+" bid", oblist, " hush with a motion of your" +
            " finger to your lips, then caution " + 
            oblist[0]->query_objective() + " not to mention private" +
            " matters in public conversation.");
        all2act(how[1]+" bids",oblist," hush with a motion of " +
            TP->query_possessive() + " finger to " + TP->query_possessive() +
            " his lips, then cautions " + oblist[0]->query_objective() + 
            " not to mention private matters in public conversation.",how[1]);
        target(how[1] + " bids you hush with a motion of " + 
            TP->query_possessive() +
            " finger to " + TP->query_possessive() + " lips, then cautions" +
            " you not to mention private matters in public conversation.", 
            oblist, how[1]);
        return 1;
    }

    actor("You"+how[1]+" bid", oblist, " hush with a motion of your finger" +
        " to your lips, then caution them not to mention private matters" +
        " in public conversation.");
    all2act(how[1]+" bids",oblist," hush with a motion of " +
        TP->query_possessive() + " finger to " + TP->query_possessive() +
        " his lips, then cautions them not to mention private matters in" +
        " public conversation.", how[1]);
    target(" bids you hush with a motion of " + TP->query_possessive() +
        " finger to " + TP->query_possessive() + " lips, then cautions you" +
        " not to mention private matters in public conversation.", oblist,
        how[1]);
    return 1;
}

int
wscrutin(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "thoroughly", 0);

    oblist = parse_this(how[0], "%i");

    if (!sizeof(oblist))
    {
        NF("Scrutinize what?\n");
        return 0;
    }
    if (sizeof(oblist) > 1)
    {
        NF("You can only scrutinize one object at a time.\n");
        return 0;
    }

    actor("You scrutinize", oblist, how[1] + ", looking for any" +
        " detail you may previously have overlooked.");
    all2act(" scrutinizes", oblist, how[1] + ", looking for any detail " +
        TP->query_pronoun() + " may previously have overlooked.", how[1]);
    target(" scrutinizes you" + how[1] + ", looking for any detail " +
        TP->query_pronoun() + " may previously have overlooked.", oblist,
        how[1]);
    return 1;
}

int
wweigh(string str)
{
    string *how;

    how = parse_adverb_with_space(str, "painstakingly", 0);

    write("You" + how[1] + " weigh the alternatives, staring into the" +
        " distance and holding your palms upturned as if balancing the" +
        " problem in your hands.\n");
    all(how[1]+ " weighs the alternatives, staring into the distance" +
        " and holding " + TP->query_possessive() + " palms upturned as if" +
        " literally balancing something.");
    return 1;
}

int
winterest(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "eagerly", 0);

    if (!stringp(how[0]))
    {
        write("You express interest in the idea and" + how[1] + " solicit" +
            " more details.\n");
        all(" expresses interest in the idea and" + how[1] + " solicits" +
            " more details." ,how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "%l");

    if (!sizeof(oblist))
    {
        NF("Express interest in whose idea?\n");
        return 0;
    }

    actor("You express interest in the idea of", oblist, " and" + how[1] +
        " solicit more details.");
    all2act(" expresses interest in the idea of", oblist, " and" + how[1] +
        " solicits more details.", how[1]);
    target(" expresses interest in your idea and " + how[1] + " solicits" +
        " more details.",oblist,how[1]);
    return 1;
}
