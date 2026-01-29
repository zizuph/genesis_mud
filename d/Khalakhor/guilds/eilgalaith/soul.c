/**********************************************************************
 * - soul.c                                                         - *
 * - Eil-Galaith, elven race guild soul                             - *
 * - Original code Created by Damaris with the help of Lucius, Tomas- *
 * - And Rhyn.                                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 **********************************************************************/
#pragma no_clone
#pragma no_inherit
#pragma strict_types

#include "guild.h"
inherit "/cmd/std/command_driver"; 
inherit "/lib/commands";

#include "guild.h"
#include <adverbs.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <tasks.h>

#define SUBLOC_SOULEXTRADESC ("_soul_cmd_extra")
#define SOULDESC(x)          (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "eilgalaith"; }

public mapping
query_cmdlist()
{
	return ([
	"eg"         : "eg",
        "egaccept"   : "egaccept",
        "egbeam"     : "egbeam",
        "egblush"    : "egblush",
        "egbow"      : "egbow",
        "egbow2"     : "egbow2",
        "egcurtsey"  : "egcurtsey",
        "egcurtsey2" : "egcurtsey2",
        "egdance"    : "egdance",
        "egdecline"  : "egdecline",
        "egdistrust" : "egdistrust",
        "egdroop"    : "egdroop",
        "egflash"    : "egflash",
        "egfrown"    : "egfrown",
        "eggiggle"   : "eggiggle",
        "egglare"    : "egglare",
        "egglow"     : "egglow",
        "eggreet"    : "eggreet",
        "eggrin"     : "eggrin",
        "eghelp"     : "eghelp",
        "eghome"     : "eghome",
        "eghum"      : "eghum",
        "egkiss"     : "egkiss",
        "eglaugh"    : "eglaugh",
        "eglist"     : "egwho",
        "eglisten"   : "eglisten",
        "eglook"     : "eglook",
        "egnod"      : "egnod",
        "egpray"     : "egpray",
        "egpresent"  : "egpresent",
        "egsay"      : "egsay",
        "egshow"     : "egshow",
        "egsing1"    : "egsing1",
        "egsing2"    : "egsing2",
        "egsmile"    : "egsmile",
        "egstand"    : "egstand",
        "egstretch"  : "egstretch",
        "egtear"     : "egtear",
        "egthink"    : "egthink",
        "egtrace"    : "egtrace",
        "egtrust"    : "egtrust",
        "egtug"      : "egtug",
        "egwarcry"   : "egwarcry",
        "egwho"      : "egwho",
        ]);
}
public void
using_soul(object live)
{
	if (!objectp(live))
	return;
	
	live->add_subloc(GUILD_SUBLOC, this_object());
}

public string
show_subloc(string subloc, object on, object who)
{
	string str, house, color;
	
	if (subloc != GUILD_SUBLOC)
	return "";
	
	if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";
	
	if (house = SERVER->query_house(on->query_real_name()))
	{
		color =  COMPOSITE_WORDS(HOUSES[house][HOUSE_CLRS]);
	}
	if (on != who)
	{
		str = capitalize(on->query_pronoun()) + " has the " +
		"distinguished mark of the mystic vine of the " +
		GUILD_NAME + ".\n";
		
		if (color)
		{
			str += capitalize(on->query_pronoun()) + " "+
			"wears the " + color + " colours from the elven "+
			"" + (IS_MEMBER(who) ? "House of " + house : ""+
			"House") + ".\n";
		}
	}
	else
	{
		int half = (on->query_race_name() == "half-elf");
		str = "You have the distinguished mark of the mystic "+
		"vine that runs from the " + (half ? "softly " : "") + ""+
		"pointed tips of your ears to join at the base of "+
		"your neck.\n";
		if (color)
		{
			str += "You are wearing the " + color + " "+
			"colours from the elven House of " + house + ".\n";
		}
	}
	return str;
}


/**********************************************************************
 * - Emotions begin here. When adding and updating please list them - *
 * - Alphabetically.                                                - *
 **********************************************************************/

