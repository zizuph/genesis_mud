#include "../guild.h"

inherit "/cmd/std/command_driver";
inherit "/d/Emerald/lib/help";

#include "soul.h"

#include <macros.h>

#include "asay.c"
#include "convey.c"
#include "idea.c"
#include "promotions.c"
#include "seek.c"

string
get_soul_id()
{
   return "KoT";
}

int
query_cmd_soul()
{
    return 1;
}

mapping
query_other_cmds()
{
    return ([]);
}

mapping
query_cmdlist()
{
    mapping other_cmds;

    other_cmds = this_object()->query_other_cmds();

    return ([
             "ktadmire"       : "admire",
             "ktapprove"      : "approve",
             "ktasay"         : "asay",
             "ktbid"          : "bid",
             "ktcompliment"   : "compliment",
             "ktcondemn"      : "condemn",
             "ktdisgust"      : "disgust",
             "ktdrum"         : "drum",
             "ktglow"         : "glow",
             "ktgreet"        : "greet",
             "help"           : "help",
             "ktidea"         : "_idea",
             "ktlisten"       : "listen",
             "ktpromotions"   : "promotions",
             "ktrevoke"       : "revoke",
             "ktrejoice"      : "rejoice",
             "ktseek"         : "seek",
           ]) + other_cmds + help_cmdlist();
}

void create_caste_soul()
{
}

nomask void
create()
{
    set_help_type(({ "keepers", "kot" }));
    read_help_dir(KOT_HELP_DIR);

    create_caste_soul();
}

int
admire(string str)
{
    object *oblist;
    
    if (!strlen(str) || !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail("Adore whom?\n");
        return 0;
    }

    targetbb(" looks at you, admiration apparent in " + POSTP +
        " eyes.", oblist);
    actor("You look at", oblist, ", admiration apparent in your eyes.");
    all2actbb(" looks at", oblist, ", admiration apparent in " + POSTP +
        " eyes.");
    return 1;
}

int
approve(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You nod approval at the idea.\n");
        all(" nods approval at the idea.");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[of] / [at] [the] %l")))
    {
        notify_fail(capitalize(query_verb()) + " whom?\n");
        return 0;
    }

    targetbb(" nods approval at your idea.", oblist);
    actor("You nod approval at", oblist, "'s idea.");
    all2actbb(" nods approval at", oblist, "'s idea.");
    return 1;
}

int
bid(string str)
{
    object *oblist;

    if (!strlen(str) || !sizeof(oblist = parse_this(str, "[to] %l")))
    {
        notify_fail("Bid farewell to whom?\n");
        return 0;
    }

    target(" bids you a fond farewell, wishing that you always walk in "+
           "the light.", oblist);
    actor("You bid a fond farewell to", oblist);
    all2actbb(" bids a fond farewell to", oblist);

    return 1;
}

int
compliment(string str)
{
    object *oblist;

    if (!strlen(str) || !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail("Whom do you wish to compliment?\n");
        return 0;
    }

    target(" compliments you on the way that you conduct yourself.", oblist);
    actor("You compliment", oblist, " on the way that " + PRO(oblist[0]) +
          " conducts " + OBJ(oblist[0]) + "self.");
    all2act(" compliments", oblist, " on the way that " + PRO(oblist[0]) +
            " conducts " + OBJ(oblist[0]) + "self.");
    return 1;
}

int
condemn(string str)
{
    object *oblist;

    if (!strlen(str) || !sizeof(oblist = parse_this(str,"[the] %l")))
    {
        notify_fail("Whom do you wish to condemn?\n");
        return 0;
    }

    target(" condemns you and your blaspheming of the Light.", oblist);
    actor("You condemn", oblist, " and " + HIS_OR_THEIR(oblist) +
        " blaspheming of the Light.");
    all2act(" condemns", oblist, " and " + HIS_OR_THEIR(oblist) +
        " blaspheming of the Light.");
    return 1;
}

int
disgust(string str)
{
    object *oblist;

    if (!strlen(str) || !sizeof(oblist = parse_this(str, "[at] %l")))
    {
        notify_fail("Turn your back on whom?\n");
        return 0;
    }

    targetbb(" turns " + POSTP + " back on you in disgust.", oblist);
    actor("You turn your back on", oblist);
    all2act(" turns " + POSTP + " back on", oblist, " in disgust.");
    return 1;
}

int
drum(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You drum your fingers impatiently.\n");
    all(" drums " + POSTP + " fingers impatiently.");
    return 1;
}

int
greet(string str)
{
    object *oblist;

    if (!strlen(str) || !sizeof(oblist = parse_this(str, "%l")))
    {
        notify_fail(capitalize(query_verb()) + " whom?\n");
        return 0;
    }
    
    target(" greets you in ancient elven: 'Ultular Enari!'", oblist);
    actor("You greet", oblist, " in ancient elven: 'Ultular Enari!'");
    all2act(" greets", oblist," in ancient elven: 'Ultular Enari!'");
    return 1;
}

int
glow(string str)
{
    object *oblist;

    if (!strlen(str) || !sizeof(oblist = parse_this(str,"[at] [the] %l")))
    {
        notify_fail(capitalize(query_verb()) + " at whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only glow at one person at a time.\n");
        return 1;
    }

    if (oblist[0]->query_race_name() == "elf")
    {
        actor("You turn and look at", oblist, " but nothing "+
            "interesting happens.");
        target(" turns and looks at you, but nothing interesting "+
            "happens.", oblist);
        all2actbb(" turns and looks at", oblist, " but nothing "+
            "interesting happens.");
        return 1;
    }

    actor("You turn and give", oblist, " a long and forceful "+
        "look. " + capitalize(PRO(oblist[0])) + " looks " +
        "suddenly shaken.");
    targetbb(" turns to you, giving you a long stare, you suddenly "+
        "feel very strange as you become aware of what looks "+
        "like glowing red embers behind " + POSTP + " eyes.", oblist);
    all2actbb(" turns to", oblist, " and gives " + OBJ(oblist[0]) +
        "a long stare. " + QCTNAME(oblist[0]) + " looks suddenly shaken.");
    return 1;
}

int
rejoice(string str)
{
    object *oblist;
    
    if (!strlen(str) || !sizeof(oblist = parse_this(str, "[at] %l")))
    {
        notify_fail(capitalize(query_verb()) + " whom?\n");
        return 0;
    }

    target(" rejoices that you are safe and well.", oblist);
    actor("You rejoice that", oblist, " is safe and well.");
    all2act(" rejoices that", oblist, " is safe and well.");
    return 1;
}

int
listen(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You stop and quickly listen to the nearby area for sounds "+
          "of danger.\n");
    allbb(" falls silent for a moment. It seems that "+OBJTP+
        " is listening intently to the surrounding area.");
    return 1;
}
