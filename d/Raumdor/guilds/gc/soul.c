/*
 * Soul for the 
 * Gentlemans club
 * Created by Damaris 10/2001
 * - slightly updated by Valen, 20011019
 * - Updated emotions Damaris 04/2006 
 */

#pragma strict_types

#include "/d/Raumdor/defs.h"
#include "guild.h"
#include <cmdparse.h>

inherit "/cmd/std/command_driver"; 
inherit "/lib/commands";

string
get_soul_id()
{
    return "gentlemans";
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
             "gc" : "gc",
         "gcbeck" : "gcbeckon",
       "gcbeckon" : "gcbeckon",
          "gcbeg" : "gcbeg",
         "gcbite" : "gcbite",
        "gcbite2" : "gcbite2",
          "gcbow" : "gcbow",
       "gccaress" : "gccaress",
      "gccomfort" : "gccomfort",
        "gcdance" : "gcdance",
         "gcdust" : "gcdust",
       "gcfrench" : "gcfrench",
         "gcgrin" : "gcgrin",
         "gchelp" : "gchelp",
          "gchug" : "gchug",
       "gchugbro" : "gchugbro",
         "gckiss" : "gckiss",
        "gckiss2" : "gckiss2",
        "gclaugh" : "gclaugh",
         "gclick" : "gclick",
         "gclook" : "gclook",
         "gclove" : "gclove",
         "gclust" : "gclust",
       "gcnibble" : "gcnibble",
        "gcoffer" : "gcoffer",
         "gcpout" : "gcpout",
          "gcrub" : "gcrub",
       "gcseduce" : "gcseduce",
        "gcsmile" : "gcsmile",
   "gcstraighten" : "gcstraighten",
       "gcstroke" : "gcstroke",
        "gcthink" : "gcthink",
        "gctrace" : "gctrace",
         "gcwarn" : "gcwarn",
         "gcwave" : "gcwave",
         "gcwipe" : "gcwipe",
    ]);
}

void
using_soul(object live)
{
    if (!objectp(live))
	return;

    /* This adds the subloc. */
    live->add_subloc("gentleman_subloc", this_object());

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

    if (subloc != "gentleman_subloc")
	return "";

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    return (on == who ? "You have" : capitalize(on->query_pronoun()) +
           " has") + " a refined aura.\n";
}

int
gc(string str)
{
	string *words;
	if (!strlen(str))
	{
		notify_fail("Perform which Gentleman command? " +
		"Syntax: gc <command> [<arguments>]\n");
		return 0;
	}
	words = explode(str, " ");
	if (!stringp(cmdlist[words[0]]))
	{
		notify_fail("The command " + words[0] +
		" is not a known Gentleman command.\n");
		return 0;
	}
	str = ((sizeof(words) > 1) ? implode(words[1..], " ") : "");
	return call_other(this_object(), cmdlist[words[0]], str);
}

string
gadverb()
{
	string *words = ({
		"smoothly", "softly", "gently", "tenderly",
		});
		return words[random(sizeof(words))];
}

int
gcbeckon(string str)
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

	notify_fail("Beckon whom?\n");
	return 0;
    }

    actor("You charmingly beckon", oblist, " to you.");
    all2act(" beckons", oblist, " to " +
            this_player()->query_objective() + ".", "",
            ACTION_INGRATIATORY);
    target(" charmingly beckons you to "+
           this_player()->query_objective() + ".", oblist, "",
           ACTION_INGRATIATORY);
    return 1;
}

int
gcbeg(string str)
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

    actor("You slowly get down on bended knee and charmingly beg " +
          "forgiveness from" + (sizeof(oblist) > 1 ? " each of" : ""),
          oblist, ".");
    all2act(" slowly gets down on " + this_player()->query_possessive() +
            " bended knee and charmingly begs forgiveness from", oblist,
            ".", "",
            ACTION_INGRATIATORY);
    target(" slowly gets down on " + this_player()->query_possessive() +
           " bended knee and charmingly begs your forgiveness.", oblist, "",
           ACTION_INGRATIATORY);
    return 1;
}

