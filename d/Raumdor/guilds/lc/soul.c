/*********************************************************************
 * - soul.c                                                        - *
 * - A simple soul that also holds emotes for Ladies club          - *
 * - Created by Damaris@Genesis 5/2003                             - *
 * - Added lchold and lcoffer Damaris@Genesis 01/2006              - *
 *********************************************************************/

#pragma strict_types

inherit "/cmd/std/command_driver"; 
inherit "/lib/commands";

#include "/d/Raumdor/defs.h"
#include "guild.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <const.h>
#include <files.h>
#include <filter_funs.h>
#include <language.h>
#include <living_desc.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <options.h>
#define SUBLOC_SOULEXTRADESC ("_soul_cmd_extra")
#define SOULDESC(x)          (this_player()->add_prop(LIVE_S_SOULEXTRA, (x)))
string
get_soul_id()
{
    return "ladies";
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
	     "lc" : "lc",
	 "lcbeck" : "lcbeckon",
       "lcbeckon" : "lcbeckon",
          "lcbeg" : "lcbeg",
         "lcbite" : "lcbite",
       "lccaress" : "lccaress",
      "lcchuckle" : "lcchuckle",
      "lccomfort" : "lccomfort",
      "lccurtsey" : "lccurtsey",
          "lccry" : "lccry",
        "lcdance" : "lcdance",
         "lcdust" : "lcdust",
       "lcfrench" : "lcfrench",
       "lcgiggle" : "lcgiggle",
         "lcgrin" : "lcgrin",
         "lchelp" : "lchelp",
         "lchold" : "lchold",
          "lchug" : "lchug",
       "lchugsis" : "lchugsis",
         "lckiss" : "lckiss",
        "lclaugh" : "lclaugh",
         "lclook" : "lclook",
         "lclove" : "lclove",
         "lclust" : "lclust",
        "lcoffer" : "lcoffer",
         "lcpout" : "lcpout",
       "lcseduce" : "lcseduce",
        "lcsmile" : "lcsmile",
     "lcstraight" : "lcstraight",
       "lcstroke" : "lcstroke",
         "lctear" : "lctear",
        "lcthink" : "lcthink",
        "lctrace" : "lctrace",
         "lcwarn" : "lcwarn",
         "lcwave" : "lcwave",
         "lcwipe" : "lcwipe",
    ]);
}

void
using_soul(object live)
{
    if (!objectp(live))
	return;

    /* This adds the subloc. */
    live->add_subloc("ladies_subloc", this_object());

    setuid(); seteuid(getuid());

}

string
show_subloc(string subloc, object on, object who)
{
    string str;

    if (subloc != "ladies_subloc")
	return "";

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    return (on == who ? "You have" : capitalize(on->query_pronoun()) +
           " has") + " an air of genteel sophistication.\n";
}

int
lc(string str)
{
	string *words;
	if (!strlen(str))
	{
		notify_fail("Perform which Ladies command? " +
		"Syntax: lc <command> [<arguments>]\n");
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
lcbeckon(string str)
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
		notify_fail("lcbeckon whom?\n");
		return 0;
	}
	actor("You flash an illustrious smile and "+
	"beckon", oblist, " to you.");
	all2act(" flashes an illustrious smile and "+
	"beckons", oblist, " to " +
	this_player()->query_objective() + ".", "",
	ACTION_INGRATIATORY);
	target(" flashes an illustrious smile and beckons "+
	"you to "+ this_player()->query_objective() + ".", oblist, "",
	ACTION_INGRATIATORY);
	return 1;
}

int
lcbeg(string str)
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
		notify_fail("Beg whose forgiveness?\n");
		return 0;
	}
	actor("You elegantly slip down on bended knee and "+
	"graciously beg forgiveness from"+
	"" + (sizeof(oblist) > 1 ? " each of" : ""), oblist, ".");
	all2act(" elegantly slips down on bended knee and "+
	"graciously begs forgiveness "+
	"from", oblist,".", "", ACTION_INGRATIATORY);
	target(" elegantly slips down on bended knee and graciously begs "+
	"your forgiveness.", oblist, "", ACTION_INGRATIATORY);
	return 1;
}

int
lcbite(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You softly bite on your bottom lip.\n");
		allbb(" softly bites on "+
		"" + this_player()->query_possessive() + " bottom lip.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lcbite whom?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You cannot bite more than one "+
		"person at once.\n");
		return 0;
	}
	actor("You softly bite on", oblist,"'s bottom lip.",);
	all2actbb(" softly bites on", oblist, "'s bottom lip.", "",);
	target(" softly bites on your bottom lip.", oblist,"");
	return 1;
}

