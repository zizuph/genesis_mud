/*********************************************************************
 * - soul.c                                                        - *
 * - Created By Damaris@SaV                                        - *
 * - Recoded by Damaris@Genesis 03/2006                            - *
 *********************************************************************/

#pragma strict_types 

inherit "/cmd/std/command_driver"; 
inherit "/lib/commands";
#include "guild.h"
#include "/d/Khalakhor/sys/basic.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <filter_funs.h>
#include <flags.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

string
get_soul_id()
{
	return "temptresses";
}

int
query_cmd_soul()
{
	return 1;
}

mapping
query_cmdlist()
{
	return ([
	/* Command name : Function name */
	          "tc" : "tc",
	      "tcbeck" : "tcbeckon",
	    "tcbeckon" : "tcbeckon",
	       "tcbeg" : "tcbeg",
	      "tcbite" : "tcbite",
	       "tcbow" : "tcbow",
	    "tccaress" : "tccaress",
	   "tccomfort" : "tccomfort",
	      "tccurl" : "tccurl",
	     "tccrawl" : "tccrawl",
	     "tcdance" : "tcdance",
	    "tcfrench" : "tcfrench",
	      "tcgrin" : "tcgrin",
	      "tchelp" : "tchelp",
	       "tchug" : "tchug",
	      "tckiss" : "tckiss",
	      "tclick" : "tclick",
	     "tclaugh" : "tclaugh",
	      "tclook" : "tclook",
	      "tclove" : "tclove",
	      "tclust" : "tclust",
	      "tcmove" : "tcmove",
	    "tcnibble" : "tcnibble",
	     "tcoffer" : "tcoffer",
	      "tcpout" : "tcpout",
	       "tcrub" : "tcrub",
	       "tcsay" : "tcsay",
	    "tcseduce" : "tcseduce",
	      "tcsigh" : "tcsigh",
	     "tcsmile" : "tcsmile",
	    "tcshimmy" : "tcshimmy",
	  "tcstraight" : "tcstraight",
	   "tcstretch" : "tcstretch",
	    "tcstroke" : "tcstroke",
	     "tcthink" : "tcthink",
	     "tctrace" : "tctrace",
	      "tcwarn" : "tcwarn",
	      "tcwave" : "tcwave",
	      "tcwipe" : "tcwipe",
	   "tcwhisper" : "tcwhisper",
                ]);
}
void
using_soul(object live)
{
	if (!objectp(live))
	return;
	/* This adds the subloc. */
	live->add_subloc("temptress_subloc", this_object());
	
	/* This makes us look good.. no makeup needed! */
	live->set_appearance_offset(-150);
	
	setuid(); seteuid(getuid());
	
	/*
	if (!present(OBJECT_ID, live))
	clone_object(OBJECT)->move(live);
	*/

}

string
show_subloc(string subloc, object on, object who)
{
	string str;
	if (subloc != "temptress_subloc")
	return "";
	
	if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
	return (on == who ? "You glow"+
	"" : capitalize(on->query_pronoun()) + " glows") +" with "+
	"feminine enticement.\n";
}

string
tadverb()
{
	string *words = ({
		"smoothly", "softly", "gently", "tenderly",
		});
		return words[random(sizeof(words))];
}

int
tc(string str)
{
	string *words;
	if (!strlen(str))
	{
		notify_fail("Perform which Temptress command? " +
		"Syntax: tc <command> [<arguments>]\n");
		return 0;
	}
	words = explode(str, " ");
	if (!stringp(cmdlist[words[0]]))
	{
		notify_fail("The command " + words[0] +
		" is not a known Temptress command.\n");
		return 0;
	}
	str = ((sizeof(words) > 1) ? implode(words[1..], " ") : "");
	return call_other(this_object(), cmdlist[words[0]], str);
}

int
tcbeckon(string str)
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
		notify_fail("Tcbeckon whom?\n");
		return 0;
	}
	actor("You temptingly beckon", oblist, " to you.");
	all2act(" beckons", oblist, " to " +
	this_player()->query_objective() + ".", "",
	ACTION_INGRATIATORY);
	target(" temptingly beckons you to "+
	this_player()->query_objective() + ".", oblist, "",
	ACTION_INGRATIATORY);
	return 1;
}

int
tcbeg(string str)
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
		notify_fail("Tcbeg whose forgiveness?\n");
		return 0;
	}
	actor("You fall on your knees begging forgiveness from" +
	(sizeof(oblist) > 1 ? " each of" : ""), oblist,
	" for your temptress ways.");
	all2act(" falls on " + HIS(TP) + " knees begging forgiveness "+
	"from", oblist, " for " + HIS(TP) + " temptress ways.", "",
	ACTION_INGRATIATORY);
	target(" falls on " + HIS(TP) + " knees begging your forgiveness "+
	"for "+ HIS(TP) +" temptress ways.", oblist, "",
	ACTION_INGRATIATORY);
	return 1;
}

