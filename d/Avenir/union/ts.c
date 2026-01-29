/*
 * The soul for the Shadow Warriors
 * Based on Nick's Solamnian Knight soul
 *   Copyright April 1996, Marc Prud'hommeaux (Lord Cirion)
 *
 * Modification Log:
 *
 *   Lucius, 2005-2006: Various cleanups and corrections.
 *   Lucius, Oct 2006: Added "uopt" command.
 *   Lucius, Nov 2007: Re-ordered includes to fix some dependency issues.
 *   Lucius, Aug 2017: More include changes.
 *   		       Moved help, promote, utitle commands here;
 *   		       Eliminated lib/help.h, lib/sphere.h
 *
 */
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include <filter_funs.h>
#include <composite.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <options.h>
#include <macros.h>

#include "defs.h"

#include "lib/language.h"       /* Guild language             */
#include "lib/attack.h"         /* Special attacks            */
#include "lib/ability.h"        /* Special guild abilities    */
#include "lib/emotions.h"       /* Stick in the emotes        */
#include "lib/options.h"        /* Options for Warriors       */


public mapping
query_ability_map(void)
{
    return ([
	"fling": SPECIAL + "fling",
   "ufling": SPECIAL + "fling",
	"slash": SPECIAL + "slash",
   "uslash": SPECIAL + "slash",
	 "sway": SPECIAL + "sway",
    ]);
}

/* Commands */
public mapping
query_cmdlist(void)
{
    return ([

     /* Special attack 'Fling' */
         "fling" : "do_ability",
        "ufling" : "do_ability",
     /* Special attack 'Slash' */
         "slash" : "do_ability",
        "uslash" : "do_ability",
     /* Special ability 'Sway' */
          "sway" : "do_ability",
#if 0
     /* Special attack 'Fling' */
         "fling" : "fling",
     /* Special attack 'Slash' */
         "slash" : "slash",
#endif
        /* Guild Language */
            "us" : "usay",
          "usay" : "usay",
          "usto" : "us_to",

       "compare" : "compare_virtue",
          "mark" : "mark",
          "dget" : "dget",
          "stop" : "stop",
          "uapp" : "uapp",
          "uins" : "uins",
        "vitals" : "vitals",
             "v" : "vitals",

          /* Help file */
          "help" : "help",

     /*      Emotions       */
  /* Keep alphabetized, please */
         "angry" : "angry",
         "blink" : "blink",
         "brood" : "brood",
          "calm" : "calm",
         "clash" : "clash",
         "cross" : "cross",
         "curse" : "curse",
         "dance" : "dance",
       "dignity" : "dignity",
        "ectios" : "ectios",
         "flick" : "flick",
          "gaze" : "gaze",
         "glare" : "glare",
         "greet" : "greet",
      "indicate" : "indicate",
     "interrupt" : "interrupt",
           "joy" : "joy",
         "laugh" : "laugh",
         "mourn" : "mourn",
        "murmur" : "murmur",
          "pain" : "pain",
       "patient" : "patient",
          "peer" : "peer",
       "respect" : "respect",
         "scorn" : "scorn",
         "smile" : "smile",
          "spin" : "spin",
         "swear" : "swear",
      "threaten" : "threaten",
          "toss" : "toss",
       "triumph" : "triumph",
        "uclean" : "uclean",
         "udown" : "udown",
       "ufinger" : "ufinger",
      "unamused" : "unamused",
       "uncloak" : "uncloak",
        "usoath" : "uoath",
        "usrage" : "urage",
        "ustudy" : "ustudy",
        "usturn" : "uturn",
         "wrath" : "wrath",

       /* General Commands */
       "promote" : "promote",
        "utitle" : "utitle",
       "utitle2" : "utitle",
      "uadverbs" : "uadverbs",
          "uopt" : "uopt",
    ]);
}

