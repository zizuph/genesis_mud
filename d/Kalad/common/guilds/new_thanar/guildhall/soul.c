/**********************************************************************
 * - soul.c                                                         - *
 * - Recode of Race guild Thanar soul                               - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "guild.h"
#include <adverbs.h>
#include <tasks.h>

inherit "/cmd/std/command_driver"; 
inherit "/lib/commands";

#define SUBLOC_SOULEXTRADESC ("_soul_cmd_extra")
#define SOULDESC(x)          (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Thanarian"; }

public mapping
query_cmdlist()
{
    return ([
         "thaccept" : "thaccept",
         "thamused" : "thamused",
           "thcomp" : "thcomp",
            "thbow" : "thbow",
          "thcurse" : "thcurse",
        "thcruelty" : "thcruelty",
        "thdecline" : "thdecline",
      "thdisregard" : "thdisregard",
          "thglare" : "thglare",
          "thgreet" : "thgreet",
           "thgrin" : "thgrin",
         "thhatred" : "thhatred",
           "thhelp" : "thhelp",
            "thjoy" : "thjoy",
          "thlaugh" : "thlaugh",
           "thlist" : "thlist",
         "thlisten" : "thlisten",
           "thlook" : "thlook",
          "thlook2" : "thlook2",
            "thnod" : "thnod",
           "thpray" : "thpray",
         "thpreach" : "thpreach",
        "thpresent" : "thpresent",
          "thpride" : "thpride",
        "threspect" : "threspect",
      "thsacrifice" : "thsacrifice",
          "thshout" : "thshout",
          "thsneer" : "thsneer",
          "thspeak" : "thspeak",
      "thsuspicion" : "thsuspicion",
          "thswear" : "thswear",
          "ththink" : "ththink",
        "thtorture" : "thtorture",
    ]);
}

public void
using_soul(object live)
{
    if (!objectp(live))
	return;

    live->add_subloc(GUILD_SUBLOC, this_object());
}

string
show_subloc(string subloc, object on, object who)
{
    string str;

    if (subloc != GUILD_SUBLOC)
	return "";

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    return (on == who ? "You have" : capitalize(on->query_pronoun()) +
           " has") + " an egotistical veneer.\n";
}

/**********************************************************************
 * - Emotions in alphabetic order please.                           - *
 **********************************************************************/
int
thaccept(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	if (strlen(parse_msg))
	{
	    write(parse_msg);
	    return 1;
	}

	notify_fail("Accept whom?\n");
	return 0;
    }

    actor("You give", oblist, " a sign of acceptance.");
    all2act(" gives", oblist, " a sign of acceptance.");
    target(" gives you a sign of acceptance.", oblist,"");
    return 1;
}


int
thamused(string str)
{
    object *oblist;
    if (!stringp(str))
    {
	write("You look around with a totally amused expression.\n");
	allbb(" looks around with a totally amused expression.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Amused at whom?\n");
        return 0;
    }


    actor("You look at", oblist," with a totally amused "+
      "expression.",);
    all2actbb(" looks at", oblist, " with a totally amused "+
      "expression.","");
    target(" looks at you with a totally amused "+
      "expression.", oblist,"");

    return 1;
}

int
thcomp(string str)
{
    object *oblist;
    if (!stringp(str))
    {
	write("You express your compassion and pity for the downtrodden.\n");
	allbb(" expresses compassion and pity for the downtrodden.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Express your compassion and pity towards whom?\n");
        return 0;
    }


    actor("You look at", oblist," with compassion and pity "
    +"because its well deserved.",);
    all2actbb(" looks at", oblist, "with compassion and pity.","");
    target(" looks at you with deep compassion and pity.", oblist,"");

    return 1;
}