int
tcbite(string str)
{
	object *oblist;
	string *how;
	string location, tadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	tadv = tadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ tadv +" bites along the back of your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" bite along the back "+
			"of", oblist, "'s " + location + ".",);
			all2act(" "+ tadv +" bites along the back "+
			"of", oblist, "'s " + location + ".", "", attrs,);
			return 1;
			
			case "abdomen":
			case "arm":
			case "belly":
			case "cheek":
			case "chin":
			case "ear":
			case "wrist":
			case "hand":
			case "hands":
			case "knee":
			case "lips":
			case "palm":
			case "shouler":
			case "stomach":
			case "thigh":
			case "tummy":
			target(" "+ tadv +" bites along your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" bite along", oblist, "'s "+
			"" + location + ".",);
			all2act(" "+ tadv +" bites along", oblist, "'s "+
			"" + location + ".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Tcbite whom [where / how]?\n");
			return 0;
		}
		return 1;
	}
	if (strlen(parse_msg))
	{
		write(parse_msg);
		return 1;
	}
	how = parse_adverb_with_space(str, "gently", 1);
	oblist = parse_this(how[0], "[the] %l", attrs);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tcbite whom [how / where]?\n");
		return 0;
	}
	actor("You bite", oblist, how[1] + ".");
	all2act(" bites", oblist, how[1] + ".", how[1], attrs);
	target(" bites you" + how[1] + ".", oblist, how[1], attrs);
	return 1;
}

int
tcbow(string str)
{
	object *oblist;
	string *how;
	how = parse_adverb_with_space(str, "temptingly", 0);
	if (!stringp(how[0]))
	{
		write("You bow" + how[1] + ", displaying a slight "+
		"amount of cleavage.\n");
		allbb(" bows" + how[1] + ", displaying a slight amount "+
		"of cleavage.", how[1], ACTION_VISUAL | ACTION_MACTIVITY);
		return 1;
	}
	oblist = parse_this(how[0], "[to] / [before] [the] %i",
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
        
        if (!sizeof(oblist))
        {
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tcbow [how] to whom/what?\n");
		return 0;
	}
	actor("You" + how[1] + " bow to", oblist,", displaying a "+
	"slight amount of cleavage.");
	all2actbb(""+ how[1] + " bows to", oblist, ", displaying a "+
	"slight amount cleavage.", how[1],
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
        targetbb("" + how[1] + " bows before you, displaying a slight "+
        "amount of cleavage.", oblist, how[1],
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
        return 1;
}

int
tccaress(string str)
{
	object *oblist;
	string *how;
	string location, tadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	tadv = tadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ tadv +" caresses along the back of "+
			"your " + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" caress along the back "+
			"of", oblist, "'s " + location + ".", );
			all2act(" "+ tadv +" caresses along the back "+
			"of", oblist, "'s " + location + ".", "", attrs,);
			return 1;
			
			case "abdomen":
			case "arm":
			case "belly":
			case "cheek":
			case "chin":
			case "ear":
			case "wrist":
			case "hand":
			case "hands":
			case "knee":
			case "lips":
			case "palm":
			case "shoulder":
			case "stomach":
			case "thigh":
			case "tummy":
			target(" "+ tadv +" caresses along your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" caress along", oblist, "'s "+
			"" + location + ".",);
			all2act(" "+ tadv +" caresses along", oblist, "'s "+
			"" + location + ".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Tccaress whom [where / how]?\n");
			return 0;
		}
		return 1;
	}
	if (strlen(parse_msg))
	{
		write(parse_msg);
		return 1;
	}
	how = parse_adverb_with_space(str, "playfully", 1);
	oblist = parse_this(how[0], "[the] %l", attrs);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tccaress whom [how / where]?\n");
		return 0;
	}
	actor("You caress", oblist, how[1] + ".");
	all2act(" caresses", oblist, how[1] + ".", how[1], attrs);
	target(" caresses you" + how[1] + ".", oblist, how[1], attrs);
	return 1;
}

int
tccomfort(string str)
{
	object *oblist;
	oblist = parse_this(str, "[the] %l", ACTION_CONTACT | ACTION_INTIMATE);
	
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tccomfort whom?\n");
		return 0;
	}
	actor("You comfort" + (sizeof(oblist) > 1 ? " each "+
	"of" : ""), oblist," against your tempting bosom.");
	all2act(" comforts", oblist, " against "+
	""+ this_player()->query_objective() +" tempting "+
	"bosom.", "",    ACTION_CONTACT | ACTION_INTIMATE);
	target(" comforts you lovingly against "+
	""+ this_player()->query_objective() +" tempting "+
	"bosom.", oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
	return 1;
}

int
tccurl(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You curl up and sit in the corner, looking so "+
		"tempting.\n");
		allbb(" curls up and sits in the corner, looking so "+
		"tempting.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tccurl up with whom?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You can only tccurl up in one set of"+
		"arms.\n");
		return 0;
	}
	actor("You curl up in",oblist,"'s arms, looking quite the "+
	"temptress.",);
	targetbb(" curls up in your arms, looking quite the "+
	"temptress.", oblist,"");
	all2actbb(" curls up in",oblist,"'s arms, looking quite the "+
	"temptress.", "",);
	return 1;
}

int
tccrawl(string str)
{
	object *oblist;
	string *how;
	how = parse_adverb_with_space(str, "sensually", 0);
	if (!stringp(how[0]))
	{
		write("You slip onto all fours and crawl" + how[1] + " "+
		"around while swaying your hips gently.\n");
		allbb(" slips onto all fours and crawls" + how[1] + " "+
		"around while swaying "+ HIS(TP) +" hips gently.");
		return 1;
	}
	oblist = parse_this(how[0], "[to] / [before] [the] %i",
	ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tccrawl [how] to whom/what?\n");
		return 0;
	}
	actor("You slip onto all fours and crawl" + how[1] + " "+
	"toward",oblist,", swaying your hips gently.");
	targetbb(" slips onto all fours and crawls" + how[1] + " "+
	"towards you, swaying "+ HIS(TP) +" hips gently.", oblist);
	all2actbb(" slips onto all fours and crawls" + how[1] + " "+
	"toward",oblist,", swaying "+ HIS(TP) +" hips gently.");
	return 1;
}

