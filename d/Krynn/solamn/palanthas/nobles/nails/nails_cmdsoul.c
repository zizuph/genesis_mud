/*
 * The cmdsoul for having your nails done in Palanthas
 *
 * Mortis 01.2006
 */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <std.h>
#include "../../local.h"

inherit "/cmd/std/command_driver";

#define POINT_DIRECTIONS ({ "up", "down", "north", "south", "west", "east", \
    "northwest", "southwest", "northeast", "southeast" })

string length, style, colour, nail, nailstyle, linearstyle, parnail;

mapping nail_participle = (["nails":"nailed",
	"nail-claws":"nail clawed",
	"claws":"clawed",
	"talons":"taloned"]);

string
get_soul_id()
{
    return "Nails";
}

int
query_cmd_soul()
{
    return 1;
}

int
get_nail_details(object player)
{
	length = player->query_length();
	style = player->query_style();
	colour = player->query_colour();
	nail = player->query_nail();
	nailstyle = player->query_nailstyle();
	linearstyle = player->query_linear_nailstyle();
	parnail = nail_participle[nail];

	if (!interactive(player) || !length || !style || !colour || !nail)
		return 0;

	return 1; 
}

int
help(string str)
{
	if (!str)
		return 0;

	if (str == "nails" || str =="nail")
	{
		TP->more("You may do the following with your nails:\n"
		+ "nbeckon <player> (adv) - Beckon to someone.\n"
		+ "nbite (adv)            - Bite your nails.\n"
		+ "ncheek <player> (adv)  - Caress someone's cheek with your nails.\n"
		+ "nchin (adv)            - Scratch your chin contemplatively.\n"
		+ "nclean (adv)           - Clean your nails.\n"
		+ "ndrum <object> (adv)   - Drum your fingers.\n"
		+ "nfile (adv)            - File your nails.\n"
		+ "nfinger <player> (adv) - Show off one of your nails.\n"
		+ "nfold (adv)            - Fold your fingers in thought.\n"
		+ "ninspect (adv)         - Inspect your nails.\n"
		+ "nlift <player> (adv)   - Lift someone's chin with your nails.\n"
		+ "nneck <player> (adv)   - Draw an ear to ear smile on your neck.\n"
		+ "nno <player> (adv)     - Shake a finger no.\n"
		+ "npoint <player> (adv)  - Point a nail at someone.\n"
		+ "nscratch (adv)         - Perform a pleasant scratch.\n"
		+ "nshush <player> (adv)  - Shush someone.\n"
		+ "nsniff (adv)           - Sniff your nails.\n"
		+ "nswipe <player> (adv)  - Swipe your nails through the air.\n"
		+ "ntap <player> (adv)    - Tap someone's shoulder with your nails.\n"
		+ "ntear (adv)            - Tear off a damaged nail.\n"
		+ "ntrace <player> (adv)  - Trace the line of someone's jaw.\n"
		+ "ntrim  (adv)           - Trim your nails.\n");
		return 1;
	}
	return 0;
}

int
nbeckon(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "endearingly", 1);
	oblist = parse_this(how[0], "%l");

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{ 
		write("You beckon" + how[1] + " with your " + linearstyle + ".\n");
		allbb(" beckons" + how[1] + " with " + HIS(TP) + " "
		+ linearstyle + ".");
		return 1;
	}

	actor("You beckon", oblist, how[1] + " with your " + linearstyle + ".");
	target(" beckons you" + how[1] + " with " + HIS(TP) + " " + linearstyle
	+ ".", oblist);
	all2act(" beckons", oblist, how[1] + " with " + HIS(TP) + " "
	+ linearstyle + "."); 

	return 1;
}

int
nbite(string str)
{
	string *how;
	how = parse_adverb_with_space(str, "nervously", 0);

    if (!get_nail_details(TP))
	{
       NF("Some of your nailstyle is missing.  Strange that.\n");
       return 0;
    }

    write("You bite your " + linearstyle + how[1] + ".\n");
    allbb(" bites " + HIS(TP) + " " + linearstyle + how[1] + ".");
    return 1;
}