int
egaccept(string str)
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
	actor("You embrace both of", oblist, " forearms in the "+
	"ancient elven sign of acceptance.");
	all2act(" embraces both of", oblist, " forearms in the "+
	"ancient elven sign of acceptance.");
	target(" embraces both of your forearms in the ancient "+
	"elven sign of acceptance.", oblist,"");
	return 1;
}

int
egbeam(string str)
{
	object *oblist;
	
	if (!stringp(str))
	{
		write("Your elven face lights up as you beam with "+
		"pleasure.\n");
		allbb("'s elven features light up as "+
		""+ this_player()->query_pronoun() +" beams with "+
		"pleasure.","",);
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Beam at whom/what?\n");
		return 0;
	}
	actor("Your elven face lights up as you beam with pleasure "+
	"at", oblist);
	all2act("'s elven features light up as "+
	""+ this_player()->query_pronoun() +" beams with pleasure "+
	"at", oblist, ".", "",);
	target("'s elven features light up as "+
	this_player()->query_pronoun() + " beams with pleasure at "+
	"you.", oblist,"",);
	return 1;
}

int
egblush(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("Your ears glow crimson on the pointed tips as "+
		"you blush.\n");
		allbb("'s ears glow crimson on the pointed tips as "+
		"" + HE(TP) + " blushes.", "",);
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	
	if (!sizeof(oblist))
	{
		notify_fail("Blush at whom/what?\n");
		return 0;
	}
	actor("Your ears glow crimson on the pointed tips as you blush "+
	"at",oblist,".");
	targetbb("'s ears glow crimson on the pointed tips as "+
	"" + HE(TP) + " blushes at you.", oblist, "",);
	all2actbb("'s ears glow crimson on the pointed tips as "+
	"" + HE(TP) + " blushes at",oblist,".",);
	return 1;
}

int
egbow(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		{
			write("You bow with a flourish of elven "+
			"elegance and grace.\n");
			allbb(" bows with a flourish of elven elegance "+
			"and grace.");
			return 1;
		}
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Bow at whom/what?\n");
		return 0;
	}
	{
		actor("You bow before",oblist," with a flourish of "+
		"elven elegance and grace.");
		targetbb(" bows with a flourish of elven elegance "+
		"and grace before you.", oblist);
		all2actbb(" bows before",oblist," in a flourish of "+
		"elven elegance and grace.");
		return 1;
	}
}

int
egbow2(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You bow grandly outlining your ancient elven "+
		"heritage.\n");
		allbb(" bows grandly outlining " + HIS(TP) + " "+
		"ancient elven heritage.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Bow at whom/what?\n");
		return 0;
	}
	actor("You bow grandly before", oblist," outlining your "+
	"ancient elven heritage.");
	targetbb(" bows grandly before you outlining " +HIS(TP)+ ""+
	"ancient elven heritage.", oblist);
	all2actbb(" bows grandly before",oblist," outlining "+
	"" +HIS(TP)+ " ancient elven heritage.");
	return 1;
}

int
egcurtsey(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You curtsey with timeless grace and elegance.\n");
		allbb(" curtseys with timeless grace and elegance.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Curtsey at whom/what?\n");
		return 0;
	}
	actor("You curtsey before",oblist," with timeless grace "+
	"and elegance.");
	targetbb(" curtseys before you with timeless grace and elegance.", oblist);
	all2actbb(" curtseys before",oblist," with timeless grace "+
	"and elegance.");
	return 1;
}

int
egcurtsey2(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You curtsey gracefully outlining your ancient "+
		"elven heritage.\n");
		allbb(" curtseys gracefully outlining " + HIS(TP) + ""+
		"ancient elven heritage.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Curtsey at whom/what?\n");
		return 0;
	}
	actor("You curtsey gracefully before",oblist," outlining your "+
	"ancient elven heritage.");
	targetbb(" curtseys gracefully before you outlining "+
	"" +HIS(TP) + " ancient elven heritage.", oblist);
	all2actbb(" curtseys gracefully before", oblist," outlining "+
	"" +HIS(TP)+ " ancient elven heritage.");
	return 1;
}