int
tcdance(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You sensually sway your hips in a tempting dance " +
		"of desire.\n");
		allbb(" sensually sways "+ HIS(TP) +" hips in a tempting "+
		"dance of desire.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tcdance with whom?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You can only Tcdance with one person "+
		"at a time.\n");
		return 0;
	}
	actor("You sensually slip your arms around", oblist, "'s neck, "+
	"pressing your body to " + oblist[0]->query_possessive() +
	" and swaying your hips in a tempting dance of desire.",);
	all2actbb(" sensually slips "+ HIS(TP) +" arms "+
	"around", oblist, "'s neck, pressing "+ HIS(TP) +" body to "+
	"" + oblist[0]->query_possessive() + " and swaying "+
	""+ HIS(TP) +" hips in a tempting dance of desire.", "",);
	target(" sensually slips "+ HIS(TP) +" arms around your "+
	"neck, pressing "+ HIS(TP) +" body to yours and swaying "+
	""+ HIS(TP) +" hips in a tempting dance of desire.", oblist, "");
	return 1;
}

int
tcfrench(string str)
{
	object *oblist;
	oblist = parse_this(str, "[the] %l", ACTION_CONTACT | ACTION_INTIMATE);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
	notify_fail("Tcfrench whom?\n");
	return 0;
	}
	actor("You trace",oblist,"'s lips with your tongue before "+
	"slipping it inside "+
	"" + oblist[0]->query_possessive() +" mouth, beginning a slow "+
	"dance with your tongue.",);
	all2act(" gives", oblist, " a deep and passionate kiss.", "",
	ACTION_CONTACT | ACTION_INTIMATE);
	target(" traces your lips with "+ HIS(TP) + " tongue before "+
	"slipping it inside your mouth, beginning a slow dance with "+
	"your tongue.", oblist, "",
	ACTION_CONTACT | ACTION_INTIMATE);
	return 1;
}

int
tcgrin(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("Your lips curl into a temptingly sexy grin.\n");
		allbb(" curls "+ this_player()->query_possessive() +
		" lips into a temptingly sexy grin.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tcgrin at whom?\n");
		return 0;
	}
	actor("Your lips curl into a temptingly sexy grin "+
	"at", oblist, ".");
	targetbb(" curls " + HIS(TP) + " lips into a temptingly sexy "+
	"grin at you.", oblist);
	all2actbb(" curl " + HIS(TP) + " lips into a temptingly sexy "+
	"grin at", oblist, ".");
	return 1;
}

int
tchug(string str)
{
	int size;
	object *oblist;
	oblist = parse_this(str, "[the] %l", ACTION_CONTACT | ACTION_INTIMATE);
	if (!(size = sizeof(oblist)))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		return notify_fail("Tchug whom?\n");
	}
	actor("You sensually wrap your arms around" +
	(size > 1 ? " each of" : ""), oblist, "'s neck and hug " +
	(size > 1 ? "them" : oblist[0]->query_objective()) +
	" enticingly.",);
	all2act(" sensually wraps " + HIS(TP) + " arms "+
	"around", oblist,"'s neck and hugs " +
	(size > 1 ? "them" : oblist[0]->query_objective()) +
	" enticingly.", "", ACTION_CONTACT | ACTION_INTIMATE,);
	target(" sensually wraps "+ HIS(TP) + " arms around your "+
	"neck and hugs you enticingly.",
	oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
	return 1;
}

int
tckiss(string str)
{
	object *oblist;
	string *how;
	string location, tadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	tadv = tadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ tadv +" brushes "+ HIS(TP) +" "+
			"lips along the back of your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" brush your lips "+
			"along the back "+
			"of", oblist, "'s " + location + ".",);
			all2act(" "+ tadv +" brushes "+ HIS(TP) +" "+
			"lips along the back "+
			"of", oblist, "'s " + location + ".", "", attrs,);
			return 1;
			
			case "abdomen":
			case "arm":
			case "belly":
			case "cheek":
			case "chin":
			case "ear":
			case "wrist":
			case "hand":
			case "hands":
			case "knee":
			case "lips":
			case "palm":
			case "shoulder":
			case "stomach":
			case "thigh":
			case "tummy":
			target(" "+ tadv +" brushes "+ HIS(TP) +" "+
			"lips along your " + location + ""+
			".", oblist, "", attrs);
			actor("You "+ tadv +" brush your lips "+
			"along", oblist, "'s " + location + ".",);
			all2act(" "+ tadv +" brushes "+ HIS(TP) +" "+
			"lips along", oblist, "'s " + location + ""+
			".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Tkiss whom [where / how]?\n");
			return 0;
		}
		return 1;
	}
	if (strlen(parse_msg))
	{
		write(parse_msg);
		return 1;
	}
	how = parse_adverb_with_space(str, "slowly", 1);
	oblist = parse_this(how[0], "[the] %l", attrs);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tkiss whom [how / where]?\n");
		return 0;
	}
	actor("You kiss", oblist, how[1] + ".");
	all2act(" kisses", oblist, how[1] + ".", how[1], attrs);
	target(" kisses you" + how[1] + ".", oblist, how[1], attrs);
	return 1;
}