int
gcbite(string str)
{
    object *oblist;
    if (!stringp(str))
    {
	write("You charmingly bite on your bottom lip.\n");
	allbb(" charmingly bites on " +
	      this_player()->query_possessive() + " bottom lip.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Bite whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("You cannot bite more than one person at once.\n");
        return 0;
    }

    actor("You charmingly bite on", oblist,"'s bottom lip.",);
    all2actbb(" charmingly bites on", oblist, "'s bottom lip.", "",);
    target(" charmingly bites on your bottom lip.", oblist,"");

    return 1;
}
int
gcbite2(string str)
{
	object *oblist;
	string *how;
	string location, gadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	gadv = gadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ gadv +" bites along the back of your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" bite along the back "+
			"of", oblist, "'s " + location + ".",);
			all2act(" "+ gadv +" bites along the back "+
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
			target(" "+ gadv +" bites along your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" bite along", oblist, "'s "+
			"" + location + ".",);
			all2act(" "+ gadv +" bites along", oblist, "'s "+
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
gcbow(string str)
{
    object *oblist;
    if (!stringp(str))
    {
	write("You bow with elegance and with sophistication.\n");
	allbb(" bows elegantly and with sophistication.");
	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Bow at whom?\n");
        return 0;
    }
    
    actor("You bow elegantly and with sophistication before", oblist,".");

    targetbb(" bows before you with elegance and sophistication.", oblist);

    all2actbb(" bows elegantly and with sophistication before", oblist, ". ");

    return 1;
}

int
gccaress(string str)
{
	object *oblist;
	string *how;
	string location, gadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	gadv = gadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ gadv +" caresses along the back of "+
			"your " + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" caress along the back "+
			"of", oblist, "'s " + location + ".", );
			all2act(" "+ gadv +" caresses along the back "+
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
			target(" "+ gadv +" caresses along your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" caress along", oblist, "'s "+
			"" + location + ".",);
			all2act(" "+ gadv +" caresses along", oblist, "'s "+
			"" + location + ".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Gccaress whom [where / how]?\n");
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
		notify_fail("Gccaress whom [how / where]?\n");
		return 0;
	}
	actor("You caress", oblist, how[1] + ".");
	all2act(" caresses", oblist, how[1] + ".", how[1], attrs);
	target(" caresses you" + how[1] + ".", oblist, how[1], attrs);
	return 1;
}

int
gccomfort(string str)
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

	notify_fail("Comfort whom?\n");
	return 0;
    }

    actor("With gentle elegance you pull" +
          (sizeof(oblist) > 1 ? " each of" : ""), oblist,
          " into a comforting embrace.");
    all2act(" with such gentle elegance pulls", oblist,
            " into a comforting embrace.", "",
            ACTION_CONTACT | ACTION_INTIMATE);
    target(" with such gentle elegance pulls you into a comforting "+
      "embrace.",
           oblist, "",
           ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
}

int
gcdance(string str)
{
    object *oblist;

    if (!stringp(str))
    {
	write("You charmingly sway your shoulders slowly back and forth "+
	      "indicating you feel like dancing.\n");
	allbb(" charmingly sways "+ this_player()->query_possessive() + " " +
   	      "shoulders slowly back and forth indicating " +
   	      this_player()->query_pronoun() +" feels like dancing.");

	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Dance with whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("You cannot dance with more than one person at once.\n");
        return 0;
    }

    actor("You charmingly slip your arms around", oblist, "'s waist, " +
          "pressing your body to " + oblist[0]->query_possessive() +
          " and swaying your body in a delightful slow dance.",);
    all2actbb(" charmingly slips " + this_player()->query_possessive() +
              " arms around", oblist, "'s waist, pressing " +
              this_player()->query_possessive() + " body " +
              "to " + oblist[0]->query_possessive() + " and " +
              "swaying " + this_player()->query_possessive() + " body " +
              "in a delightful slow dance with " +
              oblist[0]->query_possessive() + ".", "",);
    target(" charmingly slips "+ this_player()->query_possessive() +
           " arms around your waist, pressing "+
           this_player()->query_possessive() +" body to yours and " +
           "swaying "+ this_player()->query_possessive() + " body in " +
           "a delightful slow dance with you.", oblist, "");

    return 1;
}

int
gcdust()
{
    write("You dust your clothes off.\n");
    allbb(" dusts "+ this_player()->query_possessive() +" "+
      "clothes off.");
    return 1;
}

int
gcfrench(string str)
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

	notify_fail("French whom?\n");
	return 0;
    }

    actor("You smile captivatingly as you gently slip an arm around" +
          (sizeof(oblist) > 1 ? " each of" : ""), oblist,
          " and give " + oblist[0]->query_objective() +
          " a very deep and passionate kiss.");
    all2act(" smiles captivatingly as " +
            this_player()->query_pronoun() + " slips " +
            this_player()->query_possessive() + " arm around",
            oblist, " and gives " +
            (sizeof(oblist) > 1 ? "them" : oblist[0]->query_objective()) +
            " a deep passionate kiss.",
            "",ACTION_CONTACT | ACTION_INTIMATE);
    target(" smiles captivatingly as " + this_player()->query_pronoun() +
           " slips " + this_player()->query_possessive() +
           " arm around you and gives you a very deep and "+
           "passionate kiss.",
           oblist, "", ACTION_CONTACT | ACTION_INTIMATE);

    return 1;
}