int
egdance(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You dance around joyously displaying elven poise "+
		"and grace.\n");
		allbb(" dances around joyously displaying elven poise "+
		"and grace.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Dance with who?\n");
		return 0;
	}
	actor("You pull",oblist," into an enchanting embrace and "+
	"dance joyously with " + oblist[0]->query_objective() + " "+
	"while displaying elven poise and grace.");
	all2act(" pulls",oblist," into an enchanting embrace and "+
	"dances joyously with " + oblist[0]->query_objective() + " "+
	"while displaying elven poise and grace.");
	target(" pulls you into an enchanting embrace and dances "+
	"joyously with you while displaying elven poise and "+
	"grace.", oblist);
	return 1;
}

int
egdecline(string str)
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
	actor("You decline", oblist, "'s offer with a flourish of "+
	"elven grace.",);
	all2act(" declines", oblist, "'s offer with a flourish of "+
	"elven grace.");
	target(" declines your offer with a flourish of elven grace.",
	oblist, "",ACTION_INGRATIATORY);
	return 1;
}

int
egdistrust(string str)
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
		notify_fail("Distrust whom?\n");
		return 0;
	}
	if (environment(this_player())->query_prop(ROOM_I_INSIDE))
	{
		/* Inside a room */
		actor("You touch the ground with your fingertips forming "+
		"an ancient symbol, saying to", oblist,", 'to-ato "+
		"mi anlio', meaning, 'I trust you no more'.");
		all2act(" touches the ground with " + HIS(TP) + ""+
		"fingertips forming an ancient symbol, saying "+
		"to", oblist,", 'to-ato mi anlio', meaning, "+
		"'I trust you no more'.");
		target(" touches the ground with " + HIS(TP) + " "+
		"fingertips forming an ancient symbol, saying to you,"+
		"'to-ato mi anlio', meaning, 'I trust you "+
		"no more'.", oblist, "");
	}
	else
	{
		/* Outside */
		actor("You bend down scooping up a handful of "+
		"soil and in the ancient gesture of distrust you toss "+
		"it at", oblist, "'s feet saying, 'to-ato mi anlio', "+
		"meaning, 'I trust you no more'.",);
		all2act(" bends down scooping up a handful of soil, "+
		"in the ancient gesture of distrust "+
		this_player()->query_pronoun() + " tosses it "+
		"at", oblist, "'s feet saying, 'to-ato mi anlio', "+
		"meaning, 'I trust you no more'.", "",);
		target(" bends down scooping up a handful of soil, "+
		"in the ancient gesture of distrust "+ 
		this_player()->query_pronoun() + " tosses it at your "+
		"feet saying, 'to-ato mi anlio', meaning, 'I trust you "+
		"no more'.",
		oblist, "");
	}
	return 1;
}

int
egdroop()
{
	write("Your pointed ears droop with sheer exhaustion.\n");
	allbb("'s pointed ears droop with sheer exhaustion.", "",);
	return 1;
}

int
egflash(string str)
{
	object *oblist;
	
	if (this_player()->query_alignment() <= GUILD_MIN_ALIGN)
	return NF("This mystic vine does not flow well within you.\n");
	
	if (!stringp(str))
	{
		write("Your eyes flash angrily and you feel the power "+
		"of the mystic vine pulsating.\n");
		allbb("'s eyes flash angrily and the mark of the mystic "+
		"vine on " + HIS(TP) + " neck pulses red.", "",);
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Flash at whom/what?\n");
		return 0;
	}
	actor("Your eyes flash and you feel the power of the mystic "+
	"vine as your anger rises towards", oblist,".");
	targetbb("'s eyes flash angrily and the mark of the mystic vine "+
	"on " + HIS(TP) + " neck pulses red as "+
	""+ this_player()->query_pronoun() + " regards "+
	"you.",oblist, "",);
	all2actbb("'s eyes flash angrily and the mark of the mystic "+
	"vine on " + HIS(TP) + " neck pulses red as "+
	""+ this_player()->query_pronoun() + " regards"+
	"", oblist, 0, "",);
	return 1;
}