int
lccaress(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You elegantly run your fingertips along your neck "+
		"caressing your skin slowly.\n");
		allbb(" elegantly runs "+ HIS(TP) + " fingertips along "+
		"" + HIS(TP) + " neck caressing " + HIS(TP) + " "+
		"skin slowly.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lccaress whom?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You cannot caress more than one "+
		"person at once.\n");
		return 0;
	}
	actor("You elegantly run your fingertips "+
	"along", oblist, "'s neck " +
	"caressing " + oblist[0]->query_possessive() + " skin slowly.",);
	targetbb(" elegantly runs "+ HIS(TP) +" "+
	"fingertips along your neck caressing your skin "+
	"slowly.", oblist, "");
	all2actbb(" elegantly runs " + HIS(TP) + " "+
	"fingertips along", oblist, "'s neck caressing "+
	""+ oblist[0]->query_possessive() + " skin slowly.", "",);
	return 1;
}

int
lcchuckle(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You press your fingertips to your lips, "+
		"stifling an amused chuckle.\n");
		allbb(" presses  "+ HIS(TP) + " "+
		"fingertips to " + HIS(TP) + " "+
		"lips and stifles an amused chuckle.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lcchuckle at whom?\n");
		return 0;
	}
	actor("You press your fingertips to your lips as you "+
	"chuckle amusedly at", oblist,".");
	all2actbb(" presses "+ this_player()->query_possessive() + " "+
	"fingertips to " + this_player()->query_possessive() + " "+
	"lips as " + this_player()->query_pronoun() + " "+
	"chuckles amusedly at", oblist,".");
	target(" presses "+ this_player()->query_possessive() + " "+
	"fingertips to " + this_player()->query_possessive() + " "+
	"lips as " + this_player()->query_pronoun() + " "+
	"chuckles amusedly at you.", oblist, "");
	return 1;
}

int
lccomfort(string str)
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
		notify_fail("lccomfort whom?\n");
		return 0;
	}
	actor("With gentle reassurance you pull" +
	(sizeof(oblist) > 1 ? " each of" : ""), oblist,
	" into a comforting embrace.");
	all2act(" with such gentle reassurance pulls", oblist," into a "+
	"comforting embrace.", "", ACTION_CONTACT | ACTION_INTIMATE);
	target(" with such gentle reassurance pulls you into a "+
	"comforting embrace.", oblist, "", ACTION_CONTACT |
	ACTION_INTIMATE);
	return 1;
}

int
lccurtsey(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You curtsey elegantly and with poise.\n");
		allbb(" curtseys elegantly and with poise.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lccurtsey at whom?\n");
		return 0;
	}
	actor("You curtsey elegantly and with poise before", oblist, ".");
	targetbb(" curtseys before you elegantly and with poise.", oblist);
	all2actbb(" curtseys elegantly and with poise before", oblist, ".");
	return 1;
}

int
lccry(string str)
{
	SOULDESC("crying softly");
	write("You cry softly with tears streaming down "+
	"your soft cheeks.\n");
	allbb(" cries with tears streaming "+
	"down "+ this_player()->query_possessive() + " soft "+
	"cheeks.", ACTION_MACTIVITY | ACTION_VISUAL);
	return 1;
}

int
lcdance(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You gracefully sway your shoulders slowly "+
		"back and forth indicating you feel like dancing.\n");
		allbb(" gracefully sways "+ HIS(TP) + " "+
		"shoulders slowly back and forth indicating "+
		""+ HE(TP) +" feels like dancing.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lcdance with whom?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You cannot dance with more than one "+
		"person at once.\n");
		return 0;
	}
	actor("You gently slip your arms around", oblist, "'s "+
	"shoulders, discreetly pressing your body close to "+
	"" + oblist[0]->query_possessive() +
	" in a modest yet graceful slow dance.",);
	all2actbb(" gently slips " + HIS(TP) + " "+
	"arms around", oblist, "'s shoulders, pressing "+
	""+ this_player()->query_possessive() + " body to "+
	"" + oblist[0]->query_possessive() + " "+
	"in a modest yet graceful slow dance.", "",);
	target(" gently slips "+ this_player()->query_possessive() + " "+
	"arms around your shoulders, discreetly pressing "+
	""+ this_player()->query_possessive() +" body close to yours in "+
	"a modest yet graceful slow dance.", oblist, "");
	return 1;
}