int
thbow(string str)
{
    object *oblist;
    if (!stringp(str))
    {

	{
	    write("You bow with a display of style and benevolence "+
	      "befitting a Thanarian human.\n");
	    allbb(" bows with a display of style and malevolence "+
	      "befitting a Thanarian human.");
	    return 1;
	}

    }
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Bow at whom/what?\n");
        return 0;
    }
    {
	actor("You bow before",oblist," with a display of style and "+
	  "benevolence befitting a Thanarian human.");
	targetbb(" bows before you with a display of style and "+
	  "malevolence befitting a Thanarian human.", oblist);
	all2actbb(" bows before",oblist," with a display of style and "+
	  "malevolence befitting a Thanarian human.");
	return 1;
    }

}

int
thcurse(string str)
{
    object *oblist;
    if (!stringp(str))
    {

	{
	    write("You spit on the ground in disgust and curse "+
	      "loudly in the name of Thanar.\n");
	    allbb(" spits on the ground in disgust and curses "+
	      "loudly in the name of Thanar.");
	    return 1;
	}

    }
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Curse whom/what?\n");
        return 0;
    }
    {
	actor("You spit on",oblist," while calling upon "+
	  "the wrath of Thanar.");
	targetbb(" spits on you while calling upon the "+
	  "wrath of Thanar.", oblist);
	all2actbb(" spits on",oblist," while calling upon the "+
	  "wrath of Thanar.");
	return 1;
    }

}

int
thcruelty(string str)
{
    object *oblist;
    if (!stringp(str))
    {

	{
	    write("You develop a malicious and devious look on your "+
	      "face in anticipation of committing acts of cruelty.\n");
	    allbb(" develops a malicious and devious look of cruelty on "+
	      ""+ this_player()->query_possessive() + " face.");
	    return 1;
	}

    }
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Be cruel at whom/what?\n");
        return 0;
    }
    {
	actor("You relate your most malicious and devious "+
	  "ideas of cruelty to",oblist,".");
	targetbb(" relates in detail "+ this_player()->query_possessive() + " "+
	  "most malicious and devious ideas of cruelty to you.", oblist);
	all2actbb(" speaks quietly to",oblist," while a most "+
	  "malicious and devious look of cruelty crosses "+
	  ""+ this_player()->query_possessive() + " face.");
	return 1;
    }

}

int
thdecline(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	if (strlen(parse_msg))
	{
	    write(parse_msg);
	    return 1;
	}

	notify_fail("Decline whom?\n");
	return 0;
    }

    actor("You decline", oblist, "'s offer demonstrating scorn.",);
    all2act(" declines", oblist, "'s offer demonstrating scorn.",);
    target(" declines your offer demonstrating scorn.",
      oblist, "",ACTION_INGRATIATORY);
    return 1;
}

int
thdisregard(string str)
{
    object *oblist;
    if (!stringp(str))
    {

	{
	    write("You quickly scan the area and disregard everything that "+
	      "is not a threat.\n");
	    allbb(" quickly scans the area with a disregarding look.");
	    return 1;
	}

	return 1;
    }
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Disregard whom/what?\n");
        return 0;
    }
    {
	actor("You cast",oblist," a disregarding look.");
	targetbb(" casts you a disregarding look.", oblist);
	all2actbb(" casts",oblist," a disregarding look.");
	return 1;
    }

}

int
thglare(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l", ACTION_INGRATIATORY);

    if (!sizeof(oblist))
    {
	if (strlen(parse_msg))
	{
	    write(parse_msg);
	    return 1;
	}

	notify_fail("Glare at whom?\n");
	return 0;
    }

    actor("You glare at", oblist, " with utter contempt and rage.");
    all2act(" glares at", oblist, " with utter contempt and rage.", 
      "", ACTION_INGRATIATORY);
    target(" glares at you with utter contempt and rage.",
      oblist, "", ACTION_INGRATIATORY);
    return 1;
}