int
tclaugh(string str)
{
	object *oblist;
	string *how;
	how = parse_adverb_with_space(str, "temptingly", 0);
	if (!stringp(how[0]))
	{
		write("You laugh" + how[1] + " causing your bosom "+
		"to heave.\n");
		allbb(" laughs" + how[1] + " causing " + HIS(TP) + " "+
		"bosom to heave.", how[1], ACTION_VISUAL | ACTION_MACTIVITY);
		return 1;
	}
	oblist = parse_this(how[0], "[to] / [before] [the] %i",
	ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
	
        if (!sizeof(oblist))
        {
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tclaugh [how] to whom/what?\n");
		return 0;
	}
	actor("You laugh" + how[1] + " at", oblist, " causing your "+
	"bosom to heave.");
	all2actbb(" laughs" + how[1] + " at", oblist, " causing "+
	"" + HIS(TP) + " bosom to heave.", how[1],
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
	target(" laughs" + how[1] + " at you causing " + HIS(TP) + " "+
	"bosom to heave.", oblist, how[1],
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
	return 1;
}

int
tclick(string str)
{
	object *oblist;
	string *how;
	string location, tadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	tadv = tadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ tadv +" licks along the back of your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" lick along the back "+
			"of", oblist, "'s " + location + ".",);
			all2act(" "+ tadv +" licks along the back "+
			"of", oblist, "'s " + location + ".", "", attrs,);
			return 1;
			
			case "abdomen":
			case "arm":
			case "belly":
			case "cheek":
			case "chin":
			case "ear":
			case "wrist":
			case "hand":
			case "hands":
			case "knee":
			case "lips":
			case "palm":
			case "shoulder":
			case "stomach":
			case "thigh":
			case "tummy":
			target(" "+ tadv +" licks along your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" lick along", oblist, "'s "+
			"" + location + ".",);
			all2act(" "+ tadv +" licks along", oblist, "'s "+
			"" + location + ".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Tclick whom [where / how]?\n");
			return 0;
		}
		return 1;
	}
	if (strlen(parse_msg))
	{
		write(parse_msg);
		return 1;
	}
	how = parse_adverb_with_space(str, "playfully", 1);
	oblist = parse_this(how[0], "[the] %l", attrs);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tclick whom [how / where]?\n");
		return 0;
	}
	actor("You lick", oblist, how[1] + ".");
	all2act(" licks", oblist, how[1] + ".", how[1], attrs);
	target(" licks you" + how[1] + ".", oblist, how[1], attrs);
	return 1;
}

int
tclook(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You look like a true temptress as you look "+
		"around.\n");
		allbb(" looks like a true temptress as " + HE(TP) + " "+
		"looks around.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tclook at whom?\n");
		return 0;
	}
	actor("You look toward", oblist, " giving " +
	(sizeof(oblist) > 1 ? "them" : oblist[0]->query_objective()) +
	" your most tempting look.");
	all2actbb(" looks like a true temptress as "+ HE(TP) + " looks "+
	"at", oblist, "");
	target(" looks toward you with promise in "+
	""+ this_player()->query_objective() +" eyes "+
	"of "+ HIS(TP) +" temptress ways.", oblist, "");
	return 1;
}

int
tclove(string str)
{
	int size;
	object *oblist;
	
	oblist = parse_this(str, "[the] %l", ACTION_CONTACT | ACTION_INTIMATE);
	
	if (!(size = sizeof(oblist)))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		return notify_fail("Love whom?\n");
	}
	actor("You entwine your arms around" +
          (size > 1 ? " each of" : ""), oblist, "'s neck and whisper how " +
	  (size > 1 ? "they have" : (oblist[0]->query_pronoun() + " has")) +
	  " captured your temptress heart in love.",);
	  all2act(" entwines " + this_player()->query_possessive() +
            " arms around", oblist, "'s neck and whispers in "+
            (size > 1 ? "their ears." :
                (oblist[0]->query_possessive() + " ear.")),
            "", ACTION_CONTACT | ACTION_INTIMATE,);
            target(" entwines " + this_player()->query_possessive() + " "+
            "arms around your neck and whispers how you've captured "+
            "" + HIS(TP) + " temptress heart in love.",
           oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
           return 1;
}

int
tclust(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You look and feel quite like a lustful temptress " +
		"at the moment.\n");
		allbb(" looks like a lustful little temptress.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Feeling lustful at whom?\n");
		return 0;
	}
	{
		actor("You look toward", oblist, " "+
		"giving " + oblist[0]->query_objective() +  " a "+
		"most lustful look that any temptress should give.");
		all2actbb(" looks like "+ HE(TP) + " is having lustful "+
		"thoughts as "+ HE(TP) + " looks at", oblist, "");
		target(" shows you the lustful desire you provoke "+
		"within "+ HIS(TP) +".", oblist, "");
		return 1;
	}
}

int
tcmove(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You move your sensuous body in a tempting "+
		"fashion.\n");
		allbb(" moves "+ HIS(TP) +" sensuous body in a tempting "+
		"fashion.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Move what?\n");
		return 0;
	}
	actor("You move your sensuous body closer to", oblist, ".", );
	all2actbb(" moves " + HIS(TP) +" sensuous body closer "+
	"to", oblist, ".", );
	target(" moves "+ HIS(TP) + " sensuous body closer to "+
	"yours.", oblist, "");
	return 1;
}

