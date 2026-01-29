
inherit "/cmd/std/command_driver";
inherit "/cmd/std/soul_cmd";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <std.h>
#include <filter_funs.h>
#include <const.h>

#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA,x))
#define MY this_player()->query_possessive()

get_soul_id()
{
    return "Quandam Mistici Society";
}

int
is_mclub_member()
{
    return 1;
}

int
query_cmd_soul()
{
    return 1;
}

gaze(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You gaze off towards the east in thoughtful silence.\n");
    all(" gazes off towards the east in thoughtful silence.");
    SOULDESC("gazing east in thoughtful silence");
    return 1;
}

rend(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You rend your garments due to the heinous blasphemy.\n");
    all(" rends "+MY+" garments due to the heinous blasphemy.");
    return 1;
}

sign(string str)
{
    object tp, who;
    tp = this_player();
    if (!str || str == "")
    {
        write("You trace a mysterious sign in front of yourself.\n");
        all(" traces a mysterious sign before "+this_player()->query_objective()+
            "self.");
        return 1;
    }
    who = parse_this(str,"%l");
    if (!sizeof(who)) return 0;
    target(" traces a mysterious sign before you.",who);
    actor("You trace a mysterious sign before",who);
    all2actbb(" traces a mysterious sign before",who);
    return 1;
}

scold(string str)
{
    object *oblist;
    if (!strlen(str))
    {
        notify_fail("Scold who?\n");
        return 0;
    }
    oblist = parse_this(str,"%l");
    if(!sizeof(oblist))
    {
        return 0;
    }
    target(" scolds you for being such a scrouge.",oblist);
    actor("You scold",oblist," for being such a scrouge.");
    all2actbb(" scolds",oblist," for being such a scrouge.");
    return 1;
}

scorn(string str)
{
    object *oblist;
    if (!strlen(str))
    {
        notify_fail("Scorn who?\n");
        return 0;
    }
    oblist = parse_this(str,"%l");
    if(!sizeof(oblist))
    {
        return 0;
    }
    target(" scorns you with great contempt.",oblist);
    actor("You scorn",oblist," with great contempt.");
    all2actbb(" scorns",oblist," with great contempt.");
    return 1;
}

curse(string str)
{
    object tp, who;
    tp = this_player();
    if (!str || str == "")
    {
        write("You intone an ancient curse.\n");
        all(" intones an ancient curse.");
        SOULDESC("intoning an ancient curse");
        return 1;
    }
    who = parse_this(str,"%l");
    if (!sizeof(who)) return 0;
    target(" intones an ancient curse upon you.",who);
    actor("You intone an ancient curse upon",who);
    all2actbb(" intones an ancient curse upon",who);
    return 1;
}

pray(string str)
{
    object tp, who;
    tp = this_player();
    if (!str || str == "")
    {
        write("You kneel down and pray.\n");
        all(" kneels down and prays.");
        SOULDESC("kneeling on the ground praying");
        return 1;
    }
    who = parse_this(str,"%l");
    if (!sizeof(who)) return 0;
    target(" prays for you.",who);
    actor("You pray for",who);
    all2actbb(" prays for",who);
    return 1;
}

reverence(string str)
{
    object *oblist;
    if(!strlen(str))
    {
        notify_fail("Show reverence for who?\n");
        return 0;
    }
    oblist = parse_this(str, "%l");
    if(!sizeof(oblist))
    {
        return 0;
    }
    target(" shows "+MY+" reverence for you.",oblist);
    actor("You show reverence for",oblist,".");
    all2actbb(" shows "+MY+" reverence for",oblist,".");
    return 1;
}

farewell(string str)
{
    object *oblist;
    if(!strlen(str))
    {
        notify_fail("Bid farewell to who?\n");
        return 0;
    }
    oblist = parse_this(str,"%l");
    if(!sizeof(oblist))
    {
        return 0;
    }
    target(" bids you farewell.",oblist);
    actor("You bid",oblist," farewell.");
    all2actbb(" bids",oblist," farewell.");
    return 1;
}

