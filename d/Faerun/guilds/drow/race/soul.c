/*
 * drow/race/soul.c
 *
 * The guild soul for the drow racial guild.
 *
 * Added faerie fire spell - Arman December 2016
 */
#pragma no_clone
#pragma no_inherit
#pragma no_shadow
#pragma strict_types

#include "guild.h"
#include <cmdparse.h>
#include <options.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

/* For adding 'emotion' messages to players descs */
#ifndef SOULDESC
#  define SOULDESC(x)	(this_player()->add_prop("_live_s_soulextra", (x)))
#endif

/* Different messengers available for drow */
#define SAY_HOW ({"hisses", "mutters", "says", "seethes", "murmurs", \
    "utters", "jeers", "cackles" })

/* Used in f_drsay() */
private string *drow_syllables = ({
   "a", "aer", "aerth", "ahn", "alu", "argt", "aul", "aut", "ayn", "chra", "dos", "drav", "druc", "eb", "elg", "eyd", "fyr", "golth", "hal", "har", "haun", "hinn", "hru", "hyr", "hyrr", "ii", "ilm", "iln", "im", "iz", "ji", "jiv'", "ka", "kli", "kre", "lae", "laen", "lamph", "lem", "loe", "lu", "mal", "mri", "mzil", "nau", "ne", "nglo", "nin", "nint", "ob", "ol", "ol", "op", "oss", "qu", "qu'", "qua", "quar", "rag", "rath", "ril", "ror", "shri", "sig", "sol", "srin", "ssin", "ssri", "sta", "sul", "suul", "tha", "thra", "tir", "tlu", "tlu", "tuem", "tym", "uel", "ui", "uil", "ulg", "uln", "uss", "ust", "vek", "vel", "yat", "z'", "zil", "zist", "zre", });


public int
query_cmd_soul(void)
{
    return 1;
}

public string
get_soul_id(void)
{
    return "drow_racial";
}

/*
 * Add commands in alpha order by category.
 * Function names should be prefixed as follows:
 *    f_  == General command function
 *    e_  == Guild emotes.
 */
public mapping
query_cmdlist(void)
{
    return ([
           /* SPELLS */
   "qunnessaachath": "do_ability",  
          /* COMMANDS */
       "drhelp" : "f_drhelp",
       "drlist" : "f_drlist",
        "drsay" : "f_drsay",
          "drs" : "f_drs",
           /* EMOTES */
        "drack" : "e_dracknow",
     "dracknow" : "e_dracknow",
     "dramused" : "e_dramused",
      "dranger" : "e_dranger",
     "drbeckon" : "e_drbeckon",
        "drbow" : "e_drbow",
      "drcross" : "e_drcross",
    "drcurtsey" : "e_drcurtsey",
      "drdeath" : "e_drdeath",
        "drdis" : "e_drdismiss",
    "drdisgust" : "e_drdisgust",
    "drdismiss" : "e_drdismiss",
   "dreyelower" : "e_dreyelower",
   "dreyeraise" : "e_dreyeraise",
       "drgaze" : "e_drgaze",
      "drglare" : "e_drglare",
    "drgrimace" : "e_drgrimace",
       "drhand" : "e_drhand",
       "drhowl" : "e_drhowl",
      "drlaugh" : "e_drlaugh",
       "drlust" : "e_drlust",
     "drmalice" : "e_drmalice",
     "drnarrow" : "e_drnarrow" ,
        "drnod" : "e_drnod",
      "drpeace" : "e_drpeace",
   "drpleasure" : "e_drpleasure",
    "drrespect" : "e_drrespect",
       "drroar" : "e_drroar",
   "drrolleyes" : "e_drrolleyes",
     "drscream" : "e_drscream",
       "drslit" : "e_drslit",
      "drsmile" : "e_drsmile",
      "drsnarl" : "e_drsnarl",
      "drsneer" : "e_drsneer",
      "drstoic" : "e_drstoic",
      "drthink" : "e_drthink",
      "drwatch" : "e_drwatch",
     /* Drow Language Emotes */
      "drcurse" : "e_drcurse",
    "drdestiny" : "e_drdestiny",
       "drfare" : "e_drfarewell", /* Short form */
   "drfarewell" : "e_drfarewell",
      "drgreet" : "e_drgreet",
       "droath" : "e_droath",
       "drrude" : "e_drrude",
    ]);
}

public mapping
query_ability_map()
{
    return ([
        "qunnessaachath"    : SPELLS_DIR + "faerie_fire",
    ]);
}

/*
 * This is used constantly, so simplify its usage.
 */
#define OBERROR(str) if (!sizeof(oblist)) { \
	    if (strlen(parse_msg)) { write(parse_msg); return 1; } \
	    return notify_fail(str);  }


/*************************************************************************
 * C O M M A N D S
 */

/* Used to parse and display the helpfiles. */
public int
f_drhelp(string str)
{
    string file;

    setuid();
    seteuid(getuid());

    if (!strlen(str))
	str = "index";
    else
	str = lower_case(str);

    file = sprintf("%s%s", GUILD_HELP, str);
    if (file_size(file) > 0)
	return TI->more(read_file(file), 0);

    write("Unfortunaly, there is no help on that subject.\n");
    return 1;
}