int
tcnibble(string str)
{
	object *oblist;
	string *how;
	string location, tadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	tadv = tadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ tadv +" nibbles along the back of "+
			"your " + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" nibble along the back "+
			"of", oblist, "'s " + location + ".",);
			all2act(" "+ tadv +" nibbles along the back "+
			"of", oblist, "'s " + location + ".", "", attrs,);
			return 1;
			
			case "abdomen":
			case "arm":
			case "belly":
			case "cheek":
			case "chin":
			case "ear":
			case "wrist":
			case "hand":
			case "hands":
			case "knee":
			case "lips":
			case "palm":
			case "shoulder":
			case "stomach":
			case "thigh":
			case "tummy":
			target(" "+ tadv +" nibbles along your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" nibble along", oblist, "'s "+
			"" + location + ".", );
			all2act(" "+ tadv +" nibbles along", oblist, "'s "+
			"" + location + ".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Tcnibble whom [where / how]?\n");
			return 0;
		}
		return 1;
	}
	if (strlen(parse_msg))
	{
		write(parse_msg);
		return 1;
	}
	how = parse_adverb_with_space(str, "gently", 1);
	oblist = parse_this(how[0], "[the] %l", attrs);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tcnibble whom [how / where]?\n");
		return 0;
	}
	actor("You nibble on", oblist, how[1] + ".");
	all2act(" nibbles on", oblist, how[1] + ".", how[1], attrs);
	target(" nibbles on you" + how[1] + ".", oblist, how[1], attrs);
	return 1;
}

int
tcoffer(string str)
{
	object *oblist;
	oblist = parse_this(str, "[before] / [at] / [to] [the] %l");
	if(!sizeof(oblist))
	{
		write("You lean forward, giving everyone a glance "+
		"at your bosom as you offer your bottom to be spanked.\n");
		allbb(" leans forward, giving you a glance "+
		"at "+ HIS(TP) +" bosom as "+
		""+ HE(TP) + " offers "+ HIS(TP) +" bottom to be "+
		"spanked.", "");
		return 1;
	}
	else if (sizeof(oblist) > 1)
	{
		return notify_fail("Offer your bottom to whom?\n");
	}
	actor("You lean forward, giving", oblist, " a glance "+
	"at your bosom as you offer your bottom to be spanked.", );
	all2actbb(" leans forward, giving", oblist," a glance "+
	"at "+ HIS(TP) +" bosom as "+ HE(TP) + " offers "+
	""+ HIS(TP) +" bottom to be spanked.", "");
	target(" leans forward, giving you a glance at "+ HIS(TP) +" "+
	"bosom as "+ HE(TP) + " offers "+ HIS(TP) +" bottom to be "+
	"spanked.", oblist, "");
	return 1;
}

int
tcpout(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You purse your lips in a tempting pout.\n");
		allbb(" purses "+ HIS(TP) + " lips in a "+
		"most tempting pout.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tcpout at whom?\n");
		return 0;
	}
	actor("You purse your lips in a most tempting pout "+
	"at", oblist, ".");
	all2actbb(" purses " + HIS(TP) + " lips in a most "+
	"tempting pout at", oblist, ".");
	target(" purses "+ HIS(TP) + " lips at you in a "+
	"most tempting pout.", oblist, "");
	return 1;
}

int
tcrub(string str)
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
		notify_fail("Tcrub whom?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You cannot rub more than one person at "+
		"once.\n");
		return 0;
	}
	actor("You gently press your fingertips into", oblist, "'s "+
	"shoulders smoothly rubbing down "+
	"" + oblist[0]->query_possessive() + " back. You then slide "+
	"your fingers down some more to " + oblist[0]->query_possessive() +
	" waist rubbing in a sensuously tempting pattern.",);
	all2act(" gently presses " + this_player()->query_possessive() +
	" fingertips into", oblist, "'s shoulders rubbing smoothly " +
	"and gently all the way to " + oblist[0]->query_possessive() +
	" waist in a sensuously tempting pattern.", "",);
	target(" gently presses " + this_player()->query_possessive() +
	" fingertips into your shoulders smoothly rubbing downward, " +
	"back and forth. You breathe in deeply while you relax by " +
	this_player()->query_possessive() +" sensuously tempting "+
	"touch as " + this_player()->query_pronoun() + " finishes "+
	"with tender carressing patterns along your "+
	"waist.", oblist, "", ACTION_INGRATIATORY);
	return 1;
}

int
tcseduce(string str)
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
		notify_fail("Tcseduce whom?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You cannot seduce more than one person "+
		"at once.\n");
		return 0;
	}
	actor("You purr lustful thoughts into", oblist, "'s ear trying "+
	"to seduce " + oblist[0]->query_objective() + " with your "+
	"temptress ways.",);
	all2act(" purrs into", oblist, "'s ear.", "",);
	target(" purrs lustful thoughts into your ear in an attempt to "+
	"seduce you with "+ HIS(TP) +" temptress "+
	"ways.",oblist, "", ACTION_INGRATIATORY);
	return 1;
}