int
ncheek(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "gently", 1);
	oblist = parse_this(how[0], "[the] [cheek] [of] %l");

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{ 
		NF("Caress whose cheek?\n"); 
		return 0;
	}

	if (sizeof(oblist) > 1)
	{  
		NF("You can't caress the cheek of more than one person "
		+ "at once.\n"); 
		return 0;
	}

	actor("You caress", oblist, "'s cheek" + how[1] + " with the "
	+ "backs of your " + linearstyle + ".");
	target(" caresses your cheek" + how[1] + " with the backs of " + HIS(TP)
	+ " " + linearstyle + ".", oblist);
	all2act(" caresses the cheek of", oblist, how[1] + " with "
	+ HIS(TP) + " " + linearstyle + "."); 

	return 1;
}

int
nchin(string str)
{
	string *how;
	how = parse_adverb_with_space(str, "contemplatively", 0);

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	write("You scratch your chin" + how[1] + " with your "
	+ linearstyle + ".\n");
	allbb(" scratches " + HIS(TP) + " chin" + how[1] + " with "
	+ HIS(TP) + " " + linearstyle + ".");
	return 1;
}

int
nclean(string str)
{
	string *how, wname, lstyle;
	object *weapon = TP->query_weapon(-1);
	how = parse_adverb_with_space(str, "thoroughly", 0);
	wname = "nailfile";
	lstyle = length + " " + colour + " " + nail;

    if (!get_nail_details(TP))
	{
       NF("Some of your nailstyle is missing.  Strange that.\n");
       return 0;
    }

	if (sizeof(weapon) > 0)
	{
		wname = weapon[0]->short();
	}	

	if (style == "rotting")
	{
		write("You clean your " + lstyle + how[1] + " with your "
		+ wname + " dislodging a shred of rotting flesh.\nA shred of "
		+ "rotting flesh falls to the ground with a sick \""
		+ one_of_list(({"Splick", "Splish", "Splush", "Pwick"})) + "\""
		+ " sound.\n");
		allbb(" cleans " + HIS(TP) + " " + lstyle + how[1] + " with "
		+ HIS(TP) + " " + wname + " dislodging a shred of rotting flesh.\n"
		+ "A shred of rotting flesh falls to the ground with a sick \""
		+ one_of_list(({"Splick", "Splish", "Splush", "Pwick"})) + "\""
		+ " sound.\n");
		return 1;
	}

	write("You clean your " + linearstyle + how[1] + " with your "
	+ wname + ".\n");
	allbb(" cleans " + HIS(TP) + " " + linearstyle + how[1] + " with "
	+ HIS(TP) + " " + wname + ".");
	return 1;
}

int
ndrum(string str)
{
	string *how;
	object *oblist;

	if (!str)
	{
		NF("On what would you like to drum your nails?\n");
		return 0;
	}

	how = parse_adverb_with_space(str, "idly", 1);
	oblist = parse_this(how[0], "[my] [nails] [nail] [nail-claws] [claws] [talons] [on] %i", 0, 1);

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (sizeof(oblist) > 1)
	{  
		NF("You can't drum your nails on more than one object at "
		+ "a time.\n"); 
		return 0;
	}

	if (E(TP)->item_id(how[0]))
	{
		write("You drum your " + linearstyle + " upon the " + how[0]
		+ how[1] + ".\n");
		say(QCTNAME(TP) + " drums " + HIS(TP) + " " + linearstyle + " upon "
		+ "the " + how[0] + how[1] + ".\n");
		return 1;
	}

	NF("You don't find any " + how[0] + " upon which to drum your "
	+ "nails.\n");
	return 0;
}

int
nfile(string str)
{
	string *how;
	how = parse_adverb_with_space(str, "patiently", 0);

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	write("You procure your cedar nailfile and attend" + how[1] + " to your "
	+ linearstyle + ", filing them with a practiced hand.\n");
	allbb(" procures a nailfile and with a practiced hand files " + HIS(TP)
	+ " " + linearstyle + how[1] + ".");
	return 1;
}