private int
display_ranks(void)
{
    write("  This is a list of Available Drow ranks and their more "+
	"functional form:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    foreach(string key, mixed data : DROW_RANKS)
	write(sprintf("    %20s  ( %-:8s )\n", data[0], key));

    write("\n");
    return 1;
}

/*
 * Prints out a list of online members.
 * string str = Limit the display to a certain rank of drow.
 */
public int
f_drlist(string str)
{
    int type, size, ix;
    mixed *arr1, *arr2;

    /* this should maybe be simplified and just show all drow. */
    /* May not even want this command at all, or restrict it
     * to only displaying memebers of the same house. */
    switch(str)
    {
    case "ranks":     return display_ranks(); break;
    case "house":     type = HOUSE_MEMBER;    break;
    case "noble":     type = HOUSE_NOBLE;     break;
    default:          type = GUILD_MEMBER;    break;
    }

    arr1 = filter(users() - ({ TI }),
      &operator(==)(GUILD_NAME) @ &->query_guild_name_race());

    /* Filter out wizards. */
    if (!TP->query_wiz_level() && (TP->query_real_name()[-2..] != "jr"))
	arr1 = filter(arr1, not @ &->query_wiz_level());

    if (!sizeof(arr1))
    {
	write("You have an inkling that you are the only drow roaming about.\n");
	return 1;
    }

    arr2 = (string *)GSERVER->query_members(1, type) -
			({ TI->query_real_name() });

    if (!sizeof(arr2))
    {
	write("You have an inkling that there are no drow "+
	  "of that caliber roaming about.\n");
	return 1;
    }

    arr2 = sort_array(map(arr1, &->query_real_name()) & arr2);

    if (!(size = sizeof(arr2)))
    {
	write("You have an inkling that you are the only drow "+
	  "roaming about.\n");
	return 1;
    }

    write("You have an inkling that the following drow are "+
      "roaming about the realms:\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"+
      "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    ix = -1;
    while(++ix < size)
    {
	write(sprintf("%-s %-s\n", CAP(arr2[ix]),
	    find_player(arr2[ix])->query_guild_title_race()));
    }

    return 1;
}

/*
 * Replaces words with a random melange of drowish syllables.
 */
private string
drsay_replace(string str)
{
    string word = "";
    int syllables, ix;

    syllables = strlen(str);
    syllables = (syllables + random(syllables)) / 3;

    if (!syllables) syllables = 1;

    for (ix = 0; ix < syllables; ix++)
	word += one_of_list(drow_syllables);

    /* Retain Capitalization */
    if (str == capitalize(str))
	word = capitalize(word);

    /* Retain punctuation */
    switch(str[-1..])
    {
    case ".": case ",": case "?": case "!":
	word += str[-1..];
        break;
    }
    return word;
}

public int
f_drsay(string str)
{
    int size;
    mixed tmp;
    object *people, *notrans;
    string say_how = one_of_list(SAY_HOW);

    if (!strlen(str))
    {
	notify_fail("What is it you wish to say in the drow tongue?\n");
	return 0;
    }

    if (tmp = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if (strlen(tmp))
	    write(tmp);
	else
	    write("You seem unable to use your mouth at this time.\n");

	return 1;
    }

    if (TP->query_option(OPT_ECHO))
	TP->catch_tell("You say in the drow tongue: "+ str +"\n");
    else
	TP->catch_tell("Ok.\n");

    people = filter(all_inventory(environment(TP)), interactive) - ({ TP });
    if (!sizeof(people))
	return 1;

    /* Wizzies and Drow don't need to go through the conversion. */
    notrans = filter(people, &->query_wiz_level());
    notrans += filter(people, &operator(==)(GUILD_NAME) @
				&->query_guild_name_race());

    size = sizeof(notrans);
    while(size--)
    {
	notrans[size]->catch_tell(TP->query_The_name(notrans[size]) +
	    " " + say_how + " in the drow tongue: "+ str +"\n");
    }

    if (size = sizeof(people -= notrans)) do
    {
	string *arr, *drow_arr;
	int lang = people[--size]->query_skill(SS_LANGUAGE);

	arr = explode(str, " ");
	drow_arr = map(arr, drsay_replace);

	switch(lang)
	{
	case 0..25:
	    people[size]->catch_tell(
		TP->query_The_name(people[size]) +
		" " + say_how + " in a strange language: "+
		implode(drow_arr, " ") +"\n");
	    break;
	case 26..40:
	    people[size]->catch_tell(
		TP->query_The_name(people[size]) +
		" " + say_how + " in a drowish dialect: "+
		implode(drow_arr, " ") +"\n");
	    break;
	default:
	{
	    string drow_str = "";
	    int ix, sz = sizeof(arr);

	    for (ix = 0; ix < size; ix++)
	    {
		if ((random(lang) + 1) < 40)
		    drow_str += arr[ix] + " ";
		else
		    drow_str += drow_arr[ix] + " ";
	    }

	    people[size]->catch_tell(
		TP->query_The_name(people[size]) +
		" " + say_how + " in a drowish dialect: "+ drow_str + "\n");
	}
	    break;
	}
    } while(size);

    return 1;
}

public int
f_drs(string str)
{
    string tmp;
    int attr = ACTION_VISUAL | ACTION_AURAL;

    if (!strlen(str))
	return notify_fail("Sneer what?\n");

    if (tmp = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if (strlen(tmp))
	    write(tmp);
	else
	    write("You seem unable to use your mouth at this time.\n");

	return 1;
    }

    if (TP->query_option(OPT_ECHO))
	write("You sneer: "+ str +"\n");
    else
	write("Ok.\n");

    allbb(" sneers: "+ str);
    return 1;
}

/*************************************************************************
 * E M O T E S
 */

/* This is a helper function to use the Gelan eyeshadow */
private varargs string
check_eyes(object who = this_interactive())
{
    switch(who->query_eyes_number())
    {
    case 1:
	return " single "+ who->query_eyes() +" eye";
	break;
    case 2:
	return " "+ who->query_eyes() +" eyes";
	break;
    default:
	return " eyes";
	break;
    }
}

public int
e_dracknow(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if(!strlen(str))
    {
	write("You signal your acknowledgement with a barely "+
	    "noticeable nod.\n");
	allbb(" signals " + HIS(TP) +
	    " acknowledgement with a barely noticeable nod.", "", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drack [at] / [to] [the] who/what?\n");

    actor("You signal your acknowledgement with a barely noticable nod at",
	oblist);
    all2actbb(" signals " + HIS(TP) +
	" acknowledgement with a barely noticable nod at",
	oblist, "", "", attr);
    targetbb(" signals " + HIS(TP) +
	" acknowledgement with a barely noticable nod at you.",
	oblist, "", attr);

    return 1;
}

public int
e_dramused(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if(!strlen(str))
    {
	write("Your burning gaze flickers with amusement and your lips " +
	    "twist in a condescending smirk.\n");
	allbb("'s burning gaze flickers with amusement and " + HIS_HER(TP) +
	    " lips twist in a condescending smirk.", "amusedly", attr);
	SOULDESC("greatly amused about something");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Dramused [at] / [to] [the] who/what?\n");
    SOULDESC("greatly amused about something");

    actor("You turn your burning gaze directly at", oblist, " and " +
	"your lips twist in a condescending smirk of amusement.");
    all2actbb(" turns " + HIS(TP) + " burning gaze directly at", oblist,
	" and " + HIS(TP) + " lips twist in a condescending smirk " +
	"of amusement.", "amusedly", attr);
    targetbb(" turns " + HIS(TP) + " burning gaze directly at you and " +
	HIS(TP) + " lips twist in a condescending smirk of amusement",
	oblist, "amusedly", attr);

    return 1;
}

public int
e_dranger(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_THREATENING;

    if (!strlen(str))
    {
	write("You look around the area with burning anger evident "+
	   "on your face.\n");
	allbb(" looks around the area with burning anger evident "+
	    "on "+ HIS(TP) +" face.", "angrily", attr);
	SOULDESC("looking around angrily");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Dranger [at] / [to] [the] who/what?\n");
    SOULDESC("looking around with intense, burning anger");

    actor("You look at", oblist, " with an intense, burning anger.");
    all2actbb(" looks at", oblist, " with an intense, burning anger.",
	"angrily", attr);
    targetbb(" looks at you with an intense, burning anger.",
	oblist, "angrily", attr);

    return 1;
}

public int
e_drbeckon(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;
    string *how, eyes = check_eyes();

    how = parse_adverb_with_space(str, "dangerously", 1);

    if (!strlen(how[0]))
    {
	write("You beckon everyone to step closer, your" + eyes +
	    " gleaming " + how[1] + ".\n");
	allbb(" beckons everyone to step closer, " + HIS(TP) + eyes +
	    " gleaming " + how[1] + ".", how[1], attr);
	return 1;
    }

    oblist = parse_this(how[0], "[at] / [to] [the] %l", attr);
    OBERROR("Drbeckon [at] / [to] [the] who/what?\n");

    actor("You beckon", oblist, " to step closer, your" + eyes +
	" gleaming" + how[1] + ".");
    all2actbb(" beckons", oblist, " to step closer, " + HIS(TP) + eyes +
	" gleaming" + how[1] + ".", how[1], attr);
    targetbb(" beckons you to step closer, " + HIS(TP) + eyes +
	" gleaming" + how[1] + ".", oblist, how[1], attr);

    return 1;
}

public int
e_drbow(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You bow with feline grace and poise, eyes wary "+
	    "and untrusting.\n");
	allbb(" bows with feline grace and poise, eyes wary "+
	    "and untrusting.", "gracefully", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drbow [at] / [to] [the] who/what?\n");

    actor("You bow with a feline grace and poise before", oblist,
	", eyes wary and untrusting.");
    all2actbb(" bows with feline grace and poise before", oblist,
	", eyes wary and untrusting.", "gracefully", attr);
    targetbb(" bows with feline grace and poise before you, "+
	"eyes wary and untrusting.", oblist, "gracefully", attr);

    return 1;
}

public int
e_drcross(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You cross your arms across your chest, "+
	   " with a slow yet balanced movement.\n");
	allbb(" crosses " + HIS(TP) + " arms across " + HIS(TP) +
	    " chest, with a slow yet balanced movement.", "", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drcross [at] / [to] [the] who/what?\n");

    actor("You cross your arms across your chest, "+
       "with a slow yet balanced movement, never letting your gaze leave",
       oblist);
    all2actbb(" crosses " + HIS(TP) + " arms across " + HIS(TP) +
	" chest, with a slow yet balanced movement, never letting " +
	HIS(TP) + " gaze leave", oblist, "", "", attr);
    targetbb(" crosses " + HIS(TP) + " arms across " + HIS(TP) +
	" chest, with a slow yet balanced movement, never letting " +
	HIS(TP) + " gaze leave you.", oblist, "", attr);

    return 1;
}

public int
e_drcurtsey(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You curtsey with feline grace and poise, eyes wary "+
	    "and untrusting.\n");
	allbb(" curtseys with feline grace and poise, eyes wary"+
	   " and untrusting.", "gracefully", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drcurtsey [at] / [to] [the] who/what?\n");

    actor("You curtsey with a feline grace and poise before", oblist,
	", eyes wary and untrusting.");
    all2actbb(" curtseys with feline grace and poise before", oblist,
	", eyes wary and untrusting.", "gracefully", attr);
    targetbb(" curtseys with feline grace and poise before you, "+
	"eyes wary and untrusting.", oblist, "gracefully", attr);

    return 1;
}

public int
e_drdeath(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_THREATENING;

    if (!strlen(str))
    {
	write("You swear that someone will suffer a slow and "+
	    "excruciatingly painful death.\n");
	allbb(" promises to make someone suffer a slow and "+
	    "excruciatingly painful death.", "", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drdeath [at] / [to] [the] who/what?\n");

    actor("You promise", oblist, " a slow and excruciatingly "+
	"painful death.");
    all2actbb(" promises", oblist, " a slow and excruciatingly "+
	"painful death.", "", attr);
    targetbb(" promises you a slow and excruciatingly painful death.",
	oblist, "", attr);

    return 1;
}

public int
e_drdismiss(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You turn your interest elsewhere and dismiss everyone "+
	    "with a slight wave of your hand.\n");
	allbb(" turns " + HIS(TP) + " interest elsewhere and dismisses " +
	    "everyone with a slight wave of " + HIS(TP) + " hand.",
	    "dismissively", attr);
	SOULDESC("showing obvious lack of interest");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drdis[miss] [at] / [to] [the] who/what?\n");
    SOULDESC("showing obvious lack of interest");

    actor("You turn your interest elsewhere and dismiss", oblist,
	" with a slight wave of your hand.");
    all2actbb(" turns " + HIS(TP) + " interest elsewhere and dismisses",
	oblist, "with a slight wave of " + HIS(TP) + " hand.",
	"dismissively", attr);
    targetbb(" turns " + HIS(TP) + " interest elsewhere and dismisses " +
	"you with a slight of " + HIS(TP) + " hand.",
	oblist, "dismissively", attr);

    return 1;
}

public int
e_drdisgust(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_OFFENSIVE;

    if (!strlen(str))
    {
	write("You display obvious abhorrence at the thought of the "+
	    "lands of terrible light.\n");
	allbb(" displays obvious abhorrence at the thought of the "+
	    "lands of terrible light.", "", attr);
	SOULDESC("displays obvious abhorrence");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drdisgust [at] / [to] [the] who/what?\n");
    SOULDESC("displays obvious abhorrence");

    actor("You display obvious abhorrence at", oblist,
	"'s horrid appearance.");
    all2actbb(" displays obvious abhorrence at", oblist,
	"'s horrid appearance.", "", attr);
    targetbb(" displays obvious abhorrence at your horrid appearance.",
	oblist, "", attr);

    return 1;
}

public int
e_drglare(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You glare around coldly and haughtily, "+
	    "secure in the knowledge of the superiority of the drow.\n");
	allbb(" glares around coldly and haughtily, "+
	    "secure in the knowledge of the superiority of the drow.",
	    "haughtily", attr);
	SOULDESC("glaring around coldly and haughtily");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drglare [at] / [to] [the] who/what?\n");
    SOULDESC("glaring around coldly and haughtily");

    actor("You glare at", oblist, " coldly and haughtily, "+
	"secure in the knowledge of the superiority of the drow.");
    all2actbb(" glares at", oblist, " coldly and haughtily, "+
	"secure in the knowledge of the superiority of the drow.",
	"haughtily", attr);
    targetbb(" glares at you coldly and haughtily, "+
	"secure in the knowledge of the superiority of the drow.",
	oblist, "haughtily", attr);

    return 1;
}

public int
e_drhowl(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_AURAL;

    if (!strlen(str))
    {
	write("You throw your head back and let out a blood-curdling "+
	    "howl of triumph!\n");
	allbb(" throws "+ HIS(TP) +" head back and lets out a "+
	    "blood-curdling howl of triumph!", "", attr);
	SOULDESC("howling in triumph");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drhowl [at] / [to] [the] who/what?\n");
    SOULDESC("howling in triumph");

    actor("You throw your head back as you stare at", oblist,
	" and let out a blood-curdling howl of triumph!");
    all2actbb(" throws "+ HIS(TP) +" head back as "+ HE(TP) +
	" stares at", oblist, " and lets out a blood-curdling "+
	"howl of triumph!", "", attr);
    targetbb(" throws "+ HIS(TP) +" head back as "+ HE(TP) +
	" stares at you and lets out a blood-curdling howl of triumph!",
	oblist, "", attr);

    return 1;
}

public int
e_drlaugh(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You laugh with malicious glee, eyes sparkling "+
	    "dangerously.\n");
	allbb(" laughs with malicious glee, eyes sparkling "+
	    "dangerously", "maliciously", attr);
	SOULDESC("laughing with malicious glee");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drlaugh [at] / [to] [the] who/what?\n");
    SOULDESC("laughing with malicious glee");

    actor("You laugh with malicious glee at", oblist,
	", eyes sparkling dangerously.");
    all2actbb(" laughs with malicious glee at", oblist,
	", eyes sparkling dangerously.", "maliciously", attr);
    targetbb(" laughs with malicious glee at you, "+
	"eyes sparkling dangerously.", oblist, "maliciously", attr);

    return 1;
}

public int
e_drrespect(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_INGRATIATORY;

    if (!strlen(str))
    {
	notify_fail("Drrespect [at] / [to] [the] who/what?\n");
	return 0;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drrespect [at] / [to] [the] who/what?\n");

    actor("You look at", oblist, " with the respect afforded a fellow "+
	"warrior.");
    all2actbb(" looks at", oblist, " with the respect afforded a fellow "+
	"warrior.", "respectfully", attr);
    targetbb(" looks at you with the respect afforded a fellow warrior.",
	oblist, "respectfully", attr);

    return 1;
}

public int
e_drscream(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_AURAL;

    if (!strlen(str))
    {
	write("You raise your arms and let out a scream of unbridled "+
	    "passion and rage!\n");
	all(" raises " + HIS(TP) + " arms and lets out a scream of "+
	    "unbridled passion and rage!", "", attr);
	SOULDESC("screaming with unbridled passion and rage");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drrespect [at] / [to] [the] who/what?\n");
    SOULDESC("screaming with unbridled passion and rage");

    actor("You grab", oblist, " roughly by the neck and scream with "+
	"unbridled rage!");
    all2act(" grabs", oblist, " roughly by the neck and screams with "+
	"unbridled rage!", "", attr);
    target(" grabs you roughly by the neck and screams with unbridled "+
	"rage!", oblist, "", attr);

    return 1;
}

public int
e_drsmile(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You smile without a trace of mercy.\n");
	allbb(" smiles without a trace of mercy.", "mercilessly", attr);
	SOULDESC("smiling coldly and without a trace of mercy");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drsmile [at] / [to] [the] who/what?\n");
    SOULDESC("smiling coldly and without a trace of mercy");

    actor("You smile without a trace of mercy at", oblist);
    all2actbb(" smiles without a trace of mercy at", oblist,
	"", "mercilessly", attr);
    targetbb(" smiles without a trace of mercy at you.",
	oblist, "mercilessly", attr);

    return 1;
}

public int
e_drsnarl(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You clench your jaw and curl your lip in a feral snarl.\n");
	allbb(" clenches "+ HIS(TP) +" jaw and curls "+ HIS(TP) +
	    " lip in a feral snarl.", "", attr);
	SOULDESC("gazing around with a feral snarl");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drsnarl [at] / [to] [the] who/what?\n");
    SOULDESC("gazing around with a feral snarl");

    actor("You clench your jaw and curl your lip at", oblist,
	" in a feral snarl.");
    all2actbb(" clenches "+ HIS(TP) +" jaw and curls "+ HIS(TP) +
	" lip at", oblist, " in a feral snarl.", "", attr);
    targetbb(" clenches "+ HIS(TP) +" jaw and curls "+ HIS(TP) +
	" lip at you with a feral snarl.", oblist, "", attr);

    return 1;
}

public int
e_drsneer(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_OFFENSIVE;

    if (!strlen(str))
    {
	write("You sneer in contempt of the weak-willed surface "+
	    "dwellers.\n");
	allbb(" sneers in contempt of the weak-willed surface dwellers.",
	    "contemptuously", attr);
	SOULDESC("sneering in contempt");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drsneer [at] / [to] [the] who/what?\n");
    SOULDESC("sneering in contempt");

    if (sizeof(oblist) > 1)
    {
	actor("You sneer in contempt at", oblist, ", a bunch of "+
	    "weak-willed surface dwellers.");
	all2actbb(" sneers in contempt at", oblist, ", a bunch of "+
	    "weak-willed surface dwellers.", "contemptuously", attr);
    } else {
	actor("You sneer in contempt of", oblist, ", a weak-willed "+
	    "surface dweller.");
	all2actbb(" sneers in contempt of", oblist, ", a weak-willed "+
	   "surface dweller.", "contemptuously", attr);
    }

    targetbb(" sneers in contempt of you, a weak-willed surface dweller.",
	oblist, "contemptuously", attr);

    return 1;
}

public int
e_drstoic(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You remain calm and completely undisturbed.\n");
	allbb(" remains calm and completely undisturbed.", "calmly", attr);
	SOULDESC("expressionless and calm");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drstoic [at] / [to] [the] who/what?\n");
    SOULDESC("expressionless and calm");

    actor("You look at", oblist, " with stoic reserve.");
    all2actbb(" looks at", oblist, " with stoic reserve.", "stoicly", attr);
    targetbb(" looks at you with stoic reserve.", oblist, "stoicly", attr);

    return 1;
}

public int
e_drmalice(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;
    string eyes = check_eyes();

    if (!strlen(str))
    {
    	write("You get a malicious gleam in your"+ eyes +".\n");
	allbb(" gets a malicious gleam in "+ HIS(TP) + eyes +".", "", attr);
	SOULDESC("glaring around maliciously");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drmalice [at] / [to] [the] who/what?\n");
    SOULDESC("glaring maliciously");

    actor("You glare at", oblist, " with a malicious gleam in "+
	"your"+ eyes + ".");
    all2actbb(" glares at", oblist, " with a malicious gleam in "+
	HIS(TP) + eyes +".", "", attr);
    targetbb(" glares at you with a malicious gleam in "+
	HIS(TP) + eyes +".", oblist, "", attr);
    return 1;
}

public int
e_drlust(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You let your gaze wander with lust-filled eyes.\n");
	allbb(" lets "+ HIS(TP) +" gaze wander with lust-filled eyes.",
	    "", attr);
	SOULDESC("gazing around with lust");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drlust [at] / [to] [the] who/what?\n");
    SOULDESC("gazing around with lust.");

    actor("You gaze directly at", oblist, " with lust-filled eyes.");
    all2actbb(" gazes directly at", oblist, " with lust-filled eyes.",
	"", attr);
    targetbb(" gazes directly at you with lust-filled eyes.",
	oblist, "", attr);
    return 1;
}

public int
e_drgaze(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You gaze around superciliously, the corner of your lip "+
	   " twitching into an amused smile.\n");
	allbb(" gazes around superciliously, the corner of " + HIS(TP) +
	      " lip twitching into an amused smile.", "superciliously", attr);
	SOULDESC("smiling with amusement");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drgaze [at] / [to] [the] who/what?\n");
    SOULDESC("smiling with amusement");

    actor("You gaze at", oblist, " superciliously, the corner of your lip "+
	"twitching into an amused smile.");
    all2actbb(" gazes at", oblist, " superciliously, the corner of "+ HIS(TP) +
	" lip twitching into an amused smile.", "superciliously", attr);
    targetbb(" gazes at you superciliously, the corner of "+ HIS(TP) +
	" lip twitching into an amused smile.", oblist, "superciliously", attr);
    return 1;
}

public int
e_drwatch(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_THREATENING;

    if (!strlen(str))
    {
	write("You watch your surroundings out of the corner of your eye, "+
	    "muscles tensing in anticipation of battle.\n");
	allbb(" is watching " + HIS(TP) + " surroundings out of the corner "+
	    "of "+ HIS(TP) +" eye, muscles tensing in anticipation of battle.",
	    "tensely", attr);
	SOULDESC("tensing in anticipation of battle");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drwatch [at] / [to] [the] who/what?\n");
    SOULDESC("tensing in anticipation of battle");

    actor("You watch", oblist, " out of the corner of your eye, muscles "+
	"tensing in anticipation of battle.");
    all2actbb(" tenses visibly, as if preparing to spring into battle with",
	oblist, ", a battle to the death.", "tensely", attr);
    targetbb(" is watching you out of the corner of "+ HIS(TP) +" eye, "+
	"muscles tensing in anticipation of battle.", oblist, "tensely", attr);
    return 1;
}

public int
e_drgrimace(string str)
{
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You grimace in frustration and spit on the ground in disgust.\n");
	allbb(" grimaces in frustration and spits on the ground in disgust.",
	    "", attr);
	SOULDESC("grimacing in frustration");
	return 1;
    }

    notify_fail("Just drgrimace, no argument needed.\n");
    return 0;
}

public int
e_drnarrow(string str)
{
    string *how;
    object *oblist;
    int attr = ACTION_VISUAL;
    string eyes = check_eyes();

    how = parse_adverb_with_space(str, "menacingly", 1);

    if (!strlen(how[0]))
    {
	write("You narrow your" + eyes + how[1] + " as you regard your "+
	    "surroundings with piercing scrutiny.\n");
	allbb(" narrows " + HIS(TP) + eyes + how[1] + " as " + HE(TP) +
	    " regards "+ HIS(TP) +" surroundings with piercing scrutiny.",
	    how[1], attr);
	SOULDESC("regarding the surroundings with piercing scrutiny");
	return 1;
    }

    oblist = parse_this(how[0], "[at] / [to] [the] %l", attr);
    OBERROR("Drnarrow [at] / [to] [the] who/what?\n");
    SOULDESC("regarding the surroundings with piercing scrutiny");

    actor("You narrow your" + eyes + " at" , oblist, how[1] +
	" and with piercing scrutiny.");
    all2actbb(" narrows " + HIS(TP) + eyes +" at", oblist, how[1] +
	" and with piercing scrutiny.","", attr);
    targetbb(" narrows " + HIS(TP) + eyes + " at you" + how[1] +
	" and with piercing scrutiny.", oblist, how[1], attr);
    return 1;
}

public int
e_drnod(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You tilt your head slightly in a sign of greeting.\n");
	allbb(" tilts "+ HIS(TP) +" head slightly in a sign of greeting.",
	    "slightly", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drnod [at] / [to] [the] who/what?\n");

    actor("You tilt your head slightly in a sign of greeting towards", oblist);
    all2actbb(" tilts "+ HIS(TP) +" head slightly in a sign of greeting towards",
	oblist, 0, "slightly", attr);
    targetbb(" tilts "+ HIS(TP) +" head slightly in a sign of greeting towards "+
       "you.", oblist, "slightly", attr);
    return 1;
}

public int
e_drpleasure(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You suddenly raise the ends of your lips in a wicked grimace "+
	    "of pleasure.\n");
	allbb(" suddenly raises the ends of " + HIS(TP) + " lips in a wicked " +
	    "grimace of pleasure.", "", attr);
	SOULDESC("grinning with wicked pleasure");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drpleasure [at] / [to] [the] who/what?\n");
    SOULDESC("grinning with wicked pleasure");

    actor("You suddenly raise the ends of your lips in a wicked grimace "+
	"of pleasure at", oblist);
    all2actbb(" suddenly raises the ends of "+ HIS(TP) +" lips in a wicked " +
	"grimace of pleasure at", oblist, 0, "", attr);
    targetbb(" suddenly raises the ends of "+ HIS(TP) +" lips in a wicked " +
	"grimace of pleasure at you.", oblist, "", attr);
    return 1;
}

public int
e_drpeace(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You spread your arms out wide in a courtly gesture of peace.\n");
	allbb(" spreads "+ HIS(TP) +" arms out wide in a courtly gesture of "+
	    "peace.", "courtly", attr);
	SOULDESC("appearing unnervingly peaceful");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drpeace [at] / [to] [the] who/what?\n");
    SOULDESC("appearing unnervingly peaceful");

    actor("You spread your arms out wide in a courtly gesture of peace towards",
	oblist);
    all2actbb(" spreads "+ HIS(TP) +" arms out wide in a courtly gesture of "+
	"peace towards", oblist, 0, "courtly", attr);
    targetbb(" spreads "+ HIS(TP) +" arms out wide in a courtly gesture of "+
	"peace towards you.", oblist, "courtly", attr);
    return 1;
}

public int
e_drroar(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_THREATENING;
    string eyes = check_eyes();

    if (!strlen(str))
    {
	write("Your" + eyes + " flash violently as you roar wrathfully!\n");
	allbb("'s" + eyes +" flash violently as "+ HE(TP) +" roars wrathfully!",
	    "wrathfully", attr);
	SOULDESC("roaring with uncontained wrath");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drroar [at] / [to] [the] who/what?\n");
    SOULDESC("roaring with uncontained wrath");

    actor("Your" + eyes + " flash violently as you roar at", oblist,
	" with uncontained wrath!");
    all2actbb(" roars with uncontained wrath at", oblist, " as "+ HIS(TP) +
	eyes + " flash violently.", "wrathfully", attr);
    targetbb("'s" + eyes + " flash violently as "+ HE(TP) +" roars "+
	"at you with uncontained wrath!", oblist, "wrathfully", attr);
    return 1;
}

public int
e_drthink(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;
    string eyes = check_eyes();

    if (!strlen(str))
    {
	write("You find a shadow and dive into thoughts with your"+ eyes +
	    " almost closed.\n");
	allbb(" finds a shadow and dives into thoughts with "+ HIS(TP) + eyes +
	    " almost closed.", "", attr);
	SOULDESC("seemingly lost in shadowy thoughts");
	return 1;
    }

    notify_fail("Drthink... that's all you need to do.\n");
    return 0;
}

public int
e_drrolleyes(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;
    string eyes = check_eyes();

    if (!strlen(str))
    {
	write("You roll your" + eyes + " at the obvious stupidity of "+
	    "the suggestion.\n");
	allbb(" rolls "+ HIS(TP) + eyes +" at the obvious stupidity of "+
	    "the suggestion.", "", attr);
	SOULDESC("annoyed at someone else's stupitity");
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drroll[eyes] [at] / [to] [the] who/what?\n");
    SOULDESC("annoyed at someone else's stupitity");

    actor("You roll your"+ eyes +" at the obvious stupidity of the "+
	"suggestion coming from", oblist);
    all2actbb(" rolls " + HIS(TP) + eyes +" at the obvious stupidity of the "+
	"suggestion coming from", oblist, 0, "", attr);
    targetbb(" rolls " + HIS(TP) + eyes + " at the obvious stupidity of the "+
	"suggestion coming from you.", oblist, "", attr);
    return 1;
}

public int
e_drslit(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_THREATENING;

    if (!strlen(str))
    {
	write("You slowly run a finger across your throat to express your "+
	    "obvious intention.\n");
	allbb(" slowly runs a finger across "+ HIS(TP) +
	    " throat to express "+ HIS(TP) +" obvious intention.", "", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drslit [at] / [to] [the] who/what?\n");

    actor("You slowly run your finger across your throat to express your "+
	"obvious intention to", oblist);
    all2actbb(" slowly runs a finger across "+ HIS(TP) +
	" throat to express "+ HIS(TP) +" obvious intention to",
	oblist, 0, "", attr);
    targetbb(" slowly runs a finger across "+ HIS(TP) +" throat to express " +
	      HIS(TP) + "obvious intention to you.", oblist, "", attr);
    return 1;
}

public int
e_drhand(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;

    if (!strlen(str))
    {
	write("You arrogantly raise your hand, palm facing outwards, "+
	    "indicating that you have heard enough.\n");
	allbb(" arrogantly raises "+ HIS(TP) +" hand, palm facing outwards, "+
	    "indicating that "+ HE(TP) +" has heard enough.", "arrogantly", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drhand [at] / [to] [the] who/what?\n");

    actor("You arrogantly raise your hand, palm facing", oblist,
	", indicating that you have heard enough.");
    all2actbb(" arrogantly raises "+ HIS(TP) +" hand, palm facing", oblist ,
	", indicating that "+ HE(TP) +" has heard enough.", "arrogantly", attr);
    targetbb(" arrogantly raises "+ HIS(TP) +" hand, palm facing you, " +
	"indicating that "+ HE(TP) +" has heard enough.",
	oblist, "arrogantly", attr);
    return 1;
}

public int
e_dreyeraise(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;
    string eyes = check_eyes();

    if (!strlen(str))
    {
	write("You slowly raise your" + eyes +", staring straight ahead.\n");
	allbb(" slowly raises "+ HIS(TP) + eyes +", staring straight ahead.",
	    "slowly", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Dreyeraise [at] / [to] [the] who/what?\n");

    actor("You slowly raise your" + eyes +", staring straight at", oblist);
    all2actbb(" slowly raises " + HIS(TP) + eyes +", staring straight at",
	oblist, 0, "slowly", attr);
    targetbb(" slowly raises "+ HIS(TP) + eyes +", staring straight at you.",
	oblist, "slowly", attr);
    return 1;
}

public int
e_dreyelower(string str)
{
    object *oblist;
    int attr = ACTION_VISUAL;
    string eyes = check_eyes();

    if (!strlen(str))
    {
	write("You quickly lower your" + eyes +" with unquestioning respect.\n");
	allbb(" quickly lowers "+ HIS(TP) + eyes +" with unquestioning respect.",
	    "quickly", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Dreyelower [at] / [to] [the] who/what?\n");

    actor("You quickly lower your" +eyes +", showing unquestioning respect "+
	"towards", oblist);
    all2actbb(" quickly lowers "+ HIS(TP) + eyes +", showing unquestioning "+
	"respect towards", oblist, 0, "quickly", attr);
    targetbb(" quickly lowers "+ HIS(TP) + eyes +", showing you unquestioning " +
	"respect.", oblist, "quickly", attr);
    return 1;
}

/*************************************************************************
 * The following are emotes that use the Drow Language.
 */

/* Cursed creature of light */
public int
e_drcurse(string str)
{
    mixed fail;
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_AURAL | ACTION_THREATENING | ACTION_OFFENSIVE;

    if (fail = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if (strlen(fail))
	    write(fail);
	else
	    write("You seem unable to use your mouth at this time.\n");

	return 1;
    }

    if (!strlen(str))
    {
	write("You bitterly seethe: Cha'kohkev aterrucen d'ssussun!\n");
	all(" bitterly seethes: Cha'kohkev aterrucen d'ssussun!", "", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drcurse [at] / [to] [the] who/what?\n");

    actor("You roar angrily at", oblist, ": "+
	"Cha'kohkev aterrucen d'ssussun!");
    all2act(" roars angrily at", oblist, ": "+
	"Cha'kohkev aterrucen d'ssussun!", "angrily", attr);
    target(" roars angrily at you: Cha'kohkev aterrucen d'ssussun!",
	oblist, "angrily", attr);

    return 1;
}

/* The destiny of the Drow is to conquer all! */
public int
e_drdestiny(string str)
{
    mixed fail;
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_AURAL;

    if (fail = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if (strlen(fail))
	    write(fail);
	else
	    write("You seem unable to use your mouth at this time.\n");

	return 1;
    }

    if (!strlen(str))
    {
	write("You fiercely declare: "+
	    "L'elamshin d'lil Ilythiiri zhah ulu har'luth jal!\n");
	allbb(" fiercely declares: "+
	    "L'elamshin d'lil Ilythiiri zhah ulu har'luth jal!",
	    "fiercely", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drdestiny [at] / [to] [the] who/what?\n");

    actor("You fiercely declare to", oblist, " the following: "+
	"L'elamshin d'lil Ilythiiri zhah ulu har'luth jal!");
    all2act(" fiercely declares to", oblist, " the following: "+
	"L'elamshin d'lil Ilythiiri zhah ulu har'luth jal!",
	"fiercely", attr);
    target(" fiercely declares to you the following: "+
	"L'elamshin d'lil Ilythiiri zhah ulu har'luth jal!",
	oblist, "fiercely", attr);

    return 1;
}

/* Walk in the strength of the shadows of the Quarvalsharess (Drow Queen) */
public int
e_drfarewell(string str)
{
    mixed fail;
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_AURAL;

    if (fail = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if (strlen(fail))
	    write(fail);
	else
	    write("You seem unable to use your mouth at this time.\n");

	return 1;
    }

    if (!strlen(str))
    {
	write("You lift a hand in farewell and whisper: "+
	    "Z'hin wun lil z'ress del lil veldrin del Quarvalsharess.\n");
	all(" lifts a hand in farewell and whispers: "+
	    "Z'hin wun lil z'ress del lil veldrin del Quarvalsharess.",
	    "", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drfarewell [at] / [to] [the] who/what?\n");

    actor("You lift a hand in farewell to", oblist, " and whisper: "+
	"Z'hin wun lil z'ress del lil veldrin del Quarvalsharess.\n");
    all2act(" lifts a hand in farewell to", oblist, " and whispers: "+
	"Z'hin wun lil z'ress del lil veldrin del Quarvalsharess.",
	"", attr);
    target(" lifts a hand in farewell to you and whispers: "+
	"Z'hin wun lil z'ress del lil veldrin del Quarvalsharess.",
	oblist, "", attr);

    return 1;
}

/* Comrade! May the goddess bless this meeting */
public int
e_drgreet(string str)
{
    mixed fail;
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_AURAL | ACTION_INGRATIATORY;

    if (!strlen(str))
    {
	write("You clasp your forearms and cross them over your chest "+
	    "in the drow greeting.\n");
	allbb(" clasps "+ HIS(TP) +" forearms and crosses them over "+
	    HIS(TP) +" chest in the drow greeting.", "", attr);
	return 1;
    }

    if (fail = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if (strlen(fail))
	    write(fail);
	else
	    write("You seem unable to use your mouth at this time.\n");

	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drgreet [at] / [to] [the] who/what?\n");

    if (sizeof(oblist) > 1)
    {
	write("You clasp your forearms and cross them over your chest "+
	    "in the drow greeting.\n");
	allbb(" clasps "+ HIS(TP) +" forearms and crosses them over "+
	    HIS(TP) +" chest in the drow greeting.", "", attr);
	return 1;
    }

    if (oblist[0]->query_guild_name_race() == GUILD_NAME)
    {
	actor("You clasp", oblist, " by the forearms in the drow "+
	    "greeting and declare: Abbil! "+
	    "Xal l'quar'valsharess dumo nindol talthalra.");
	all2act(" clasps", oblist, " by the forearms in the drow "+
	    "greeting and declare: Abbil! "+
	    "Xal l'quar'valsharess dumo nindol talthalra.", "", attr);
	target(" clasps you by the forearms in the drow greeting and "+
	    "declares: Abbil! Xal l'quar'valsharess dumo nindol talthalra.",
	    oblist, "", attr);
    }
    else
    {
	actor("You bow towards", oblist, " with the smooth and "+
	    "fluid ease that only the drow possess.");
	all2act(" bows toward", oblist, " with the smooth and "+
	    "fluid ease that only the drow possess.", "", attr);
	target(" bows toward you with the smooth and "+
	    "fluid ease that only the drow possess.", oblist, "", attr);
    }

    return 1;
}

/* All power to the Goddess! Victory to Her lands! */
public int
e_droath(string str)
{
    mixed fail;
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_AURAL;

    if (fail = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if (strlen(fail))
	    write(fail);
	else
	    write("You seem unable to use your mouth at this time.\n");

	return 1;
    }

    if (!strlen(str))
    {
	write("You fiercely declare: Jal z'ress ulu l'Valsharess! "+
	   "Ultrinnan ulu Ilta thac'zilen!\n");
	allbb(" fiercely declares: Jal z'ress ulu l'Valsharess! "+
	    "Ultrinnan ulu Ilta thac'zilen!", "fiercely", attr);
	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Droath [at] / [to] [the] who/what?\n");

    actor("You fiercely declare to", oblist, " the following: "+
	"Jal z'ress ulu l'Valsharess! Ultrinnan ulu Ilta thac'zilen!");
    all2act(" fiercely declares to", oblist, " the following: "+
	"Jal z'ress ulu l'Valsharess! Ultrinnan ulu Ilta thac'zilen!",
	"fiercely", attr);
    target(" fiercely declares to you the following: "+
	"Jal z'ress ulu l'Valsharess! Ultrinnan ulu Ilta thac'zilen!",
	oblist, "fiercely", attr);

    return 1;
}

/* A Gift to the Spider and Darkness! */
public int
e_drrude(string str)
{
    mixed fail;
    object *oblist;
    int attr = ACTION_VISUAL | ACTION_AURAL | ACTION_THREATENING | ACTION_OFFENSIVE;

    if (!strlen(str))
    {
	notify_fail("Drrude [at] / [to] [the] who/what?\n");
	return 0;
    }

    if (fail = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if (strlen(fail))
	    write(fail);
	else
	    write("You seem unable to use your mouth at this time.\n");

	return 1;
    }

    oblist = parse_this(str, "[at] / [to] [the] %l", attr);
    OBERROR("Drrude [at] / [to] [the] who/what?\n");

    actor("You point at", oblist, " and sneer: "+
	"Natha belbol ulu lil orbb lueth oloth!");
    all2act(" points at", oblist, " and sneers: "+
	"Natha belbol ulu lil orbb lueth oloth!", "", attr);
    target(" points at you and sneers: "+
	"Natha belbol ulu lil orbb lueth oloth!", oblist, "", attr);

    return 1;
}