int
tcshimmy(string str)
{
	object *oblist;
	if (!stringp(str))
	{
	write("You shimmy your shoulders making your bosom jiggle "+
	"temptingly.\n");
	allbb(" shimmies "+ HIS(TP) +" shoulders making "+ HIS(TP) +" "+
	"bosom jiggle temptingly.");
	return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tcshimmy at whom?\n");
		return 0;
	}
	actor("You shimmy your shoulders making your bosom jiggle "+
	"temptingly before", oblist, ".");
	all2actbb(" shimmies " + HIS(TP) + " shoulders making "+
	""+ HIS(TP) +" bosom jiggle temptingly before", oblist, ".");
	target(" shimmies "+ HIS(TP) + " shoulders making "+ HIS(TP) +" "+
	"bosom jiggle temptingly before you.", oblist, "");
	return 1;
}

int
tcsigh(string str)
{
	object *oblist;
	string *how;
	how = parse_adverb_with_space(str, "temptingly", 0);
	if (!stringp(how[0]))
	{
		write("You sigh" + how[1] + " causing your bosom "+
		"to heave.\n");
		allbb(" sighs" + how[1] + " causing " + HIS(TP) + " "+
		"bosom to heave.", how[1], ACTION_VISUAL | ACTION_MACTIVITY);
		return 1;
	}
	oblist = parse_this(how[0], "[to] / [before] [the] %i",
	ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
	
        if (!sizeof(oblist))
        {
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tcsigh [how] to whom/what?\n");
		return 0;
	}
	actor("You sigh" + how[1] + " at", oblist, " causing your "+
	"bosom to heave.");
	all2actbb(" sighs" + how[1] + " at", oblist, " causing "+
	"" + HIS(TP) + " bosom to heave.", how[1],
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
	target(" sighs" + how[1] + " at you causing " + HIS(TP) + " "+
	"bosom to heave.", oblist, how[1],
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
	return 1;
}

int
tcsmile(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("Your lips curl up in a tempting smile.\n");
		allbb("'s lips curl up in a tempting smile.", "",);
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tcsmile at whom/what?\n");
		return 0;
	}
	actor("Your lips curl up in a tempting smile at", oblist, ".");
	all2actbb("'s lips curl up in a tempting smile at", oblist, ".",
              "",);
        target("'s lips curl up in a tempting smile at you.", oblist,
           "",);
        return 1;
}

int
tcstraight(string str)
{
	object *oblist;
	string *how;
	how = parse_adverb_with_space(str, "sensually", 0);
	if (!stringp(how[0]))
	{
		write("You" + how[1] + " straighten your clothes.\n");
		allbb("" + how[1] + " straightens " + HIS(TP) +" clothes.", how[1], ACTION_VISUAL | ACTION_MACTIVITY);
		return 1;
	}
	oblist = parse_this(how[0], "[to] / [before] [the] %i",
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
        
        if (!sizeof(oblist))
        {
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tcstraight [how] to whom/what?\n");
		return 0;
	}
	actor("You" + how[1] + " straighten", oblist,"'s clothes.",);
	all2actbb(""+ how[1] + " straightens", oblist, "'s clothes.",
	how[1], ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY, );
        targetbb("" + how[1] + " straightens your clothes.", oblist,
        how[1],ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
        return 1;
}

int
tcstretch(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You temptingly raise each one of your arms "+
		"stretching your sensuous body.\n");
		allbb(" temptingly raises each one of "+ HIS(TP) +" arms "+
		"stretching "+ HIS(TP) +" sensuous body.", "");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tcstretch at whom/what?\n");
		return 0;
	}
	actor("You temptingly raise each one of your arms stretching "+
	"your sensuous body directly in front of", oblist, ".");
	all2actbb(" temptingly raises each one of "+ HIS(TP) +" "+
	"arms stretching "+ HIS(TP) +" sensuous body directly in "+
	"front of", oblist, ".");
        target(" temptingly raises each one of "+ HIS(TP) +" "+
	"arms stretching "+ HIS(TP) +" sensuous body directly in "+
	"front of you.", oblist,);
        return 1;
}

int
tcstroke(string str)
{
	object *oblist;
	string *how;
	string location, tadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	tadv = tadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ tadv +" strokes "+ HIS(TP) +" "+
			"fingertips along the back of your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" stroke your fingertips "+
			"along the back "+
			"of", oblist, "'s " + location + ".", );
			all2act(" "+ tadv +" strokes "+ HIS(TP) +" "+
			"fingertips along the back "+
			"of", oblist, "'s " + location + ".", "", attrs, );
			return 1;
			
			case "abdomen":
			case "arm":
			case "belly":
			case "cheek":
			case "chin":
			case "ear":
			case "wrist":
			case "hand":
			case "hands":
			case "knee":
			case "lips":
			case "palm":
			case "shoulder":
			case "stomach":
			case "thigh":
			case "tummy":
			target(" "+ tadv +" strokes "+ HIS(TP) +" "+
			"fingertips along your " + location + ""+
			".", oblist, "", attrs);
			actor("You "+ tadv +" stroke your fingertips "+
			"along", oblist, "'s " + location + ".",);
			all2act(" "+ tadv +" strokes "+ HIS(TP) +" "+
			"fingertips along", oblist, "'s " + location + ""+
			".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Tcstroke whom [where / how]?\n");
			return 0;
		}
		return 1;
	}
	if (strlen(parse_msg))
	{
		write(parse_msg);
		return 1;
	}
	how = parse_adverb_with_space(str, "playfully", 1);
	oblist = parse_this(how[0], "[the] %l", attrs);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tcstroke whom [how / where]?\n");
		return 0;
	}
	actor("You stroke", oblist, how[1] + " with your fingertips.");
	all2act(" strokes", oblist, how[1] + " with "+ HIS(TP) +" "+
	"fingertips.", how[1], attrs);
	target(" strokes you" + how[1] + " with "+ HIS(TP) +" "+
	"fingertips.", oblist, how[1], attrs);
	return 1;
}