int
nfinger(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "slowly", 1);
	oblist = parse_this(how[0], "%l");

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{ 
		write("You" + how[1] + " extend your middle finger to better "
		+ "display your " + nailstyle + ".\n");
		allbb(how[1] + " extends " + HIS(TP) + " middle finger to better "
		+ "display " + HIS(TP) + " " + nailstyle + ".");
		return 1;
	}

	actor("You" + how[1] + " extend your middle finger to", oblist, " that "
	+ "all may better view your " + nailstyle + ".");
	target(how[1] + " extends " + HIS(TP) + " middle finger to you "
	+ "providing an unimpeded view of " + HIS(TP) + " " + nailstyle
	+ " and leaving no doubt as to " + HIS(TP) + " opinion of you.", oblist);
	all2act(how[1] + " extends " + HIS(TP) + " middle finger to", oblist,
	  " providing an unimpeded view of " + HIS(TP) + " " + nailstyle
	+ " and leaving no doubt as to " + HIS(TP) + " opinion of the "
	+ "situation."); 

	return 1;
}

int
nfold(string str)
{
	string *how;
	how = parse_adverb_with_space(str, "monotonously", 0);

    if (!get_nail_details(TP))
	{
       NF("Some of your nailstyle is missing.  Strange that.\n");
       return 0;
    }

    write("You fold your " + linearstyle + " together" + how[1]
	+ " as you contemplate the matter.\n");
    allbb(" folds " + HIS(TP) + " " + linearstyle + " together" + how[1]
	+ " as " + HE(TP) + " contemplates the matter.");
    return 1;
}

int
ninspect(string str)
{
	string *how;
	how = parse_adverb_with_space(str, "devotedly", 0);

    if (!get_nail_details(TP))
	{
       NF("Some of your nailstyle is missing.  Strange that.\n");
       return 0;
    }

    write("You inspect your " + length + " " + colour + " " + nail + how[1]
	+ ", satisfied with their " + style + " appearance.\n");
    allbb(" inspects " + HIS(TP) + " " + length + " " + colour + " "
	+ nail + how[1] + ", satisfied with their " + style + " appearance.");
    return 1;
}

int
nlift(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "contemplatively", 1);
	oblist = parse_this(how[0], "[the] [chin] [of] %l");

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{ 
		NF("Lift whose chin?\n");
		return 0;
	}

	if (sizeof(oblist) > 1)
	{  
		NF("You can't lift the chin of more than one person "
		+ "at once.\n"); 
		return 0;
	}

	actor("You lift", oblist, "'s chin" + how[1] + " with one of your "
	+ linearstyle + ".");
	target(" lifts your chin" + how[1] + " with one of " + HIS(TP)
	+ " " + linearstyle + ".", oblist);
	all2act(" lifts the chin of", oblist, how[1] + " with one of "
	+ HIS(TP) + " " + linearstyle + "."); 

	return 1;
}

int
nneck(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "forebodingly", 1);
	oblist = parse_this(how[0], "%l");

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{ 
		write("You slowly trace your " + nailstyle + " across your neck"
		+ how[1] + ".\n");
		allbb(" slowly traces " + HIS(TP) + " " + nailstyle + " across "
		+ HIS(TP) + " neck" + how[1] + ".");
		return 1;
	}

	actor("You gaze" + how[1] + " at", oblist, " as you trace your "
	+ nailstyle + " across your neck from ear to ear slowly.");
	target(" gazes" + how[1] + " at you as " + HE(TP) + " traces " + HIS(TP)
	+ " " + nailstyle + " across " + HIS(TP) + " neck from ear to ear "
	+ "slowly.", oblist);
	all2act(" gazes" + how[1] + " at", oblist, " as " + HE(TP) + " traces "
	+ HIS(TP) + " " + nailstyle + " across " + HIS(TP) + " neck from ear "
	+ "to ear slowly.");
	return 1;
}