meyes(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You show the eyes of mystery.\n");
    all(" grows dark and "+MY+" eyes seem to glow with a "+
        "luminescent fire.");
    return 1;
}

msmile(string str)
{
    object tp, who;
    tp = this_player();
    if (!str || str == "")
    {
        write("You smile mysteriously.\n");
        all(" smiles mysteriously, which seems to summon an eerie presence.");
        return 1;
    }
    who = parse_this(str,"%l");
    if (!sizeof(who))
    {
        return 0;
     }
    target(" smiles at you mysteriously, which seems to summon an eerie presence.",who);
    actor("You smile mysteriously at",who);
    all2actbb(" smiles mysteriously at",who,", which seems to summon an "+
        "eerie presence.");
    return 1;
}

hail(string str)
{
    object *oblist;
    string sex;
    if (!strlen(str))
    {
        notify_fail("Hail who?\n");
        return 0;
    }
    oblist = parse_this(str,"%l");
    if (!sizeof(oblist))
    {
        return 0;
    }
    if (sizeof(oblist) !=1)
    {
        notify_fail("You can only hail one person at a time!\n");
        return 0;
    }
    if (!objectp(present("mclub_beads", oblist[0])))
    {
        notify_fail("You can only hail a club member.\n");
        return 0;
    }
    if (oblist[0]->query_gender() == G_MALE) sex = "Brother.'";
    else
    if (oblist[0]->query_gender() == G_FEMALE) sex = "Sister.'";
    else sex = "Friend.'";
    target(" kneels in front of you and intones, 'Hail "+sex+"",oblist);
    actor("You hail",oblist," in solemn humility.");
    all2actbb(" kneels before",oblist," and intones, 'Hail "+sex);
    return 1;
}

salute(string str)
{
    object *oblist;
    if(!strlen(str))
    {
        notify_fail("Salute who?\n");
        return 0;
    }
    oblist = parse_this(str,"%l");
    if(!sizeof(oblist))
    {
        return 0;
    }
    target(" salutes you in mystery.",oblist);
    actor("You salute",oblist," in mystery.");
    all2actbb(" salutes",oblist," in mystery.");
    return 1;
}

blink(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You blink.\n");
    all(" blinks.");
    return 1;
}

mcontemplate(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You turn to the east for a moment and contemplate the memory of the Ancient Ones.\n");
    all(" turns to the east for a moment, in silent contemplation of something mysterious.");
    return 1;
}

fathom(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You fathom the secrets of mystery that no one will ever know.\n");
    all(" fathoms the secrets of the Ancient darkness.");
    return 1;
}

wail(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You wail loudly.\n");
    all(" wails loudly.");
    return 1;
}

white(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("Your face goes white as you realize the gravity of the situation.\n");
    all("'s face goes white as "+this_player()->query_pronoun()+" realizes the gravity of the situation.");
    return 1;
}

mhang(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You hang your head in grief over Mystery.\n");
    all(" hangs "+MY+" head in grief over some terrible loss.");
    return 1;
}

mresign(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You resign yourself to life without Mystery.\n");
    all(" resigns "+this_player()->query_objective()+"self to something which seems to pain "+
    this_player()->query_objective()+".");
    return 1;
}

minvoke(string str)
{
    object tp;
    tp = this_player();
    if (str != "the Ancients") return 0;
    write("You fall to the ground and invoke the ancient words of summoning.\nNothing "+
        "happens.  You are left only with a hollow sense of emptiness.\n");
    all(" falls to "+this_player()->query_possessive()+" knees and cries out a mysterious "+
        "invocation.\nNothing happens.");
    return 1;
}