int
thgreet(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l", ACTION_INGRATIATORY);

    if (!sizeof(oblist))
    {
	if (strlen(parse_msg))
	{
	    write(parse_msg);
	    return 1;
	}

	notify_fail("Greet whom?\n");
	return 0;
    }

    actor("You raise your hand toward", oblist, " in greeting "+
      "saying: Hail to Thanar!",);
    all2act(" raises "+HIS(TP) +" hand towards", oblist, " in "+
      "greeting saying: Hail to Thanar!", "",);
    target(" raises "+HIS(TP) +" hand towards you in greeting "+
      "saying: Hail to Thanar!",oblist, "");
    return 1;
}

int
thgrin(string str)
{
    object *oblist;
    if (!stringp(str))
    {
	write("You grin with utter political power sparkling in your eyes.\n");
	allbb(" grins with utter political power sparkling "+
	  "in " + HIS(TP) + " eyes.", "",);
	return 1;
    }
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Grin at whom/what?\n");
        return 0;
    }
    actor("You grin at",oblist," with utter political power "
    +"sparkling in your eyes.");
    targetbb(" grins at you with utter political power sparkling in "+
      ""+ HIS(TP) +" eyes.", oblist, "");
    all2actbb(" grins at", oblist, " with utter political power sparkling in "+
      ""+ HIS(TP) +" eyes.");
    return 1;
}

int
thhatred(string str)
{
    object *oblist;
    if (!stringp(str))
    {

	{
	    write("You glance around with a look of pure hatred.\n");
	    allbb(" glances around with a look of pure hatred.");
	    return 1;
	}

    }
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Hatred at whom/what?\n");
        return 0;
    }
    {
	actor("You look at",oblist," with utter contempt and "+
	  "burning hatred.");
	targetbb(" looks at you with utter contempt and "+
	  "burning hatred.", oblist);
	all2actbb(" looks at",oblist," with utter contempt "+
	  "and burning hatred.");
	return 1;
    }

}
public int
thhelp(string str)
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

int
thjoy(string str)
{

      write("Your heart fills with joy as you smile, knowing that "+
        "nothing can defeat the will of Thanar.\n");
      allbb("'s smiles with a joyful gleam in "+ HIS(TP) +" eyes.",);
      return 1;
}
mixed
get_title(object who)
{
    if (!who->query_guild_member(GUILD_NAME))
    {
	return 0;
    }


    if (wildmatch("*jr", who->query_real_name()))
    {
	return 0;
    }

    if (who->query_wiz_level())
    {
	if (SECURITY->query_guild_is_master("thanarian", who->query_real_name()))
	    return who->query_name();
	else
	    return 0;
    }
    else
	return who->query_name() + " " + who->query_guild_title_race();
}

int
thlaugh(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "cruelly", 0);

    if (!stringp(how[0]))
    {
        SOULDESC("laughing" + how[1]);
        write("You laugh" + how[1] + " with a superior sparkle in "+
          "your human eyes.\n");
        allbb(" laughs" + how[1] + " with a superior sparkle in "+
          ""+ HIS(TP) +" human eyes.", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Laugh [how] at whom/what?\n");
        return 0;
    }

    SOULDESC("laughing" + how[1]);
    actor("You laugh" + how[1] + " with a superior sparkle in "+
          "your human eyes at", oblist);
    all2actbb(" laughs" + how[1] + " with a superior sparkle in "+
          ""+ HIS(TP) +" human eyes at", oblist, 0, how[1]);
    targetbb(" laughs" + how[1] + " with a superior sparkle in "+
          ""+ HIS(TP) +" human eyes at you.", oblist, how[1]);
    return 1;
}

int
thlist(string str)
{
    string *titles;

    if (this_player()->query_attack())
    {
	notify_fail("You cannot concentrate on this while in "+
	  "combat!\n");
	return 0;
    }

    write("You offer a devout prayer to the great God Thanar.\n");

    titles = map(users() - ({ this_player() }), get_title) - ({ 0 });

    write("You sense that there "+(sizeof(titles) == 1 ? "is": "are")+" "+
      ""+ (sizeof(titles) ? LANG_WNUM(sizeof(titles)) : "no") +
      " other " + ((sizeof(titles) == 1) ? "Thanarian's around"+
        "" : "Thanarian's around") + ".\n");
    
    map(titles, write @ &sprintf("- %-=70s\n", ));

    write("\n");

    return 1;
}