int
lcdust()
{
	write("You dust your clothes off.\n");
	allbb(" dusts "+ HIS(TP) +" clothes off.");
	return 1;
}


int
lcfrench(string str)
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
		return notify_fail("lcfrench whom?\n");
	}
	actor("You gently press your fingertips to" +
	(size > 1 ? " each of" : ""), oblist, "'s cheek while giving " +
	(size > 1 ? "them" : oblist[0]->query_objective()) +
	" a sweet yet passionate kiss.",);
	all2act(" gently presses " + HIS(TP) + " "+
	"fingertips to", oblist,"'s cheek while giving " +
	(size > 1 ? "them" : oblist[0]->query_objective()) + " a "+
	"sweet yet passionate kiss.", "", ACTION_CONTACT |
	ACTION_INTIMATE,);
	target(" gently presses "+ HIS(TP) + " fingertips to your "+
	"cheek while giving you a sweet yet passionate "+
	"kiss.", oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
	return 1;
}


int
lcgrin(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("Your lips curl up in a marvelous yet "+
		"quite refined grin.\n");
		allbb(" curls up "+ HIS(TP) +" lips in a marvelous "+
		"yet refined grin.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lcgrin at whom?\n");
		return 0;
	}
	actor("Your lips curl up in a marvelous yet refined "+
	"grin at", oblist, ".");
	targetbb(" curls up "+ this_player()->query_possessive() + " "+
	"lips giving you a marvelous yet refined grin.", oblist);
	all2actbb(" lips curl up in a marvelous yet refined "+
	"grin at", oblist, ".");
	return 1;
}

int
lcgiggle(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You giggle flirtatiously as you lower "+
		"your eyes.\n");
		allbb(" giggles flirtatiously as "+
		""+ this_player()->query_pronoun() + " lowers "+
		"" + this_player()->query_possessive() + " eyes.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lcgiggle at whom?\n");
		return 0;
	}
	actor("You giggle flirtatiously at", oblist," as you "+
	"lower your eyes.");
	all2actbb(" giggles flirtatiously at", oblist," as "+
	""+ this_player()->query_pronoun() +" lowers her eyes.");
	target(" giggles flirtatiously at you as "+
	""+ this_player()->query_pronoun() + " lowers "+
	"" + this_player()->query_possessive() + " eyes.", oblist, "");
	return 1;
}

int
lchold(string str)
{
	object *oblist;
	string *how;
	how = parse_adverb_with_space(str, "elegantly", 0);
	if (!stringp(how[0]))
	{
		write("You" + how[1] + " hold your hands together in "+
		"your lap.\n");
		allbb("" + how[1] + " holds "+
		""+ this_player()->query_possessive() + " "+
		"hands together in " + HIS(TP) + " "+
		"lap.", how[1],);
		return 1;
	}
	oblist = parse_this(how[0], "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lchold hands with who?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You cannot hold hands with more than one "+
		"person that isn't very lady like.\n");
		return 0;
	}
	actor("You slip your hand in", oblist, "'s hand " +
	"holding it in yours" + how[1] + ".",);
	targetbb(" slips "+ this_player()->query_possessive() +" "+
	"hand in yours holding it" + how[1] + ".", oblist, how[1],);
	all2actbb(" slips " + this_player()->query_possessive() + " "+
	"hand in", oblist, "'s hand holding it" + how[1] + ".", "",);
	return 1;
}

int
lchug(string str)
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
		return notify_fail("lchug whom?\n");
	}
	actor("You graciously slip your arms around" +
	(size > 1 ? " each of" : ""), oblist, "'s waist and hug " +
	(size > 1 ? "them" : oblist[0]->query_objective()) +
	" pleasantly.",);
	all2act(" graciously slips " + this_player()->query_possessive() +
	" arms around", oblist,"'s waist and hugs " +
	(size > 1 ? "them" : oblist[0]->query_objective()) +
	" pleasantly.", "", ACTION_CONTACT | ACTION_INTIMATE,);
	target(" graciously slips "+ this_player()->query_possessive() +
	" arms around your waist and hugs you pleasantly.",
	oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
	return 1;
}

int
lchugsis(string str)
{
	object *oblist;
	oblist = parse_this(str, "[the] %l", ACTION_CONTACT |
	ACTION_INTIMATE);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("Hug whom?\n");
		return 0;
	}
	actor("You gently hug" +
	(sizeof(oblist) > 1 ? " each of" : ""), oblist,
	" in a warm sisterly embrace.");
	all2act(" gently hugs", oblist, " in a warm sisterly embrace.",
	"", ACTION_CONTACT | ACTION_INTIMATE);
	target(" gently hugs you in a warm sisterly embrace.",
	oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
	return 1;
}