int
gcgrin(string str)
{
    object *oblist;
    
    if (!stringp(str))
    {
	write("Your lips curl up in a captivating grin.\n");
	allbb(" curls up "+ this_player()->query_possessive() +
	      " lips in a captivatingly soft grin.");

	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Grin at whom?\n");
        return 0;
    }

    actor("Your lips curl up in a captivating grin at", oblist, ".");
    targetbb(" curls up "+ this_player()->query_possessive() +
             " lips at you and gives you a captivating grin.", oblist);
    all2actbb(" lips curl up in a captivating grin at", oblist, ".");

    return 1;
}

int
gchug(string str)
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

	return notify_fail("Hug whom?\n");
    }

    actor("You suavely slip your arms around" +
          (size > 1 ? " each of" : ""), oblist, "'s waist and hug " +
          (size > 1 ? "them" : oblist[0]->query_objective()) +
          " charmingly.",);
    all2act(" suavely slips " + this_player()->query_possessive() +
            " arms around", oblist,"'s waist and hugs " +
            (size > 1 ? "them" : oblist[0]->query_objective()) +
            " charmingly.", "", ACTION_CONTACT | ACTION_INTIMATE,);
    target(" suavely slips "+ this_player()->query_possessive() +
           " arms around your waist and hugs you charmingly.",
           oblist, "", ACTION_CONTACT | ACTION_INTIMATE);

    return 1;
}

int
gchugbro(string str)
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

	notify_fail("Hug whom?\n");
	return 0;
    }

    actor("You firmly hug" +
          (sizeof(oblist) > 1 ? " each of" : ""), oblist,
          " in a warm brotherly embrace.");
    all2act(" firmly hugs", oblist, " in a warm brotherly embrace.",
            "", ACTION_CONTACT | ACTION_INTIMATE);
    target(" firmly hugs you in a warm brotherly embrace.",
           oblist, "", ACTION_CONTACT | ACTION_INTIMATE);
    return 1;
}

int
gckiss(string str)
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

    actor("You press your charming lips to" +
          (sizeof(oblist) > 1 ? " each of" : ""), oblist,
          "'s in a captivating gentle kiss.",);
    all2act(" gives", oblist, " a charming kiss.", "",
            ACTION_CONTACT | ACTION_INTIMATE);
    target(" presses " + this_player()->query_possessive() +
           " charming lips to yours in a captivating gentle kiss.",
           oblist, "", ACTION_CONTACT | ACTION_INTIMATE);

    return 1;
}

int
gckiss2(string str)
{
	object *oblist;
	string *how;
	string location, gadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	gadv = gadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ gadv +" brushes "+ HIS(TP) +" "+
			"lips along the back of your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" brush your lips "+
			"along the back "+
			"of", oblist, "'s " + location + ".",);
			all2act(" "+ gadv +" brushes "+ HIS(TP) +" "+
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
			target(" "+ gadv +" brushes "+ HIS(TP) +" "+
			"lips along your " + location + ""+
			".", oblist, "", attrs);
			actor("You "+ gadv +" brush your lips "+
			"along", oblist, "'s " + location + ".",);
			all2act(" "+ gadv +" brushes "+ HIS(TP) +" "+
			"lips along", oblist, "'s " + location + ""+
			".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Gckiss whom [where / how]?\n");
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
		notify_fail("Gckiss whom [how / where]?\n");
		return 0;
	}
	actor("You kiss", oblist, how[1] + ".");
	all2act(" kisses", oblist, how[1] + ".", how[1], attrs);
	target(" kisses you" + how[1] + ".", oblist, how[1], attrs);
	return 1;
}