int
thlisten(string str)
{
    object *oblist;
    if (!stringp(str))
    {
	write("You instinctively turn to a sound and listen closely.\n");
	allbb(" moves suddenly as if listening to something.");
	return 1;
    }
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Listen to whom/what?\n");
        return 0;
    }
    actor("You turn toward",oblist," trying to hide your disdain "+
      "as you listen.");
    targetbb(" turns toward you with an odd expression while "+
      ""+ HE(TP) +" listens to you.", oblist,);
    all2actbb(" turns toward", oblist," "+
      "with an odd expression as " + HE(TP) + " listens.");
    return 1;
}

int
thlook(string str)
{
    object *oblist;
    if (!stringp(str))
    {
	write("You gaze around with a barely concealed "+
	  "look of overwhelming arrogance.\n");
	allbb(" gazes around with a barely concealed "+
	  "look of overwhelming arrogance.");
	return 1;
    }
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Look at whom/what?\n");
        return 0;
    }
    actor("You look at",oblist," with a barely concealed "+
      "look of overwhelming arrogance.");
    targetbb(" looks at you with a barely concealed look "+
      "of overwhelming arrogance.", oblist);
    all2actbb(" looks at",oblist," with a barely concealed "+
      "look of overwhelming arrogance.");
    return 1;
}

int
thlook2(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "cruelly", 0);

    if (!stringp(how[0]))
    {
        write("You crack your knuckles while" + how[1] + " "+
          "looking around the area.\n");
        allbb(" cracks "+ HIS(TP) +" knuckles while" + how[1] + " "+
          "looking around the area.", how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Laugh [how] at whom/what?\n");
        return 0;
    }

    actor("You crack your knuckles while" + how[1] + " looking at", oblist);
    all2actbb(" cracks "+ HIS(TP) +" knuckles while" + how[1] + " looking "+
      "at", oblist, 0, how[1]);
    targetbb(" cracks "+ HIS(TP) +" knuckles while" + how[1] + " looking "+
      "at you.", oblist, how[1]);
    return 1;
}

int
thnod(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "arrogantly", 0);

    if (!stringp(how[0]))
    {
        write("You feel quite bored with the whole situation "+
          "so you simply nod" + how[1] + ".\n");
        allbb(" appears quite bored with this whole situation then "+
          ""+ HE(TP) +" simple nods" + how[1] + ".", how[1]);
        SOULDESC("nodding" + how[1]);
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Nod [how] at whom/what?\n");
        return 0;
    }

    SOULDESC("nodding" + how[1]);
    actor("You feel quite bored and nod" + how[1] + " at", oblist);
    all2actbb(" looks quite bored while " + HE(TP) + " "+
      "nods" + how[1] + " at", oblist, 0, how[1]);
    targetbb(" looks quite bored while " + HE(TP) + " "+
      "nods" + how[1] + " at you.", oblist, how[1]);
    return 1;
}

int
thpray(string str)
{
    object *oblist;
    if (!stringp(str))
    {

    write("You offer up faithful prayers for strength to the great Thanar.\n");
    allbb(" whispers in an unknown language.");
    return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Pray for whom/what?\n");
        return 0;
    }
    actor("You reach outwards toward", oblist," whispering an ancient "+
      "prayer that the great Thanar alone has taught you.");
    targetbb(" reaches towards you whispering an ancient "+
      "prayer.", oblist);
    all2actbb(" reaches outward towards",oblist," whispering "+
      "some ancient words of prayer.");
    return 1;
}