int
egfrown(string str)
{
	object *oblist;
	string *how;
	
	how = parse_adverb_with_space(str, "in deep displeasure", 0);
	if (!stringp(how[0]))
	{
		SOULDESC("frowning" + how[1]);
		write("Your elven features frown" + how[1] + ".\n");
		allbb("'s elven features "+
		"frown" + how[1] + ".", how[1],);
		return 1;
	}
	oblist = parse_this(how[0], "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Frown [how] at whom/what?\n");
		return 0;
	}
	SOULDESC("frowning" + how[1]);
	actor("Your elven features frown" + how[1] + " at", oblist);
	all2actbb("'s elven features "+
	"frown" + how[1] + " at", oblist, 0, how[1],);
	targetbb("'s elven features "+
	"frown" + how[1] + " at you.", oblist, how[1],);
	return 1;
}

int
eggiggle(string str)
{
	object *oblist;
	string *how;
	how = parse_adverb_with_space(str, "adorably", 0);
	if (!stringp(how[0]))
	{
		SOULDESC("giggling" + how[1]);
		write("You giggle" + how[1] + " with elven amusement "+
		"dancing in your eyes.\n");
		allbb(" giggles" + how[1] + " with elven amusement "+
		"dancing in " + HIS(TP) + " eyes.", how[1]);
		return 1;
	}
	oblist = parse_this(how[0], "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Giggle [how] at whom/what?\n");
		return 0;
	}
	SOULDESC("giggling" + how[1]);
	actor("You giggle" + how[1] + " with elven amusement dancing "+
	"in your eyes at", oblist);
	all2actbb(" giggles" + how[1] + " with elven amusement dancing "+
	"in "+ HIS(TP) +" eyes at", oblist, 0, how[1]);
	targetbb(" giggles" + how[1] + " with elven amusement dancing "+
	"in "+ HIS(TP) +" eyes at you.", oblist, how[1]);
	return 1;
}

int
egglare(string str)
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
	actor("The tips of your pointed ears begin to quiver in rage as "+
	"you glare at", oblist, ".");
	all2act(" glares at", oblist, " while the tips of "+ 
	this_player()->query_objective() + " pointed ears quiver in "+
	"rage.", "", ACTION_INGRATIATORY);
	target(" glares at you while the tips of "+
	this_player()->query_objective() + " pointed ears quiver in "+
	"rage.", oblist, "", ACTION_INGRATIATORY);
	return 1;
}

int
egglow()
{
	if (this_player()->query_alignment() <= GUILD_MIN_ALIGN)
	return NF("The mystic vine fails to glow.\n");
	write("The mark of the mystic vine begins to glow softly "+
	"with your pleasure.\n");
	allbb("'s mark of the mystic vine begins to glow softly "+
	"with "+ HIS(TP) +" pleasure.", "",);
	return 1;
}

int
eggreet(string str)
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
	actor("You take", oblist, "'s hand into yours in an ancient "+
	"elven tradition of greeting saying the ancient "+
	"words, 'Hijio'.",);
	all2act(" takes", oblist, "'s hand into "+HIS(TP) +" own in an "+
	"ancient elven tradition of greeting saying the ancient "+
	"words, 'Hijio'.", "",);
	target(" takes your hand into "+HIS(TP)+" own and greets you "+
	"with the ancient words, 'Hijio'.",oblist, "");
	return 1;
}

int
eggrin(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You grin in that adorable elven fashion "+
		"with your eyes sparkling.\n");
		allbb("'s elven eyes sparkle as " + HE(TP) + " grins in "+
		"an adorable fashion.", "",);
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Grin at whom/what?\n");
		return 0;
	}
	actor("You grin in that adorable elven fashion at",oblist," "+
	"with your eyes sparkling.");
	targetbb(" grins in an adorable elven fashion at you with "+
	""+ HIS(TP) +" eyes sparkling.", oblist, "");
	all2actbb(" grins in an adorable elven fashion at", oblist, " "+
	"with "+ HIS(TP) +" eyes sparkling.");
	return 1;
}

public int
eghelp(string str)
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

int
eghome()
{
	write("You get a distant look in your elven eyes.\n");
	allbb(" gets a distant look in " +HIS(TP) + " elven eyes.");
	return 1;

}

int
eghum()
{
	write("You hum an ancient elven melody that recalls the age "+
	"of innocence.\n");
	allbb(" hums an ancient elven melody that recalls the age "+
	"of innocence.");
	return 1;
}