int
gclaugh(string str)
{
    object *oblist;

    if (!stringp(str))
    {
	write("You laugh charmingly as your eyes dance and " +
	      "sparkle with mirth.\n");
	allbb(" laughs charmingly as " +
	      this_player()->query_possessive() +
	      " eyes dance and sparkle with mirth.");

	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Laugh at whom?\n");
        return 0;
    }

    actor("You laugh charmingly at", oblist, " as your eyes dance and " +
          "sparkle with mirth.");
    all2actbb(" laughs charmingly at", oblist, " as " +
              this_player()->query_possessive() +
              " eyes dance and sparkle with mirth.");
    target(" laughs charmingly at you as " +
           this_player()->query_possessive() +
           " eyes dance and sparkle with mirth.", oblist, "");

    return 1;
}

int
gclick(string str)
{
	object *oblist;
	string *how;
	string location, gadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	gadv = gadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ gadv +" licks along the back of your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" lick along the back "+
			"of", oblist, "'s " + location + ".",);
			all2act(" "+ gadv +" licks along the back "+
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
			target(" "+ gadv +" licks along your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" lick along", oblist, "'s "+
			"" + location + ".",);
			all2act(" "+ gadv +" licks along", oblist, "'s "+
			"" + location + ".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Gclick whom [where / how]?\n");
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
		notify_fail("Gclick whom [how / where]?\n");
		return 0;
	}
	actor("You lick", oblist, how[1] + ".");
	all2act(" licks", oblist, how[1] + ".", how[1], attrs);
	target(" licks you" + how[1] + ".", oblist, how[1], attrs);
	return 1;
}

int
gclook(string str)
{
    object *oblist;

    if (!stringp(str))
    {
	write("You look like a true gentleman as you look around.\n");
	allbb(" looks like a true gentleman as " +
              this_player()->query_pronoun() + " looks around.");

	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Look at whom?\n");
        return 0;
    }
    
    actor("You look toward", oblist, " giving " +
          (sizeof(oblist) > 1 ? "them" : oblist[0]->query_objective()) +
          " your most charming look.");
    all2actbb(" looks like a true gentleman as " +
              this_player()->query_pronoun() + " looks at", oblist, "");
    target(" looks toward you with charm and poise denoting what " +
           "a gentleman " + this_player()->query_pronoun() +
           " truly is.", oblist, "");

    return 1;
}

int
gclove(string str)
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
          (size > 1 ? " each of" : ""), oblist, "'s waist and whisper how " +
	  (size > 1 ? "they have" : (oblist[0]->query_pronoun() + " has")) +
	  " captured your heart in love.",);
    all2act(" entwines " + this_player()->query_possessive() +
            " arms around", oblist, "'s waist and whispers in "+
            (size > 1 ? "their ears." :
                (oblist[0]->query_possessive() + " ear.")),
            "", ACTION_CONTACT | ACTION_INTIMATE,);
    target(" entwines " + this_player()->query_possessive() +
           " arms around your waist and whispers how you've captured " +
           this_player()->query_possessive() + " heart in love.",
           oblist, "", ACTION_CONTACT | ACTION_INTIMATE);

    return 1;
}

int
gclust(string str)
{
    object *oblist;

    if (!stringp(str))
    {
	write("You look and feel quite like a lustful gentleman " +
              "at the moment.\nShame on you!\n");
	allbb(" looks like "+ this_player()->query_pronoun() + " is " +
              "having some lustful thoughts.");

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
      "more lustful look than any gentleman should give.\nShame on you!");
    all2actbb(" looks like "+ this_player()->query_pronoun() + " "+
    "is having lustful thoughts as "+
    ""+ this_player()->query_pronoun() + " looks at", oblist, "");
    target(" shows you the lustful desire you provoke "+
      "within "+ this_player()->query_objective() +".", oblist, "");
    return 1;
    }
}

int
gcnibble(string str)
{
	object *oblist;
	string *how;
	string location, gadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	gadv = gadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ gadv +" nibbles along the back of "+
			"your " + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" nibble along the back "+
			"of", oblist, "'s " + location + ".",);
			all2act(" "+ gadv +" nibbles along the back "+
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
			target(" "+ gadv +" nibbles along your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" nibble along", oblist, "'s "+
			"" + location + ".", );
			all2act(" "+ gadv +" nibbles along", oblist, "'s "+
			"" + location + ".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Gcnibble whom [where / how]?\n");
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
		notify_fail("Gcnibble whom [how / where]?\n");
		return 0;
	}
	actor("You nibble on", oblist, how[1] + ".");
	all2act(" nibbles on", oblist, how[1] + ".", how[1], attrs);
	target(" nibbles on you" + how[1] + ".", oblist, how[1], attrs);
	return 1;
}