int
lckiss(string str)
{
	object *oblist;
	oblist = parse_this(str, "[the] %l", ACTION_CONTACT | 
	ACTION_INTIMATE);
	if (!sizeof(oblist))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		notify_fail("lckiss whom?\n");
		return 0;
	}
	actor("You press your lips to" +
	(sizeof(oblist) > 1 ? " each of" : ""), oblist,
	"'s in an enchantingly gentle kiss.",);
	all2act(" gives", oblist, " an enchanting kiss.", "",
	ACTION_CONTACT | ACTION_INTIMATE);
	target(" presses " + this_player()->query_possessive() +
	" lips to yours in an enchantingly gentle kiss.",
	oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
	return 1;
}

int
lclaugh(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You laugh attractively as your eyes dance and "+
		"sparkle enchantingly.\n");
		allbb(" laughs attractively as " +
		this_player()->query_possessive() +
		" eyes dance and sparkle enchantingly.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lclaugh at whom?\n");
		return 0;
	}
	actor("You laugh attractively at", oblist, " as your eyes "+
	"dance and sparkle enchantingly.");
	all2actbb(" laughs attractively at", oblist, " as " +
	this_player()->query_possessive() +
	" eyes dance and sparkle enchantingly.");
	target(" laughs attractively at you as " +
	this_player()->query_possessive() +
	" eyes dance and sparkle enchantingly.", oblist, "");
	return 1;
}

int
lclook(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You look like a true lady as you look around.\n");
		allbb(" looks like a true lady as " +
		this_player()->query_pronoun() + " looks around.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("llook at whom?\n");
		return 0;
	}
	actor("You look toward", oblist, " giving " +
	(sizeof(oblist) > 1 ? "them" : oblist[0]->query_objective()) +
	" your most gracious look.");
	all2actbb(" looks like a true lady as "+
	"" + this_player()->query_pronoun() + " glances at", oblist, "");
	target(" looks toward you with graciousness and poise like a "+
	"true lady should.", oblist, "");
	return 1;
}

int
lclove(string str)
{
	int size;
	object *oblist;
	oblist = parse_this(str, "[the] %l", ACTION_CONTACT |
	ACTION_INTIMATE);
	if (!(size = sizeof(oblist)))
	{
		if (strlen(parse_msg))
		{
			write(parse_msg);
			return 1;
		}
		return notify_fail("lclove whom?\n");
	}
	actor("You entwine your arms around" +
	(size > 1 ? " each of" : ""), oblist, "'s neck and whisper how " +
	(size > 1 ? "they have" : (oblist[0]->query_pronoun() + " has")) +
	" captured your gentle heart in love.",);
	all2act(" entwines " + this_player()->query_possessive() +
	" arms around", oblist, "'s neck and whispers in "+
	(size > 1 ? "their ears." :
	(oblist[0]->query_possessive() + " ear.")),
	"", ACTION_CONTACT | ACTION_INTIMATE,);
	target(" entwines " + this_player()->query_possessive() +
	" arms around your neck and whispers how you've captured " +
	this_player()->query_possessive() + " gentle heart in love.",
	oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
	return 1;
}

int
lclust(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You look and feel quite lustful at the moment.\n"+
		"Shame on you!\n");
		allbb(" looks like "+ HE(TP) + " is having some "+
		"lustful thoughts.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Feeling lustful at whom?\n");
		return 0;
	}
	{
		actor("You give", oblist, " a far more lustful look than "+
		"any lady ever should.\nShame on you!");
		all2actbb(" looks like "+ HE(TP) + " "+
		"is having lustful thoughts as "+
		""+ HE(TP) + " looks at", oblist, "");
		target(" shows you the lustful desire you provoke "+
		"within "+ HIM(TP) +".", oblist, "");
		return 1;
	}
}
int
lcoffer(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You offer your hand to be kissed.\n");
		allbb(" offers "+ HIS(TP) + " hand to be kissed.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("Offer your hand to be kissed at who?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You cannot offer your hand to be kissed by "+
		"more than one person at a time.\n");
		return 0;
	}
	{
		actor("You offer", oblist, " your hand to be kissed.");
		all2actbb(" offers", oblist, " "+
		""+ HIS(TP) + " hand to be kissed.");
		target(" offers you "+ HIS(TP) +" hand "+
		"to be kissed.", oblist, "");
		return 1;
	}
}

