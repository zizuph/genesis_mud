/*
 * More emotes for Wild Elves
 */

#include "/d/Shire/cypress/sys/defs.h"
#include "/d/Shire/cypress/guilds/wrunner/wrunner_defs.h"
#include <adverbs.h>
#include <cmdparse.h>

inherit "/cmd/std/command_driver";

int agree(string str)
{
        object *oblist;
        if(!strlen(str))
        {
                write("You stroke your chin thoughtfully, and come to " +
                    "the conclusion you agree with the idea.\n");
                all(" strokes " + HIS_HER(TP) + " chin thoughtfully, then " +
                "decides " + HE_SHE(TP) + " agrees with the idea.");
                return 1;
        }
        oblist = parse_this(str, "%l");
        if(!sizeof(oblist))
                return 0;
        actor("You stroke your chin, lost in thought. After deep " +
            "contemplation, you come to the conclusion you agree " +
            "with",oblist,"'s idea.");
        target(" strokes " + HIS_HER(TP) + " chin, seemingly lost in thought. " +
            "After deep contemplation, " + HE_SHE(TP) + " comes to the " +
            "conclusion " + HE_SHE(TP) + " agrees with your idea.", oblist);
        all2actbb(" strokes " + HIS_HER(TP) + " chin, seemingly lost in " +
            "thought. After deep contemplation, " + HE_SHE(TP) + 
            " comes to the conclusion " + HE_SHE(TP) + " agrees " +
            "with", oblist,"'s idea.");
        return 1;
}

int apologize(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "stiffly", 0);

    if (!stringp(how[0]))
    {
        write("You clench your jaw and" + how[1] + " offer a hollow apology.\n");
        allbb(" clenches " + HIS_HER(TP) + " jaw and" + how[1] + 
            " offers a hollow apology.", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] [to] %i");

    if (!sizeof(oblist))
    {
        notify_fail("weapologize [how] to whom?\n");
        return 0;
    }

    actor("You clench your jaw and" + how[1] + " offer a hollow " +
        "apology to", oblist,".");
    targetbb(" clenches " + HIS_HER(TP) + " jaw and" + how[1] + 
        " offers a hollow apology to you.", oblist);
    all2actbb(" clenches " + HIS_HER(TP) + " jaw and" + how[1] +
        " offers a hollow apology to", oblist, ".");
    return 1;
}

int avert(string str)
{
        write("You avert your eyes from the unpleasant scene before you.\n");
        all(" averts " + HIS_HER(TP) + " eyes from the unpleasant scene before " + 
            HIM_HER(TP) + " .");
        return 1;
}

int bite(string str)
{
        write("You bite your tongue, holding back a scathing remark.\n");
        all(" bites "+HIS_HER(TP)+" tongue and holds back a scathing remark.");
        return 1;
}

int blink(string str)
{
        write("You slowly blink your eyes, unable to believe what you saw.\n");
        all(" slowly blinks "+HIS_HER(TP)+" eyes, unable to believe " +
            "what " + HE_SHE(TP) + " saw.");
        return 1;
}

int blanch(string str)
{
        write("You swallow slowly as the color slowly drains from your " +
            "face.\n");
        all(" swallows slowly as the color slowly drains from "+HIS_HER(TP)+
            " face.");
        return 1;
}

int blow(string str)
{
        write("You take a deep breath, and blow it slowly from your lips.\n");
        all(" takes a deep breath, and slowly blows it from " + HIS_HER(TP) + 
            " lips.");
        return 1;
}

int caress(string str)
{
        write("You absentmindedly caress your tiny, golden ring.\n");
        all(" absentmindedly caresses "+HIS_HER(TP)+" tiny, golden ring.");
        return 1;
}


int choke(string str)
{
        write("You choke back a cutting remark.\n");
        all(" chokes "+HIS_HER(TP)+" back a cutting remark.");
        return 1;
}

int think(string str)
{
        write("You think quickly, your mind bouncing from one idea to another.\n");
        all(" thinks quickly, with thoughts dancing across " + HIS_HER(TP) + 
            " face.");
        return 1;
}