int
egkiss(string str)
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
		notify_fail("Kiss whom?\n");
		return 0;
	}
	actor("You press your graceful lips "+
	"to" + (sizeof(oblist) > 1 ? " each of" : ""), oblist,
	"'s in a lingering elven kiss.",);
	all2act(" presses "+ HIS(TP) +" graceful lips to", oblist, "'s "+
	"in a lingering elven kiss.", "", ACTION_CONTACT | ACTION_INTIMATE,);
	target(" presses "+ HIS(TP) +" graceful lips to yours in a "+
	"lingering elven kiss.", oblist, "", ACTION_CONTACT | ACTION_INTIMATE,);
	return 1;
}

int
eglaugh(string str)
{
	object *oblist;
	string *how;
	how = parse_adverb_with_space(str, "delightfully", 0);
	
	if (!stringp(how[0]))
	{
		SOULDESC("laughing" + how[1]);
		write("You laugh" + how[1] + " with a mysterious glint "+
		"in your elven eyes.\n");
		allbb(" laughs" + how[1] + " with a mysterious glint in "+
		""+ HIS(TP) +" elven eyes.", how[1]);
		return 1;
	}
	oblist = parse_this(how[0], "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Laugh [how] at whom/what?\n");
		return 0;
	}
	SOULDESC("laughing" + how[1]);
	actor("You laugh" + how[1] + " with a mysterious glint in "+
	"your elven eyes at", oblist);
	all2actbb(" laughs" + how[1] + " with a mysterious glint in "+
	""+ HIS(TP) +" elven eyes at", oblist, 0, how[1]);
	targetbb(" laughs" + how[1] + " with a mysterious glint in "+
	""+ HIS(TP) +" elven eyes at you.", oblist, how[1]);
	return 1;
}

int
eglisten(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("Your pointed ears instinctively move and "+
		"you tilt your head toward a distant sound.\n");
		allbb("'s pointed ears move suddenly and " + HE(TP) + " "+
		"tilts " + HIS(TP) + " head as if listening to "+
		"something.",);
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Listen to whom/what?\n");
		return 0;
	}
	actor("Your pointed ears instinctively move toward",oblist," "+
	"as you listen closely.");
	targetbb("'s pointed ears instinctively move toward you "+
	"as " + HE(TP) + " listens closely.", oblist,);
	all2actbb("'s pointed ears instinctively move toward", oblist," "+
	"as " + HE(TP) + " listens closely.", "",);
	return 1;
}

int
eglook(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You look around with a measure of concern etched in your elven features.\n");
		allbb(" looks around with a measure of concern etched "+
		"in " + HIS(TP) + " elven features.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Look at whom/what?\n");
		return 0;
	}
	actor("You look at",oblist," with a measure of concern etched "+
	"in your elven features.");
	targetbb(" looks at you with a measure of concern etched "+
	"in " + HIS(TP) + " elven features.", oblist);
	all2actbb(" looks at",oblist," with a measure of concern etched "+
	"in " + HIS(TP) + " elven features.");
	return 1;
}

int
egnod(string str)
{
	object *oblist;
	string *how;
	
	how = parse_adverb_with_space(str, "thoughtfully", 0);
	if (!stringp(how[0]))
	{
		write("You tilt your head for a moment then "+
		"nod" + how[1] + ".\n");
		allbb(" tilts " + HIS(TP) + " head a moment then "+
		"nods" + how[1] + ".", how[1]);
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
	actor("You tilt your head and nod" + how[1] + " at", oblist);
	all2actbb(" tilts " + HIS(TP) + " head and "+
	"nods" + how[1] + " at", oblist, 0, how[1]);
	targetbb(" tilts " + HIS(TP) + " head and "+
	"nods" + how[1] + " at you.", oblist, how[1]);
	return 1;
}

int
egpray(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You touch the mystic vine at your temple "+
		"then reach outwards in the air whispering an "+
		"ancient elven prayer for strength, courage and "+
		"knowledge.\n");
		allbb(" touches the mystic vine on " + HIS(TP) + " "+
		"temple then reaches outward in the air whispering "+
		"an ancient elven prayer for strength, courage and "+
		"knowledge.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Pray for whom/what?\n");
		return 0;
	}
	actor("You touch the mystic vine at your temple then reach "+
	"outwards toward", oblist," whispering an ancient "+
	"elven prayer for strength, courage and knowledge.");
	targetbb(" touches the mystic vine on " + HIS(TP) + " temple "+
	"then reaches towards you whispering an ancient "+
	"elven prayer for strength, courage and knowledge.", oblist);
	all2actbb(" touches the mystic vine on " + HIS(TP) + " temple "+
	"then reaches outward towards ",oblist," whispering an "+
	"ancient elven prayer for strength, courage and knowledge.");
	return 1;
}