int
thpreach(string str)
{
    object *oblist;
    if (!stringp(str))
    {

    write("You begin to preach the praises of Thanar's world "+
      "vision, a vision where humanity, shall hold positions "+
      "of power and defend Kalad from the Saurians and Goblins "+
      "who seek to destroy it.\n");
    allbb(" begins to preach the praises of Thanar's world "+
      "vision, a vision where humanity, shall hold positions "+
      "of power and defend Kalad from the Saurians and Goblins "+
      "who seek to destroy it.");
    SOULDESC("preaching the glories of Thanar's vision for Kalad");    
    return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Preach the ways of Thanar to whom?\n");
        return 0;
    }
    
    SOULDESC("preaching the glories of Thanar's world vision");
    actor("You begin to preach to", oblist, " about the great Thanar's "+
      "vision in defence of Kalad.");
    targetbb(" begins to preach to you about Thanar's "+
      "vision in defence of Kalad.", oblist);
    all2actbb(" begins to preach to", oblist, " about Thanar's "+
      "vision in defence of Kalad.");
    return 1;
}

int
thpresent(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l", ACTION_INGRATIATORY);

    if (!sizeof(oblist))
    {
	if (strlen(parse_msg))
	{
	    write(parse_msg);
	    return 1;
	}

	notify_fail("Present yourself to whom?\n");
	return 0;
    }

    actor("You present yourself to", oblist, " "+
      "by gesturing to " + (sizeof(oblist) > 1 ? "them" : 
	oblist[0]->query_objective()) + " quite arrogantly with a "+
	"slight nod.");
    all2act(" presents "+ this_player()->query_objective() +"self to", 
      oblist, " as an arrogant Thanarian would.", 
      "", ACTION_INGRATIATORY); 
    target(" presents "+ this_player()->query_objective() +
      "self to you just as an arrogant Thanarian would.", 
      oblist, "", ACTION_INGRATIATORY);
    return 1;
}

int
thpride()
{
    write(" You stand tall and erect brimming with pride.\n");
    allbb(" stands tall and erect brimming with pride "+
      "in every arrogant feature.");
    return 1;
}

int
threspect(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l", ACTION_INGRATIATORY);

    if (!sizeof(oblist))
    {
	if (strlen(parse_msg))
	{
	    write(parse_msg);
	    return 1;
	}

	notify_fail("Show respect to who/whom?\n");
	return 0;
    }

    actor("You look at" + (sizeof(oblist) > 1 ? " each of" : ""),
          oblist, " with great respect, judging them for being quite shrewd.");
    all2act(" looks at", oblist," with great respect.", "",
            ACTION_INGRATIATORY);
    target(" looks at you with respect for being a shrewd "+
      "individual.", oblist, "", ACTION_INGRATIATORY);
    return 1;
}

int
thsacrifice(string str)
{
    object *oblist;
    if (!stringp(str))
    {

      write("You look around the area for a suitable "+
        "sacrifice to Thanar.\n");
      allbb(" looks around the area for a suitable "+
        "sacrifice to Thanar.");
      SOULDESC("looking around the area for a suitable sacrifice to Thanar");
      return 1;
   }
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Pray for whom/what?\n");
        return 0;
    }
    SOULDESC("looking around the area for a suitable sacrifice to Thanar");
    actor("You gaze very intently at", oblist, ", your next "+
      "convert to Thanar.");
    targetbb( "gazes very intently at you, for you are the next "+
      "convert to Thanar.", oblist);
     all2actbb(" gazes very intently at", oblist, ", the next "+
       "convert to Thanar.");
    return 1;
}

int
thshout(string str)
{
    object *oblist;
    if (!stringp(str))
    {

    write("You shout out in pure ecstasy at all the "+
      "glory that shall belong to Thanar.\n");
    allbb(" shouts out in pure ecstasy at all the glory "+
      "that shall belong to Thanar.");
    SOULDESC("shouting out loud in pure ecstasy");
    return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Shout at who/whom?\n");
        return 0;
    }
    SOULDESC("shouting out loud in pure ecstasy");
    actor("You shout at", oblist, " in pure ecstasy, "+
      "for all glory is Thanar's.");
    targetbb(" shouts at you in pure ecstasy, for all glory "+
      "is Thanar's.", oblist);
    all2actbb(" shouts at", oblist, " in pure ecstasy, for all "+
      "glory is Thanar's.");
    return 1;
}