int
lcpout(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("You curl up your lips in a charismatic pout.\n");
		allbb(" curls up "+ this_player()->query_possessive() +
		" lips in a charismatic pout.");
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lcpout at whom?\n");
		return 0;
	}
	actor("You curl up your lips in a charismatic pout at",
	oblist, ".");
	all2actbb(" curls up " + HIS(TP) + " lips in a charismatic "+
	"pout at", oblist, ".");
	target(" curls up "+ HIS(TP) + " lips at you in a charismatic "+
	"pout.", oblist, "");
	return 1;
}

int
lcseduce(string str)
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
		notify_fail("lcseduce whom?\n");
		return 0;
	}
	if (sizeof(oblist) > 1)
	{
		notify_fail("You cannot seduce more than one "+
		"person at once.\n");
		return 0;
	}
	actor("You whisper sweet little endearments in", oblist,
	"'s ear trying to seduce " + oblist[0]->query_objective() +
	".",);
	all2act(" whispers into", oblist, "'s ear.", "",);
	target(" whispers sweet little endearments in your ear "+
	"trying to seduce you.", oblist, "", ACTION_INGRATIATORY);
	return 1;
}

int
lcsmile(string str)
{
	object *oblist;
	if (!stringp(str))
	{
		write("Your lips curl up in a cultured smile.\n");
		allbb("'s lips curl up in a cultured smile.", "",);
		return 1;
	}
	oblist = parse_this(str, "[at] [the] %i");
	if (!sizeof(oblist))
	{
		notify_fail("lcsmile at whom/what?\n");
		return 0;
	}
	actor("Your lips curl up in a cultured smile at", oblist, ".");
	all2actbb("'s lips curl up in a cultured smile at", oblist, ".",
	"",);
	target("'s lips curl up in a cultured smile at you.", oblist,
	"",);
	return 1;
}

int
lcstraight()
{
	write("You straighten your clothes in a refined "+
	"fashion.\n");
	allbb(" straightens "+ this_player()->query_possessive() +" "+
	"clothes in a refined fashion.");
	return 1;
}

int
lcstroke(string str)
{
	object *oblist;
	string *how;
	string location;
	int    attrs;

    attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);

    oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
      "'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
      "'forearm' / 'hand' / 'hands' / 'knee' / 'lips' / 'neck' / "+
      "'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy' / "+
      "'wrist'", attrs);
      notify_fail("Stroke whom [where / how] ?\n");
      if (sizeof(oblist))
      {
	      how = explode(str, " ");
	      switch(location = how[sizeof(how) - 1])
	      {
		      case "neck":
		      case "forearm":
		      target(" elegantly strokes " + this_player()->query_possessive() + " "+
		      "fingertips along the back of "+
		      "your " + location + ".", oblist, "", attrs);
		      actor("You elegantly stroke your fingertips "+
		      "along the back of", oblist, "'s " + location + ".",);
		      all2act(" elegantly strokes " + this_player()->query_possessive() + " "+
		      "fingertips along the back of", oblist, "'s " + location + ".", "", attrs,);
		      return 1;
		      
		      case "abdomen":
		      case "arm":
		      case "belly":
		      case "cheek":
		      case "chin":
		      case "ear":
		      case "forehead":
		      case "hand":
		      case "hands":
		      case "knee":
		      case "lips":
		      case "palm":
		      case "stomach":
		      case "tummy":
		      target(" elegantly strokes " + this_player()->query_possessive() + " "+
		      "fingertips along your " + location + ".", oblist, "", attrs);
		      actor("You elegantly stroke your fingertips "+
		      "along", oblist, "'s " + location + ".", );
		      all2act(" elegantly strokes " + this_player()->query_possessive() + " "+
		      "fingertips along", oblist, "'s " + location + ".", "", attrs, );
		      return 1;
		      
		      default:
		      notify_fail("Stroke whom [where / how]? Rather... this should " +
		      "not happen. Please make a sysbugreport about this.\n");
		      return 0;
		      }
		      return 1;
		     }
		     
		     return 0;
}

int
lctear()
{
	SOULDESC("crying softly");
	write("A single tear softly falls down your soft cheek.\n");
	allbb(" looks up and a single tear softly falls "+
	"down "+ this_player()->query_possessive() + " "+
	"soft cheek.", ACTION_MACTIVITY | ACTION_VISUAL);
	return 1;
}