int
tcthink(string str)
{
	object *oblist;
	string *how;
	how = parse_adverb_with_space(str, "temptingly", 0);
	if (!stringp(how[0]))
	{
		write("You run your fingertips" + how[1] + " along your "+
		"chin in a thoughful manner.\n");
		allbb(" runs " + HIS(TP) + " fingertips" + how[1] + " "+
		"along " + HIS(TP) +" chin in a thoughtful "+
		"manner.", how[1], ACTION_VISUAL | ACTION_MACTIVITY);
		return 1;
	}
	oblist = parse_this(how[0], "[to] / [before] [the] %i",
	ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
	
        if (!sizeof(oblist))
        {
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tcthink [how] to whom/what?\n");
		return 0;
	}
	actor("You run your fingertips" + how[1] + " along your chin "+
	"while thoughtfully gazing upon", oblist, ".");
	all2actbb(" runs "+ HIS(TP) +" fingertips" + how[1] + " along "+
	"" + HIS(TP) +" chin while thoughtfully gazing "+
	"upon", oblist,".", how[1],
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
	target(" runs "+ HIS(TP) +" fingertips" + how[1] + " along "+
	"" + HIS(TP) +" chin while thoughtfully gazing at you.", oblist, how[1],
        ACTION_PROXIMATE | ACTION_VISUAL | ACTION_MACTIVITY);
	return 1;
}

int
tctrace(string str)
{
	object *oblist;
	string *how;
	string location, tadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	tadv = tadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ tadv +" traces "+ HIS(TP) +" "+
			"fingertips along the back of your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ tadv +" trace your fingertips "+
			"along the back "+
			"of", oblist, "'s " + location + ".",);
			all2act(" "+ tadv +" traces "+ HIS(TP) +" "+
			"fingertips along the back "+
			"of", oblist, "'s " + location + ".", "", attrs,);
			return 1;
			
			case "abdomen":
			case "arm":
			case "belly":
			case "cheek":
			case "chin":
			case "ear":
			case "wrist":
			case "hand":
			case "hands":
			case "knee":
			case "lips":
			case "palm":
			case "shoulder":
			case "stomach":
			case "thigh":
			case "tummy":
			target(" "+ tadv +" traces "+ HIS(TP) +" "+
			"fingertips along your " + location + ""+
			".", oblist, "", attrs);
			actor("You "+ tadv +" trace your fingertips "+
			"along", oblist, "'s " + location + ".",);
			all2act(" "+ tadv +" traces "+ HIS(TP) +" "+
			"fingertips along", oblist, "'s " + location + ""+
			".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Tctrace whom [where / how]?\n");
			return 0;
		}
		return 1;
	}
	if (strlen(parse_msg))
	{
		write(parse_msg);
		return 1;
	}
	how = parse_adverb_with_space(str, "playfully", 1);
	oblist = parse_this(how[0], "[the] %l", attrs);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Tctrace whom [how / where]?\n");
		return 0;
	}
	actor("You trace", oblist, how[1] + " with your fingertips.");
	all2act(" traces", oblist, how[1] + " with "+ HIS(TP) +" "+
	"fingertips.", how[1], attrs);
	target(" traces you" + how[1] + " with "+ HIS(TP) +" "+
	"fingertips.", oblist, how[1], attrs);
	return 1;
}

int
tcwarn(string str)
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
		notify_fail("Tcwarn who?\n");
		return 0;
	}
	actor("You warn", oblist, " that "+
	"if " + oblist[0]->query_pronoun() + " is "+
	"naughty " + oblist[0]->query_pronoun() + " will be punished.");
	all2act(" warns", oblist, " that "+
	"if " + oblist[0]->query_pronoun() + " is "+
	"naughty " + oblist[0]->query_pronoun() + " will be punished.");
	target(" warns you that if you're naughty you will be "+
	"punished.",oblist, "");
	return 1;
}

int
tcwave(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You wave slowly and sensually purr: Remember "+
		"me always.\n");
		allbb(" waves slowly and sensually purrs: Remember me "+
		"always.");
		return 1;
	}
	
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tcwave at whom?\n");
		return 0;
	}
	actor("You wave in", oblist, "'s direction and sensually purr: "+
	"Remember me always.",);
	all2actbb(" waves slowly in", oblist, "'s direction "+
	"and sensually purrs: Remember me always.",);
	target(" waves slowly in your direction and sensually purrs: "+
	"Remember me always.", oblist, "");
	return 1;
}
int
tcwipe(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You slowly wipe a glistening tear from your "+
		"eye.\n");
		allbb(" slowly wipes a glistening tear from "+
		"" + HIS(TP) + " eye.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tcwipe what?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You cannot wipe more than one eye at "+
		"once.\n");
		return 0;
	}
	actor("You sensuously wipe a tear from", oblist,"'s cheek.", );
	all2actbb(" sensuously wipes away something "+
	"from", oblist, "'s cheek.", "", );
	target(" sensuously wipes away a tear that has fallen on your "+
	"cheek.", oblist,"");
	return 1;
}