int
egpresent(string str)
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
	actor("You present yourself to", oblist, " in the ancient elven "+
	"tradition of Eil-Galaith by placing your hand over your "+
	"heart, then gesturing to " + (sizeof(oblist) > 1 ? "them" : 
	oblist[0]->query_possessive()) + " heart with your other hand.");
	all2act(" presents "+ this_player()->query_objective() +"self "+
	"to", oblist, " in an ancient elven tradition of "+
	"Eil-Galaith.", "", ACTION_INGRATIATORY);
	target(" presents "+ this_player()->query_objective() +
	"self to you in the ancient elven tradition of Eil-Galaith " +
	"by placing "+ this_player()->query_possessive() +" hand "+
	"over "+ this_player()->query_possessive() +" heart then "+
	"gesturing to you with "+ this_player()->query_possessive() +" "+
	"other hand.", oblist, "", ACTION_INGRATIATORY);
	return 1;
}

int
egsay(string str)
{
	object *oblist;
	int i;
	if (!strlen(str))
	{
		notify_fail("You wish to say what in the tongue "+
		"of Eil-Galaith?\n");
		return 0;
	}
	oblist = FILTER_PLAYERS(all_inventory(environment(this_player())));
	oblist -= ({ this_player() });
	write("Through the power of the mystic vine you speak in "+
	"an ancient tongue: " + str + "\n");
	
	for (i = 0; i < sizeof(oblist); i++)
	{
		if ((IS_MEMBER(oblist[i])) || oblist[i]->query_wiz_level())
		{
			oblist[i]->catch_tell(this_player()->query_The_name(oblist[i]) +
			" speaks in an ancient tongue "+
			"saying: " + str + "\n");
		}
		else
		{
			oblist[i]->catch_tell(this_player()->query_The_name(oblist[i]) + " "+
			"speaks in an ancient tongue, that you do not "+
			"understand.\n");
		}
	}
	return 1;
}

int
egshow(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You show the distinguished mark of mystic "+
		"vine that runs from the "+
		"" + (this_player()->query_race_name() == "half-elf" ?
		"softly " : "") + "pointed tips of your ears to "+
		"join at the base of your neck.\n");
		allbb(" shows you the distinguished mark of the "+
		"mystic vine that runs from the "+
		"" + (this_player()->query_race_name() == "half-elf" ?
		"softly " : "") + "pointed tips of " +
		this_player()->query_possessive() + " ears to join "+
		"at the base of " + HIS(TP) + " neck.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("egshow to whom/what?\n");
		return 0;
	}
	actor("You show",oblist," the distinguished mark of mystic "+
	"vine that runs from the "+
	"" + (this_player()->query_race_name() == "half-elf" ?
	"softly " : "") + "pointed tips of your ears to join at the base "+
	"of your neck.");
	targetbb(" shows you the distinguished mark of the mystic vine "+
	"that runs from the "+
	"" + (this_player()->query_race_name() == "half-elf" ?
	"softly " : "") + "pointed tips of " +
	this_player()->query_possessive() + " ears to join at the " +
	"base of " + this_player()->query_possessive() + " neck.", oblist);
	all2actbb(" shows",oblist," the distinguished mark of the mystic "+
	"vine that runs from the "+
	"" + (this_player()->query_race_name() == "half-elf" ?
	"softly " : "") + "pointed tips of " +
	this_player()->query_possessive() + " ears to join at the " +
	"base of " + this_player()->query_possessive() + " neck.");
	return 1;
}

int
egsing1()
{
	write("You sing an ancient elven song of life and peace.\n");
	allbb(" sings an ancient elven song of life and peace.");
	return 1;
}