int
lcthink()
{
	write("You run you fingertips along your chin in a refined yet "+
	"thoughtful manner.\n");
	allbb(" runs " + HIS(TP) + " fingertips along " + HIS(TP) + " "+
	"chin in a refined yet thoughtful manner.", "");
	return 1;
}

int
lctrace(string str)
{
    object *oblist;
    string *how;
    string location;
    int    attrs;

    attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);

    oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
      "'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
      "'forearm' / 'hand' / 'hands' / 'knee' / 'lips' / 'neck' / "+
      "'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy' / "+
      "'wrist'", attrs);
    notify_fail("lctrace whom [where / how] ?\n");
    if (sizeof(oblist))
    {
        how = explode(str, " ");
        switch(location = how[sizeof(how) - 1])
        {
        case "neck":
        case "forearm":
            target(" elegantly traces "+
            "" + this_player()->query_possessive() + " "+
              "fingertips along the back of "+
              "your " + location + ".", oblist, "", attrs);
            actor("You elegantly trace your fingertips "+
              "along the back of", oblist, "'s " + location + ".",);
            all2act(" elegantly traces "+
            "" + this_player()->query_possessive() + " "+
              "fingertips along the back "+
              "of", oblist, "'s " + location + ".", "", attrs,);
            return 1;

        case "chin":
        case "cheek":
        case "abdomen":
        case "belly":
        case "tummy":
        case "ear":
        case "thigh":
        case "stomach":
        case "lips":
        case "forehead":
        case "hand":
        case "hands":
        case "arm":
        case "palm":
        case "knee":
            target(" elegantly traces "+
            "" + this_player()->query_possessive() + " "+
              "fingertips along your " + location + ".", oblist, "", attrs);
            actor("You elegantly trace your fingertips "+
              "along", oblist, "'s " + location + ".", );
            all2act(" elegantly traces "+
            "" + this_player()->query_possessive() + " "+
              "fingertips along", oblist, "'s " + location + ".", "", attrs, );
            return 1;

        default:
            notify_fail("Trace whom [where / how]? Rather... this should " +
                "not happen. Please make a sysbugreport about this.\n");
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

        notify_fail("Trace whom [how / where]?\n");
        return 0;
    }

}

int
lcwarn(string str)
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
		notify_fail("lcwarn who?\n");
		return 0;
    }

    actor("You warn", oblist, " that if " +
          ((sizeof(oblist) > 1) ? "they continue" :
              (oblist[0]->query_pronoun() + " continues")) +
          " in such a manner you will be forced to settle this " +
          "in a ladies fashion, and " +
          ((sizeof(oblist) > 1) ? "they" : oblist[0]->query_pronoun()) +
          " will be punished throughly.");
    all2act(" warns", oblist, " that if " +
            ((sizeof(oblist) > 1) ? "they continue" :
                (oblist[0]->query_pronoun() + " continues")) +
            " in such a manner then " + this_player()->query_pronoun() +
            " will be forced to settle this in a ladies fashion and " +
            ((sizeof(oblist) > 1) ? "they" : oblist[0]->query_pronoun()) +
            " will be punished thoroughly.");
    target(" warns you that if you continue in such a manner then " +
           this_player()->query_pronoun() + " will be forced to " +
           "settle this in a ladies fashion, and that you will be " +
           "punished thoroughly.", oblist, "");

    return 1;
}

int
lcwave(string str)
{
    object *oblist;

    if (!stringp(str))
    {
	write("You wave elegantly and gracefully.\n");
	allbb(" waves elegantly and gracefully.");

	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Wave at whom?\n");
        return 0;
    }

    actor("You wave elegantly and gracefully in", oblist, "'s direction.", );
    all2actbb(" waves elegantly and gracefully in", oblist, "'s direction.",);
    target(" waves elegantly and gracefully in your direction.", oblist, "");

    return 1;
}
int
lcwipe(string str)
{
    object *oblist;
    if (!stringp(str))
    {
	write("You elegantly wipe a tear from your eye.\n");
	allbb(" elegantly wipes a tear from " +
	      this_player()->query_possessive() + " eye.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Wipe what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("You cannot wipe more than one eye at once.\n");
        return 0;
    }

    actor("You elegantly wipe a tear from", oblist,"'s cheek.",);
    all2actbb(" elegantly wipes away a tear from", oblist, "'s cheek.", "",);
    target(" elegantly wipes away a tear that has fallen on your "+
      "cheek.", oblist,"");

    return 1;
}

public int
lchelp(string str)
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