// Called by help(), this gives an array of publicly shown
// union commands
public string *
query_union_commands(void)
{
    return ({
    /* Commands first */
          "mark",	"dget",		"uapp",
          "uins",	"fling",	"slash",
          "sway",	"utitle",	"utitle2",
          "usay",	"usto",		"uadverbs",
	  "uopt",
    /* Emotes second */
         "angry",	"brood",	"calm",
         "clash",	"cross",	"curse",
       "dignity",	"ectios",	"flick",
          "gaze",	"glare",	"greet",
      "indicate",	"interrupt",	"joy",
         "mourn",	"murmur",	"pain",
       "patient",	"respect",	"scorn",
          "spin",	"threaten",	"triumph",
        "uclean",	"udown",	"ufinger",
      "unamused",	"uncloak",	"usoath",
        "usrage",	"ustudy",	"usturn",
         "wrath",
    });
}

/* Id and autoload */
public nomask string
get_soul_id(void)	{ return "Shadow_Union"; }

/* It is a real command soul */
public nomask int
query_cmd_soul(void)	{ return 1; }

/*
 * Help command.
 */
public void
help_union_spheres(void)
{
    write(sprintf("%|78s\n\n      %-#76.4s\n\n",
	    "---- Commands for the "+ OCC_NAME +" ----",
	    implode(query_union_commands(), "\n")));
}

public int
help(string str)
{
    if (!strlen(str))
	return 0;

    str = lower_case(str);

    if (MEMBER_SPHERE(TP, "mentor") && parse_command(str, ({}),
	    "[on] [the] [shadow] [union] 'mentor' / 'mentors'"))
    {
	write("Mentor commands:\n\n");
	write("    * promote  - Promote someone as a true member "+
	    "of the Union.\n");
	write("\n");
	return 1;
    }

    if (!parse_command(str, ({}),
	    "[on] [the] [shadow] 'union' / 'warriors'"))
	return 0;

    // give extra sphere-specific command help
    TP->query_cmdsoul_list()->help_union_spheres();
    return 1;
}

/* 
 * Promote without ceremony.
 * Useable by Mentors or Elders only.
 */
public int
promote(string str)
{
    object *oblist, who;

    if (!strlen(str))
	return 0;

    str = lower_case(str);

    /* Only mentors or Elders can promote people past trainee. */
    if (!MEMBER_SPHERE(TP, SPH_MENTOR))
	return 0;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	notify_fail("Promote who past the level of trainee?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only promote one person at a time.\n");
	return 0;
    }

    who = oblist[0];

    if (!IS_MEMBER(who))
    {
	TP->catch_msg(QCTNAME(who) + " is not a member of the Union.\n");
	return 1;
    }

    if (who->query_skill(OCC_LEVEL) >= NORMAL)
    {
	TP->catch_msg(QCTNAME(who) + " has already been promoted to "+
	    "a true member of the Union.\n");
	return 1;
    }

    who->set_skill(OCC_LEVEL, NORMAL);
    who->save_me();

    if (who == TP)
    {
	write("You promote yourself as a true member of the Union.\n");
	return 1;
    }

    TP->catch_msg("You brush your hand against " + QTNAME(who) +
	"'s forehead and accept " + HIM(who) +
	" as a true member of the Union.\n");
    who->catch_msg(QCTNAME(TP) + " brushes " + HIS(TP) +
	" hand against your forehead.\nYou are infused with "+
	"a sense of grace.\n");
    say(QCTNAME(TP) + " places " + HIS(TP) + " hand against "+
	QTNAME(who) + "'s forehead for a moment.\n");

    return 1;
}

public int
utitle(string str)
{
    string title, *titles = TP->possible_union_titles(1);

    if (!strlen(str) || str == "list")
    {
	if (!sizeof(titles))
	{
	    write("You have no titles to choose from.\n");
	    return 1;
	}
	else
	{
	    write("Possible title" + (sizeof(titles) == 1 ? " is " :
		    "s are ") + COMPOSITE_WORDS(titles +
		    ({ "random", "none" })) + ".\n");
	    return 1;
	}
    }

    // Check to see if we are setting the first or second title
    title = TP->set_union_title(str, (query_verb() == "utitle2") + 1);

    if (!strlen(title))
	return NF("That is not a title you may choose from.\n");

    write("You set your title to " + title + ".\n");
    return 1;
}