int
gcoffer(string str)
{
    object *oblist;

    if (!stringp(str))
    {
	write("You gallantly offer your assistance.\n");
	allbb(" gallantly offers "+ this_player()->query_possessive() +
              " assistance.", "");

	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Offer assistance to whom?\n");
        return 0;
    }

    actor("You gallantly offer your assistance to", oblist, ".", );
    all2actbb(" gallantly offers " + this_player()->query_possessive() +
              " assistance to", oblist, ".", "");
    target(" gallantly offers to be of assistance to you.", oblist, "");

    return 1;
}

int
gcpout(string str)
{
    object *oblist;

    if (!stringp(str))
    {
	write("You purse your charming lips in a captivating pout.\n");
	allbb(" purses "+ this_player()->query_possessive() +
              " charming lips in a captivating pout.");

	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Pout at whom?\n");
        return 0;
    }

    actor("You purse your charming lips in a captivating pout at",
          oblist, ".");
    all2actbb(" purses " + this_player()->query_possessive() +
              " charming lips in a captivating pout at", oblist, ".");
    target(" purses "+ this_player()->query_possessive() +
           " charming lips at you in a captivating pout.", oblist, "");

    return 1;
}

int
gcrub(string str)
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

	notify_fail("Rub whom?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You cannot rub more than one person at once.\n");
	return 0;
    }

    actor("You gently press your fingertips into", oblist, "'s shoulders " +
          "smoothly rubbing down " + oblist[0]->query_possessive() +
          " back. You then slide your fingers down some more to " +
          oblist[0]->query_possessive() +
          " waist rubbing in a smooth gentle pattern.",);
    all2act(" gently presses " + this_player()->query_possessive() +
            " fingertips into", oblist, "'s shoulders rubbing smoothly " +
            "and gently all the way to " + oblist[0]->query_possessive() +
            " waist in a smooth gentle pattern.", "",);
    target(" gently presses " + this_player()->query_possessive() +
           " fingertips into your shoulders smoothly rubbing downward, " +
           "back and forth. You breathe in deeply while you relax by " +
           this_player()->query_possessive() +" gentle smooth touch as " +
           "he finishes with tender carressing patterns along your "+
           "waist.", oblist, "", ACTION_INGRATIATORY);

    return 1;
}

int
gcseduce(string str)
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

	notify_fail("Seduce whom?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You cannot seduce more than one person at once.\n");
	return 0;
    }

    actor("You whisper sweet little endearments in", oblist,
          "'s ear trying to seduce " + oblist[0]->query_objective() +
          " with your charm.",);
    all2act(" whispers into", oblist, "'s ear.", "",);
    target(" whispers sweet little endearments in your ear trying to " +
           "seduce you with " + this_player()->query_possessive() +
           " charm.", oblist, "", ACTION_INGRATIATORY);
    return 1;
}

int
gcsmile(string str)
{
    object *oblist;
    if (!stringp(str))
    {
	write("Your lips curl up in a captivating smile.\n");
	allbb("'s lips curl up in a captivating smile.", "",);

	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Smile at whom/what?\n");
        return 0;
    }

    actor("Your lips curl up in a captivating smile at", oblist, ".");
    all2actbb("'s lips curl up in a captivating smile at", oblist, ".",
              "",);
    target("'s lips curl up in a captivating smile at you.", oblist,
           "",);

    return 1;
}

int
gcstraighten()
{
    write("You straighten your clothes in a gentlemanly fashion.\n");
    allbb(" straightens "+ this_player()->query_possessive() +" "+
      "clothes in a gentlemanly fashion.");
    return 1;
}