int
nno(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "decisively", 1);
	oblist = parse_this(how[0], "[at] %l");

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{ 
		write("You shake a " + style + " " + colour + " "
		+ parnail + " finger" + how[1] + " indicating, \"No\".\n");
		allbb(" shakes a " + style + " " + colour + " "
		+ parnail + " finger" + how[1] + " indicating, \"No\".");
		return 1;
	}

	actor("You shake a " + style + " " + colour + " "
	+ parnail + " finger" + how[1] + " at", oblist, " indicating, \"No\".");
	target(" shakes a " + style + " " + colour + " " + parnail
	+ " finger" + how[1] + " at you indicating, \"No\".", oblist);
	all2act(" shakes a " + style + " " + colour + " "
	+ parnail + " finger at", oblist, how[1] + " indicating, \"No\"."); 

	return 1;
}

int
npoint(string str)
{
	string *how, *tmp;
    object *oblist;
	length = TP->query_length();
	style = TP->query_style();
	colour = TP->query_colour();
	nail = TP->query_nail();
	how = parse_adverb_with_space(str, "confidently", 1);

    NF("Where do you want to point with a " + style + " "
	+ colour + " " + parnail + " finger?\n");

    if (!stringp(how[0]))
    {
		write("You point" + how[1] + " in a general direction with a "
		+ style + " " + colour + " " + parnail + " finger.\n");
		allbb(" points" + how[1] + " in a general direction with a "
		+ style + " " + colour + " " + parnail + " finger.");
		return 1;
    }

    how[0] = lower_case(how[0]);
    if (member_array(how[0], POINT_DIRECTIONS) >= 0)
    {
        write("You point" + how[1] + " " + how[0] + " with a "
		+ style + " " + colour + " " + parnail + " finger.\n");
        allbb(" points" + how[1] + " " + how[0] + " with a "
		+ style + " " + colour + " " + parnail + " finger.");
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %i", 0, 1);

    if (!sizeof(oblist))
    {
        tmp = explode(how[0], " ");
        if (sizeof(tmp) > 1 && tmp[0] == "at")
            str = implode(tmp[1 .. sizeof(tmp) - 1], " ");
        oblist = FIND_STR_IN_OBJECT(how[0], environment(TP));
        if (!sizeof(oblist))
        {
            if (environment(TP)->item_id(how[0]))
            {
                write("You point" + how[1] + " at the " + how[0] + " with a "
				+ style + " " + colour + " " + parnail
				+ " finger.\n");
                allbb(" points" + how[1] + " at " + LANG_ADDART(how[0])
				+ " with a " + style + " " + colour + " "
				+ parnail + " finger.");
                return 1;
            }
            return 0;
        }

	if (oblist[0] != TP)
	{
	    write("You point at " + LANG_THESHORT(oblist[0]) + ".\n");
	    allbb(" points at " + LANG_THESHORT(oblist[0]) + ".");
	    return 1;
	}
    }

    if (oblist[0] == TP)
    {
        write("You point" + how[1] + " at yourself with a " + style + " "
		+ colour + " " + parnail + " finger.\n");
        allbb(" points" + how[1] + " at " + HIMSELF(TP) + " with a "
		+ style + " " + colour + " " + parnail + " finger.");
        return 1;
    }

    actor("You point" + how[1] + " at", oblist, " with a " + style + " "
	+ colour + " " + parnail + " finger.");
    all2actbb(" points" + how[1] + " at", oblist, " with a " + style + " "
	+ colour + " " + parnail + " finger.");
    targetbb(" points" + how[1] + " at you with a " + length + " "
	+ style + " " + colour + " " + parnail + " finger.", oblist);
    return 1;
}

int
nscratch(string str)
{
	string *how;
	how = parse_adverb_with_space(str, "demandingly", 0);

    if (!get_nail_details(TP))
	{
       NF("Some of your nailstyle is missing.  Strange that.\n");
       return 0;
    }

    write("You plunge your " + linearstyle + how[1] + " into your butt, "
	+ "scratching it until sated.\n");
    allbb(" plunges " + HIS(TP) + " " + linearstyle + how[1] + " into "
	+ HIS(TP) + " butt, scratching it until sated.");
    return 1;
}

int
nshush(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "clinically", 1);
	oblist = parse_this(how[0], "%l");

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{ 
		NF("Who would you like to shush?\n");
		return 0;
	}

	actor("You place a " + style + " " + colour + " " + parnail
	+ " finger over your lips and shush", oblist, how[1] + ".");
	target(" places a " + style + " " + colour + " " + parnail
	+ " finger over " + HIS(TP) + " lips and shushes you" + how[1]
	+ ".", oblist);
	all2act(" places a " + style + " " + colour + " " + parnail
	+ " finger over " + HIS(TP) + " lips and shushes", oblist, how[1]
	+ "."); 
	return 1;
}