int
egsing2()
{
	write("You sing an ancient elven song of harmony of ages.\n");
	allbb(" sings an ancient elven song of harmony of ages.");
	return 1;
}

int
egsmile(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("Your lips curl in a mysterious smile.\n");
		allbb("'s elven lips curl in a mysterious smile.", "", );
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Smile at whom/what?\n");
		return 0;
	}
	actor("You smile at",oblist," with a glint of elven "+
	"mystery in your eyes.");
	targetbb(" smiles at you with a glint of elven "+
	"mystery in "+ HIS(TP)+" eyes.", oblist);
	all2actbb(" smiles at",oblist," with a glint of elven "+
	"mystery in "+ HIS(TP)+" eyes.");
	return 1;
}

int
egstand()
{
	write("You stand still radiating a silent grace.\n");
	allbb(" stands radiating a silent grace.");
	return 1;
}

int
egstretch()
{
	write("You stretch your elven body showing off your "+
	"subtle grace.\n");
	allbb(" stretches "+ this_player()->query_possessive() +" "+
	"elven body in a most graceful manner.");
	return 1;
}

int
egtear(string str)
{
	str = check_adverb_with_space(str, "silently");
	if (str == NO_ADVERB_WITH_SPACE)
	{
		notify_fail("Cry how?\n");
		return 0;
	}
	SOULDESC("crying" + str);
	write("A single elven tear falls down your cheek" + str + ".\n");
	allbb(" looks up and a single elven tear falls "+
	"down "+ this_player()->query_possessive() + " "+
	"cheek" + str + ".", str, ACTION_MACTIVITY | ACTION_VISUAL);
	return 1;
}

int
egthink()
{
	write("You run your graceful fingertips along your elven chin in "+
	"a thoughtful manner.\n");
	allbb(" runs "+ HIS(TP) +" graceful fingertips along "+
	""+ HIS(TP) + " elven chin in a thoughtful manner.", "");
	return 1;
}

int
egtrace(string str)
{
	object *oblist;
	string *how;
	string location;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] 'forearm' / " +
        "'cheek' / 'chin' / 'neck' / 'abdomen' / 'belly' / 'tummy' / " +
        "'ear' / 'thigh' / 'knee' / 'lips'", attrs);
        if (sizeof(oblist))
        {
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" gently traces " + HIS(TP) + " "+
			"elven fingertips along the side of "+
			"your " + location + ".", oblist, "", attrs);
			actor("You gently trace your elven fingertips "+
			"along the side of", oblist, "'s " + location + ".",);
			all2act(" gently traces " + HIS(TP) + " "+
			"fingertips along the side "+
			"of", oblist, "'s " + location + ".", "", attrs,);
			return 1;
			
			case "chin":
			case "cheek":
			case "abdomen":
			case "belly":
			case "tummy":
			case "ear":
			case "thigh":
			case "knee":
			case "ear":
			case "lips":
			target(" gently traces " + HIS(TP) + " "+
			"elven fingertips along your "+
			"" + location + ".", oblist, "", attrs);
			actor("You gently trace your elven fingertips "+
			"along", oblist, "'s " + location + ".", );
			all2act(" gently traces " + HIS(TP) + " "+
			"elven fingertips along"+
			"", oblist, "'s " + location + ".", "", attrs, );
			return 1;
			default:
			notify_fail("Trace whom [where / how]? "+
			"Rather... this should not happen. Please make "+
			"a sysbugreport about this.\n");
			return 0;
		}
		return 1;
	}
	if (strlen(parse_msg))
	{
		write(parse_msg);
		return 1;
	}
	how = parse_adverb_with_space(str, "softly", 1);
	oblist = parse_this(how[0], "[the] %l", attrs);
	if (sizeof(oblist))
	{
		/* You need something here if oblist matches. */
	}
	if (strlen(parse_msg))
	{
		write(parse_msg);
		return 1;
	}
	notify_fail("Trace whom [how / where]?\n");
	return 0;
}