public int
tchelp(string str)
{
	string filename, subject, text;
	if (!str)
	{
		subject = "index";
	}
	else if (sscanf(str, "%s", subject) != 1)
	{
		notify_fail("There is no help section for that "+
		"subject.\n");
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

/*  Prototype. */
varargs int say_text(string str, string adverb = "");
public int say_to(string str, function format);

/* tcsay - Say something using an adverb. */
int
tcsay(string str)
{
	string *how;
	if (!strlen(str))
	{
		notify_fail("Syntax: tcsay <adverb> <text>\n");
		return 0;
	}
	how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 0);
	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	{
		notify_fail("Cannot resolve \"" + explode(str, " ")[0] +
		"\" to an adverb.\n");
		return 0;
	}
	if (!strlen(how[0]))
	{
		notify_fail("Syntax: tcsay <adverb> <text>\n");
		return 0;
	}
	return say_text(how[0], how[1]);
}

void
print_say(string adverb, object *oblist, string say_string)
{
	string qcomp;
	qcomp = COMPOSITE_ALL_LIVE(oblist);
	if (this_player()->query_option(OPT_ECHO))
	{
		write("You" + adverb + " purr to " + qcomp + ": "+
		"" + say_string + "\n");
	}
	else
	{
		write("Ok.\n");
	}
	say(QCTNAME(this_player()) + adverb + " purrs to "+
	"" + QCOMPLIVE + ": " + say_string + ""+
	"\n", (oblist + ({ this_player() }) ));
	oblist->catch_msg(QCTNAME(this_player()) + adverb + " purrs to "+
	"you: " + say_string + "\n");
}

/* say_to */
public int
say_to(string str, function format)
{
	object *oblist;
	string qcomp;
	string say_string;
	
	say_string = str;
	/* Whisper to all people. */
	if (wildmatch("all *", str))
	{
		str = extract(str, 4);
		oblist = FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
	}
	/* Whisper to my team. */
	else if (wildmatch("team *", str))
	{
		str = extract(str, 5);
		oblist = this_player()->query_team_others() &
		all_inventory(environment(this_player()));
	}
	/* Find out who we talk to. */
	else if (!parse_command(lower_case(str), environment(this_player()),
	"[to] [the] %i %s", oblist, str))
	{
		notify_fail("Say [how] what to whom/what?\n");
		return 0;
	}
	else
	{
		oblist = NORMAL_ACCESS(oblist, 0, 0) - ({ this_player() });
	}
	if (!sizeof(oblist) ||
	!strlen(str))
	{
		return 0;
	}
	say_string = extract(say_string, -(strlen(str)));
	this_player()->set_say_string(say_string);
	format(oblist, say_string);
	return 1;
}

/* say_text */
varargs int
say_text(string str, string adverb = "")
{
	mixed tmp;
	if (!strlen(str))
	{
		notify_fail("What do you wish to say?\n");
		return 0;
	}
	if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
	{
		write(stringp(tmp) ? tmp : "You are gagged and "+
		"cannot speak.\n");
		return 1;
	}
	
	if (!this_player()->query_wiz_level() &&
	wildmatch("*       *", str))
	{
		str = implode((explode(str, " ") - ({ "" }) ), " ");
	}
	if (wildmatch("to *", str))
	{
		if (say_to(extract(str, 3), &print_say(adverb)))
		{
			return 1;
		}
	}
	this_player()->set_say_string(str);
	if (this_player()->query_option(OPT_ECHO))
	{
		write("You" + adverb + " purr: " + str + "\n");
	}
	else
	{
		write("Ok.\n");
	}
	say(QCTNAME(this_player()) + adverb + " purrs: " + str + "\n");
	return 1;
}

/* tcwhisper - whisper something to someone. */
void
print_tcwhisper(string adverb, object *oblist, string str)
{
    object *wizards;
    
    if (this_player()->query_option(OPT_ECHO))
        actor("You" + adverb + " purr in", oblist, "'s ear: " + str);
    else
        write("Ok.\n");
    all2act(" purrs something to", oblist);
    
    /* Give the message to all wizards, too. */
    wizards = FILTER_IS_WIZARD(all_inventory(environment(this_player()))) -
        oblist - ({ this_player() });
    wizards->catch_tell("As wizard, you hear " +
        this_player()->query_objective() + " purr: " + str + "\n");

    target("" + adverb + " purrs in your ear: " + str, oblist);
    oblist->catch_whisper(str);    
}

int
tcwhisper(string str)
{
    mixed tmp;
    string *how;

    if (!stringp(str))
    {
        notify_fail("Tcwhisper [to] <whom> <what>?\n");
        return 0;
    }

    
    if (tmp = this_player()->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
        write(stringp(tmp) ? tmp : "You are gagged and cannot tcwhisper.\n");
        return 1;
    }
    
    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 0);
    if (strlen(how[0]) && how[1] != NO_DEFAULT_ADVERB_WITH_SPACE)
    {
        str = how[0];
    }
    else
    {
        how[1] = NO_ADVERB;
    }


    
    if (strlen(str))
    {
        if (wildmatch("to *", str))
            str = extract(str, 3);
        
        if (say_to(str, &print_tcwhisper(how[1])))
        {
            return 1;
        }
    }
    
    notify_fail("Tcwhisper [to] <whom> <what>?\n");
    return 0;
}