mshake(string str)
{
    object *oblist;
    if(!strlen(str))
    {
        notify_fail("Shake who?\n");
        return 0;
    }
    oblist = parse_this(str,"%l");
    if(!sizeof(oblist))
    {
        return 0;
    }
    if(sizeof(oblist) != 1)
    {
        notify_fail("You can only shake one person at a time!\n");
        return 0;
    }
    target(" grabs you by the shoulders and tries to shake some sense into you.",oblist);
    actor("You grab",oblist," and try to shake some sense into "+oblist[0]->query_objective()+".");
    all2actbb(" grabs",oblist," by the shoulders and tries to shake some sense into "+
        oblist[0]->query_objective()+".");
    return 1;
}

mbow(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You bow your head in rememberance.\n");
    all(" slowly lowers "+MY+" head and closes "+MY+" eyes in rememberance "+
        "for that which has past.");
    return 1;
}

mcall(string str)
{
    object tp;
    tp = this_player();
    if (str) return 0;
    write("You motion for a moment of silence.\n");
    all(" raises "+MY+" hand and calls for a moment of silence.");
    return 1;
}


int
cmd_list()
{
    object tp;
    tp = this_player();
    tp->catch_msg("The following emotes are available:\n"+
        "mblink - blink\n"+
        "mcurse (player(s)) - intone an ancient curse (on <player(s)>)\n"+
        "mfarewell <player(s)> - bid farewell to <player(s)>\n"+
        "(mcfarewell, mfare, and mcfare also work as mfarewell)\n"+
        "mfathom - fathom the secrets of mystery\n"+
        "mgaze - gaze off towards the east in thoughtful silence\n"+
        "mhail <player> - hail <player> in solemn humility\n"+
        "(mchail also works as mhail)\n"+
        "minvoke the Ancients - try in vain to invoke the Ancients\n"+
        "mbow - bow your head in rememberance\n"+
        "mcall - motion for a moment of silence\n"+
        "mcontemplate - turn east and contemplate the memory of the Ancient Ones\n"+
        "meyes - show the eyes of mystery\n"+
        "mhang - hang your head in grief over Mystery\n"+
        "mresign - resign yourself to life without Mystery\n"+
        "mshake <player(s)> - grab <player(s)> and try to shake some sense into them\n"+
        "msmile (player(s)) - smile mysteriously (at <player(s)>)\n"+
        "mpray (player(s)) - kneel and pray or pray for <player(s)>\n"+
        "mrend - rend your garments\n"+
        "mreverence <player(s)> - show your reverence for <player(s)>\n"+
        "msalute <player(s)> - salute <player(s)> in mystery\n"+
        "mscold <player(s)> - scold <player(s)> for being such a scrouge\n"+
        "mscorn <player(s)> - scorn <player(s)> with great contempt\n"+
        "msign (player(s)) - trace a mysterious sign (before <player(s)>)\n"+
        "mwail - wail loudly\n"+
        "mwhite - realize the gravity of the situation\n"+
        "\n"+
        "NOTE:  The ()'s mean optional, the <>'s mean mandatory.\n"+
        "\n");
    return 1;
}

mapping
query_cmdlist()
{
    return ([
        "msign":"sign",
        "mrend":"rend",
        "mgaze":"gaze",
        "mscold":"scold",
        "mscorn":"scorn",
        "mcurse":"curse",
        "mpray":"pray",
        "mreverence":"reverence",
        "mfarewell":"farewell",
        "mcfarewell":"farewell",
        "mfare":"farewell",
        "mcfare":"farewell",
        "mbow":"mbow",
        "mcall":"mcall",
        "meyes":"meyes",
        "mhang":"mhang",
        "mresign":"mresign",
        "mshake":"mshake",
        "msmile":"msmile",
        "mhail":"hail",
        "mchail":"hail",
        "msalute":"salute",
        "mblink":"blink",
        "mcontemplate":"mcontemplate",
        "mwail":"wail",
        "mwhite":"white",
        "mfathom":"fathom",
        "minvoke":"minvoke",
        "mclist":"cmd_list",
    ]);
}