int
egtrust(string str)
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
		notify_fail("Trust who?\n");
		return 0;
	}
	actor("You touch your mark of the mystic vine with two fingers "+
	"then place them on", oblist, "'s temple signifying in the ancient "+
	"elven tradition that you place your trust in "+
	(sizeof(oblist) > 1 ? "them" : oblist[0]->query_objective()) + ".", );
	all2act(" touches the mark of the mystic vine "+
	"on "+ this_player()->query_possessive() +" pointed ear "+
	"then touches", oblist, "'s temple signifying in the ancient "+
	"elven tradition that "+ 
	this_player()->query_pronoun() +" places "+ 
	this_player()->query_possessive() +" trust in "+
	(sizeof(oblist) > 1 ? "them" : oblist[0]->query_objective()) + ".",
        "", ACTION_INGRATIATORY,);
        target(" touches the mark of the mystic vine on "+
        this_player()->query_possessive() +" pointed ear then touches "+
        "your temple signifying in the ancient elven tradition that "+ 
        this_player()->query_pronoun() +" places "+ 
        this_player()->query_possessive() +" trust in you.",
        oblist, "", ACTION_INGRATIATORY);
        return 1;
}

int
egtug(string str)
{
	object *oblist;
	string *how;
	how = parse_adverb_with_space(str, "adorably", 0);
	if (!stringp(how[0]))
	{
		write("You tug" + how[1] + " on your pointed ears.\n");
		allbb(" tugs" + how[1] + " on " + HIS(TP) + " pointed "+
		"ears.", how[1]);
		return 1;
	}
	oblist = parse_this(how[0], "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Tug [how] on whose ears?\n");
		return 0;
	}
	actor("You tug" + how[1] + " on", oblist, "'s ears.",);
	all2act(" tugs" + how[1] + " on", oblist, "'s ears.", how[1],
        ACTION_CONTACT | ACTION_INTIMATE | ACTION_LACTIVITY, );
        target(" tugs" + how[1] + " on your ears.", oblist, how[1],
        ACTION_CONTACT | ACTION_INTIMATE | ACTION_LACTIVITY);
        return 1;
}


int
egwarcry(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You shout the ancient elven words of attack and "+
		"your mark of the mystic vine glows crimson with your "+
		"fury.\n");
		allbb(" shouts some ancient elven words of attack and "+
		""+ HIS(TP) + " mark of the mystic vine glows crimson "+
		"with " + HIS(TP) + " fury.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("egwarcry at whom/what?\n");
		return 0;
	}
	actor("You shout the ancient elven words of attack at",oblist," "+
	"and your mark of the mystic vine glows crimson with your fury.");
	targetbb(" shouts some ancient elven words of attack at you, and "+
	"" + HIS(TP) + " mark of the mystic vine glows crimson with "+
	"" + HIS(TP) + " fury.", oblist);
	all2actbb(" shouts some ancient elven words of attack "+
	"at", oblist," and " + HIS(TP) + " mark of the mystic vine glows "+
	"crimson with " + HIS(TP) + " fury.");
	return 1;
}

int
eg(string str)
{
	string *words;
	if (!strlen(str))
	{
		notify_fail("Perform which Eil-Galaith command? "+
		"Syntax: eg <command> [<arguments>]\n");
		return 0;
	}
	words = explode(str, " ");
	if (!stringp(cmdlist[words[0]]))
	{
		notify_fail("The command " + words[0] +
		" is not a known Eil-Galaith command.\n");
		return 0;
	}
	str = ((sizeof(words) > 1) ? implode(words[1..], " ") : "");
	return call_other(this_object(), cmdlist[words[0]], str);
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
		if (SECURITY->query_guild_is_master("eilgalaith", who->query_real_name()))
		return who->query_name();
		else
		return 0;
	}
	else
	return who->query_name() + " " + who->query_guild_title_race();
}

int
egwho(string str)
{
	string *titles;
	write("You touch the mystic vine at your temple and it "+
	"begins to flow through you.\n");
	titles = map(users() - ({ this_player() }), get_title) - ({ 0 });
	write("Your pointed ears tingle as you "+
	"sense " + (sizeof(titles) ? LANG_WNUM(sizeof(titles)) : "no") +
	" other " + ((sizeof(titles) == 1) ? "member of "+
	"Eil-Galaith" : "members of Eil-Galaith") +".\n");
	map(titles, write @ &sprintf("- %-=70s\n", ));
	write("\n");
	return 1;
}