int
nsniff(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "curiously", 1);
	oblist = parse_this(lower_case(how[0]), "%l");

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{
		write("You lift your " + nailstyle + " to your nose, sniffing them"
		+ how[1] + " to determine where they've been, and you know where "
		+ "that is.\n");
		allbb(" lifts " + HIS(TP) + " " + nailstyle + " to " + HIS(TP)
		+ " nose, sniffing them" + how[1] + " to determine where they've "
		+ "been.  Judging by the expression on " + HIS(TP) + " face, you "
		+ "believe you know as well.");
		return 1;
    }

	if (sizeof(oblist) > 1)
	{
		NF("Whose nails would you like to sniff?  Pick one person.\n"); 
		return 0;
	}

	if (!get_nail_details(oblist[0]))
	{
		actor("You smell", oblist, "'s fingers" + how[1] + " in an attempt "
		+ "to ascertain where they've been recently, and you think you know "
		+ "now.");
		target(" smells your fingers" + how[1] + " in an attempt "
		+ "to ascertain where they've been recently, and you know where that "
		+ "is.", oblist);
		all2act(" smells", oblist, "'s fingers" + how[1] + " in an attempt "
		+ "to ascertain where they've been recently.  Judging by the "
		+ "expression on " + HIS(TP) + " face, you believe you know as "
		+ "well.");
		get_nail_details(TP);
		return 1;
	}
	
	actor("You smell", oblist, "'s " + length + " " + style + " "
	+ colour + " " + nail + how[1] + " in an attempt to ascertain where "
	+ "they've been recently, and you think you know now.");
	target(" smells your " + length + " " + style + " "
	+ "colour" + " " + nail + how[1] + " in an attempt to ascertain where "
	+ "they've been recently, and you know where that is.", oblist);
	all2act(" smells", oblist, "'s " + length + " " + style + " "
	+ colour + " " + nail + how[1] + " in an attempt to ascertain where "
	+ "they've been recently.  Judging by the expression on " + HIS(TP)
	+ " face, you believe you know as well.");
	get_nail_details(TP);
	return 1;
}

int
nswipe(string str)
{
	string *how, sound;
	object *oblist;
	how = parse_adverb_with_space(str, "in a deadly arc", 1);
	oblist = parse_this(how[0], "[at] %l");
	sound = one_of_list(({"whoosh of air", "whistling sound",
		"swish of air", "swooshing noise"}));

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{ 
		write("You swipe your " + linearstyle + " through the air"
		+ how[1] + ".\n");
		allbb(" swipes " + HIS(TP) + " " + linearstyle + " through the air"
		+ how[1] + ".\n");
		return 1;
	}

	if (sizeof(oblist) > 1)
	{  
		NF("You can't swipe at more than one person at once.\n"); 
		return 0;
	}

	actor("You swipe your " + linearstyle + how[1] + " in front of", oblist,
	  "'s face with a " + sound + ".");
	target(" swipes " + HIS(TP) + " " + linearstyle + how[1] + " in front "
	+ "of your face with a " + sound + ".", oblist);
	all2act(" swipes " + HIS(TP) + " " + linearstyle + how[1] + " in front "
	+ "of", oblist, "'s face with a " + sound + "."); 

	return 1;
}