int
gcstroke(string str)
{
	object *oblist;
	string *how;
	string location, gadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	gadv = gadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ gadv +" strokes "+ HIS(TP) +" "+
			"fingertips along the back of your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" stroke your fingertips "+
			"along the back "+
			"of", oblist, "'s " + location + ".", );
			all2act(" "+ gadv +" strokes "+ HIS(TP) +" "+
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
			target(" "+ gadv +" strokes "+ HIS(TP) +" "+
			"fingertips along your " + location + ""+
			".", oblist, "", attrs);
			actor("You "+ gadv +" stroke your fingertips "+
			"along", oblist, "'s " + location + ".",);
			all2act(" "+ gadv +" strokes "+ HIS(TP) +" "+
			"fingertips along", oblist, "'s " + location + ""+
			".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Gcstroke whom [where / how]?\n");
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
		notify_fail("Gcstroke whom [how / where]?\n");
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
gcthink()
{
	write("You run your fingertips along your chin in a thoughtful "+
	"manner.\n");
	allbb(" runs " + HIS(TP) + " fingertips along " + HIS(TP) + " "+
	"chin in a thoughtful manner.", "");
	return 1;
}

int
gctrace(string str)
{
	object *oblist;
	string *how;
	string location, gadv;
	int    attrs;
	attrs = (ACTION_CONTACT | ACTION_VISUAL | ACTION_MACTIVITY | ACTION_INTIMATE);
	oblist = parse_this(str, "[the] %l [all] [in] [under] [the] / "+
	"'forearm' / 'neck' / " +
	"'abdomen' / 'arm' / 'belly' / 'cheek' / 'chin' / 'ear' / "+
	"'wrist' / 'hand' / 'hands' / 'knee' / 'lips' / "+
	"'palm' / 'shoulder' / 'stomach' / 'thigh' / 'tummy'", attrs);
	
	gadv = gadverb();
	if (sizeof(oblist))
	{
		how = explode(str, " ");
		switch(location = how[sizeof(how) - 1])
		{
			case "neck":
			case "forearm":
			target(" "+ gadv +" traces "+ HIS(TP) +" "+
			"fingertips along the back of your "+
			"" + location + ".", oblist, "", attrs);
			actor("You "+ gadv +" trace your fingertips "+
			"along the back "+
			"of", oblist, "'s " + location + ".",);
			all2act(" "+ gadv +" traces "+ HIS(TP) +" "+
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
			target(" "+ gadv +" traces "+ HIS(TP) +" "+
			"fingertips along your " + location + ""+
			".", oblist, "", attrs);
			actor("You "+ gadv +" trace your fingertips "+
			"along", oblist, "'s " + location + ".",);
			all2act(" "+ gadv +" traces "+ HIS(TP) +" "+
			"fingertips along", oblist, "'s " + location + ""+
			".", "", attrs,);
			return 1;
			
			default:
			notify_fail("Gctrace whom [where / how]?\n");
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
		notify_fail("Gctrace whom [how / where]?\n");
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
gcwarn(string str)
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

	notify_fail("Warn who?\n");
	return 0;
    }

    actor("You warn", oblist, " that if " +
          ((sizeof(oblist) > 1) ? "they continue" :
              (oblist[0]->query_pronoun() + " continues")) +
          " in such a manner you will be forced to settle this " +
          "in a gentlemanly fashion, and " +
          ((sizeof(oblist) > 1) ? "they" : oblist[0]->query_pronoun()) +
          " will be punished throughly.");
    all2act(" warns", oblist, " that if " +
            ((sizeof(oblist) > 1) ? "they continue" :
                (oblist[0]->query_pronoun() + " continues")) +
            " in such a manner then " + this_player()->query_pronoun() +
            " will be forced to settle this in a gentlemanly fashion and " +
            ((sizeof(oblist) > 1) ? "they" : oblist[0]->query_pronoun()) +
            " will be punished thoroughly.");
    target(" warns you that if you continue in such a manner then " +
           this_player()->query_pronoun() + " will be forced to " +
           "settle this in a gentlemanly fashion, and that you will be " +
           "punished thoroughly.", oblist, "");

    return 1;
}

int
gcwave(string str)
{
    object *oblist;

    if (!stringp(str))
    {
	write("You wave slowly and charmingly.\n");
	allbb(" waves slowly and charmingly.");

	return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Wave at whom?\n");
        return 0;
    }

    actor("You wave slowly and charmingly in", oblist, "'s direction.", );
    all2actbb(" waves slowly and charmingly in", oblist, "'s direction.",);
    target(" waves slowly and charmingly in your direction.", oblist, "");

    return 1;
}
int
gcwipe(string str)
{
    object *oblist;
    if (!stringp(str))
    {
	write("You quickly wipe a tear from your eye.\n");
	allbb(" quickly wipes something away from " +
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

    actor("You gently wipe a tear from", oblist,"'s cheek.", );
    all2actbb(" gently wipes away something from", oblist, "'s cheek.", "",);
    target(" gently wipes away a tear that has fallen on your "+
      "cheek.", oblist,"");

    return 1;
}

public int
gchelp(string str)
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