int
thsneer(string str)
{
    object *oblist;
    if (!stringp(str))
    {

    write("You sneer in obvious derision and complete "+
      "contempt of everything in sight.\n");
    allbb(" sneers in obvious derision and complete "+
      "contempt of everything in sight.");
    SOULDESC("sneering with contempt");
    return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Sneer at who/whom?\n");
        return 0;
    }
    SOULDESC("sneering with contempt");
    actor("You sneer at", oblist, " in obvious derision and "+
      "complete contempt.");
    targetbb(" sneers at you in obvious derision and complete "+
      "contempt.", oblist);
    all2actbb(" sneers at", oblist, " in obvious derision and "+
      "complete contempt.");
    return 1;
}

int
thspeak(string str)
{
    object *oblist;
    int i;

    if (!strlen(str))
    {
	notify_fail("You wish to say what in the ancient "+
	  "tongue of Thanar?\n");
	return 0;
    }

    oblist = FILTER_PLAYERS(all_inventory(environment(this_player())));
    oblist -= ({ this_player() });

    write("In the ancient Thanar tongue, you say: " + str + "\n");

    for (i = 0; i < sizeof(oblist); i++)
    {
	if ((IS_MEMBER(oblist[i])) || oblist[i]->query_wiz_level())
	{
	    oblist[i]->catch_tell(this_player()->query_The_name(oblist[i]) +
	      " speaks in an ancient tongue saying: " + str + "\n");
	}
	else
	{
	    oblist[i]->catch_tell(this_player()->query_The_name(oblist[i]) +
	      " speaks in an ancient tongue, that you do not understand.\n");
	}
    }

    return 1;
}

int
thsuspicion(string str)
{
    object *oblist;
    if (!stringp(str))
    {
    
    write("You peer around the room suspiciously, searching for thieves.\n");
    allbb(" peers around the room suspiciously, searching for thieves.");
    SOULDESC("peering around suspiciously");
    return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Suspect who/whom?\n");
        return 0;
    }
   
   SOULDESC("peering around suspiciously, searching for thieves");
   actor("You peer at", oblist, " suspiciously, searching for "+
     "any sign of thievery.");
   targetbb(" watches you suspiciously, as though you were a thief.", oblist);   
   all2actbb(" peers at", oblist, " suspiciously, searching for "+
     "any sign of thievery.");
    
   return 1;
}

int
thswear(string str)
{
    object *oblist;
    if (!stringp(str))
    {
    
    write("You swear profusely and curse the Goblins and Saurians of Kalad.\n");
    allbb(" swears profusely and curses the Goblins and Saurians of Kalad.");
    return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Swear at who/whom?\n");
        return 0;
    }
   
   actor("You swear profusely and curse at", oblist, ".");
   targetbb(" swears profusely and curses at you.", oblist);   
   all2actbb(" swears profusely and curses at", oblist, ".");
    
   return 1;
}

int
ththink()
{
    write("You run your fingertips along your chin in "+
      "an arrogant manner.\n");
    allbb(" runs "+ HIS(TP) +" fingertips along "+
    ""+ HIS(TP) + " chin in an arrogant manner.", "");
    return 1;
}

int
thtorture(string str)
{
   object *oblist;
   if (!stringp(str))
   {
    
   write("You search for someone to torture.\n");
   allbb(" searches for someone to torture.");
   SOULDESC("searching for someone to torture");
   return 1;
   }

   oblist = parse_this(str, "[at] [the] %i");

   if (!sizeof(oblist))
   {
       notify_fail("Torture who/whom?\n");
       return 0;
   }
   SOULDESC("looking around, searching for someone to torture");   
   actor("You are ready to cruelly torture", oblist, " without mercy.");
   targetbb(" is ready to cruelly torture you without mercy.", oblist);   
   all2actbb(" is ready to cruelly torture", oblist, " without mercy.");
    
   return 1;
}