int
ntap(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "expectantly", 1);
	oblist = parse_this(how[0], "%l");

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{ 
		NF("Tap whose shoulder?\n");
		return 0;
	}

	actor("You tap", oblist, "'s shoulder" + how[1] + " with your "
	+ linearstyle + ".");
	target(" taps your shoulder" + how[1] + " with " + HIS(TP) + " "
	+ linearstyle + ".", oblist);
	all2act(" taps", oblist, "'s shoulder" + how[1] + " with " + HIS(TP) + " "
	+ linearstyle + "."); 

	return 1;
}

int
ntear(string str)
{
	string *how;
	how = parse_adverb_with_space(str, "savagely", 0);

    if (!get_nail_details(TP))
	{
       NF("Some of your nailstyle is missing.  Strange that.\n");
       return 0;
    }

    write("You discover one of your " + style + " " + nail + " too far gone "
	+ "to repair.  You tear it off your finger completely and toss it into "
	+ "your mouth, crunching it between your teeth" + how[1] + ".\n");
    allbb(" discovers one of " + HIS(TP) + " " + style + " " + nail
	+ " too far gone to repair.\n" + C(HE(TP)) + " tears it off " + HIS(TP)
	+ " finger completely and tosses it into " + HIS(TP) + " mouth, "
	+ "crunching it between " + HIS(TP) + " teeth" + how[1] + ".");
    return 1;
}

int
ntrace(string str)
{
	string *how;
	object *oblist;
	how = parse_adverb_with_space(str, "sensually", 1);
	oblist = parse_this(how[0], "[the] [jaw] [of] %l");

    if (!get_nail_details(TP))
	{
		NF("Some of your nailstyle is missing.  Strange.\n");
		return 0;
	}

	if (!sizeof(oblist))
	{ 
		NF("Trace whose jaw?\n");
		return 0;
	}

	if (sizeof(oblist) > 1)
	{  
		NF("You can't trace the jaw of more than one person "
		+ "at once.\n"); 
		return 0;
	}

	actor("You trace the outline of", oblist, "'s jaw" + how[1] + " with your "
	+ style + " " + colour + " " + parnail + " fingers.");
	target(" traces the outline of your jaw" + how[1] + " with "
	+ HIS(TP) + " " + style + " " + colour + " " + parnail
	+ " fingers.", oblist);
	all2act(" traces the outline of", oblist, "'s jaw" + how[1] + " with "
	+ HIS(TP) + " " + style + " " + colour + " " + parnail
	+ " fingers."); 

	return 1;
}

int
ntrim(string str)
{
	string *how, wname, lstyle;
	object *weapon = TP->query_weapon(-1);
	how = parse_adverb_with_space(str, "precisely", 0);
	wname = "clippers";
	lstyle = length + " " + colour + " " + nail;

    if (!get_nail_details(TP))
	{
       NF("Some of your nailstyle is missing.  Strange that.\n");
       return 0;
    }

	if (sizeof(weapon) > 0)
	{
		wname = weapon[0]->short();
	}	

	write("You trim your " + linearstyle + how[1] + " with your "
	+ wname + ".\n");
	allbb(" trims " + HIS(TP) + " " + linearstyle + how[1] + " with "
	+ HIS(TP) + " " + wname + ".");
	return 1;
}

mapping
query_cmdlist()
{
    return
    ([
        "help":"help",
		"nbeckon":"nbeckon",
        "nbite":"nbite",
        "ncheek":"ncheek",
        "nchin":"nchin",
        "nclean":"nclean",
        "ndrum":"ndrum",
        "nfile":"nfile",
        "nfinger":"nfinger",
		"nfold":"nfold",
        "ninspect":"ninspect",
		"nlift":"nlift",
		"nneck":"nneck",
        "nno":"nno",
        "npoint":"npoint",
        "nscratch":"nscratch",
        "nshush":"nshush", 
        "nsniff":"nsniff",
		"nswipe":"nswipe",
		"ntap":"ntap",
		"ntear":"ntear",
		"ntrace":"ntrace",
		"ntrim":"ntrim"
    ]);
}
