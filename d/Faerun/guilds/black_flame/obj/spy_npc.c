// Spy npc      /d/Avenir/inherit/spy_npc.c
// creator(s):  Lilith  Jan 99
// last update: Lucius April 2005: Changed how information is relayed.
//              Lucius, May 2007: Further fixes.
// purpose:     These npcs take note of who they meet and will 
//              report on request.
// note:        Some code borrowed from Cirion's union npc.
//              use create_spy() like you would create_monster()
// bug(s):
// to-do:
#pragma strict_types

inherit "/d/Avenir/inherit/monster";

#include <macros.h>
#include <composite.h>

#include "/d/Avenir/include/relation.h"

public static int alarm_id, cleanup_alarm, auto_intro;

/* Mapping of all the passer-by's for this NPC  */
/* During this reboot. It will be of the form:  */
/* ([ "name" : ({ (int)known, (when), "short", "long", "name" }) ]); */
private static mapping passer_by = ([]);

public void
add_spy_ask(void)
{
    /*
     * We can now ask the NPC for a list of people we have met.
     * We can also ask the NPC to describe the person, but since
     * the question is handled dynamically (e.g., we can only
     * respond to "ask cyrus to describe the dark-haired elf"
     * if we have met a dark-haired elf...), this will be handled
     * in the catch_question() function.
     */
    add_ask(({ "list people", "who have you met", "report", 
	"list met", "report who you saw", "report who you met", 
	"list those you met", "who have you encountered",
	"who have you seen"}),
	VBFC_ME("ask_about_encountered"), 1);
}

public void
spy_auto_intro(void)	{ auto_intro = 1; }

static void
create_monster(void)
{
    ::create_monster();

    add_spy_ask();
    add_name("spy");

    this_object()->create_spy();
}

/*  Mask this function to make your npc react differently.
 *  See /d/Avenir/common/mon/town_crier.c for an example.
 */
public void
check_meet(object tp)
{
    alarm_id = 0;
}

private void
perform_cleanup(void)
{
    /* Two weeks good? */
    int i, limit = (60 * 60 * 24 * 14);
    string *people = m_indices(passer_by);

    cleanup_alarm = 0;

    if (!sizeof(people))
	return;

    for (i = 0; i < sizeof(people); i++)
    {
	if (passer_by[people[i]][1] < limit)
	    m_delkey(passer_by, people[i]);
    }
}

/* 
 *  Make things happen when I meet the right people.
 */
public varargs void
meet_living(object who, int known = 0)
{
    /* Don't notice npcs */
    if (!query_interactive(who))
	return;

    /* If we can't see them, we can't remember them */
    if (!CAN_SEE(this_object(), who) ||
	!CAN_SEE_IN_ROOM(this_object()))
	return;

    /* Don't do this for wizards or JR's */
#ifndef DEBUG
    if ((who->query_wiz_level()) || wildmatch("*jr", who->query_name()))
	return;
#endif

    /* I always know members of the Union, they guard Sybarus, after all. */
    if (IS_UNION(who))
	known = 1;

    string name = who->query_real_name();

    /* Don't magically forget names upon next encounter. */
    if (passer_by[name] && passer_by[name][0])
	known = 1;

    passer_by[name] = ({ known, time(), who->query_nonmet_name(),
	who->long(this_object()), name });

    if (!cleanup_alarm && !random(3))
	cleanup_alarm = set_alarm(itof(5), 0.0, perform_cleanup);

#ifdef DEBUG
command("say meet_living() called for "+ name +"; known=="+ known);
#endif
}

/*
 * convert a string to an array of past
 * tense descriptions.
 */
private string *
convert_string_past(string str, int met, string nm)
{
    int i, s;
    string *ret, *build = ({}), foobar;

    if (!strlen(str))
	return ({ });

    ret = explode(str, " ");
    foreach(string word : ret)
    {
	switch(word)
	{
	// "He is a..." to "He was a..."
	case "is":	ret[i] = "was";		break;
	// "He has scars..." to "He had scars..."
	case "has":	ret[i] = "had";		break;
	// "He looks happy..." to "He looked happy..."
	case "looks":	ret[i] = "looked";	break;
	// "He seems to be..." to "He seemed to be..."
	case "seems":	ret[i] = "seemed";	break;
	// "His eyes are..." to "His eyes were..."
	case "are":	ret[i] = "were";	break;
	// "He wears ..." to "He wore..."
	case "wears":	ret[i] = "wore";	break;
	// "He holds ..." to "He held..."
	case "holds":	ret[i] = "held";	break;
	// "presenting himself as..." to "who presented himself as..."
	case "presenting":  ret[i] = "who presented";	break;
	}

	i++;
    }

    // return the newline-delimited array...
    ret = explode(implode(ret, " "), "\n");

    // All this so a questioner cannot obtain the real name
    // of a player he shouldn't know.
    if (met == 0)
    {
	nm = lower_case(nm);

	s = sizeof(ret);
	i = -1;
	while( ++i < s )
	{
	    if (!(sscanf(lower_case(ret[i]),
			"%s" + nm + " %s", foobar, foobar)))
	    {
		build += ({ ret[i] });
	    }
	}
    }
    else
	build = ret;

    return build;
}

/*
 * Give a nice listing of those people who I have
 * encountered, based on whether I know them or not.
 *
 * E.g., "a long-armed elf, Cirion, and a sultry dark-skinned human"
 */
private string
list_met(void)
{
    int i, s;
    mixed elem;
    string *indices, *descs = ({});

    indices = m_indices(passer_by);

    if (!sizeof(indices))
	return "Law-biding sybarites";

    s = sizeof(indices);
    i = -1;
    while(++i < s)
    {
	elem = passer_by[indices[i]];

	if(elem[0] == 0)
	    descs += ({ elem[2] });
	else
	    descs += ({ capitalize(indices[i]) });
    }

    if (sizeof(descs) == 1)
	return "Law-abiding sybarites...and that " + descs[0];
    else
	return COMPOSITE_WORDS(descs);
}

// for debugging...
public void
dump_met(void)
{
    dump_mapping(passer_by);
}

/*
 * Describe how long ago I met someone.
 */
public string
time_met_desc(int tm)
{
    int how_long_ago;

    /* How long ago I met the person, in minutes. */
    how_long_ago = (time() - tm) / 60;

    switch(how_long_ago)
    {
    case 0 .. 2:
	return "just now";
	break;
    case 3 .. 7:
	return "very recently";
	break;
    case 8 .. 20:
	return "fairly recently";
	break;
    case 21 .. 60:
	return "recently";
	break;
    case 61 .. 120:
	return "a little while ago";
	break;
    case 121 .. 250:
	return "a while ago";
	break;
    default:
	return "a long time ago";
	break;
    }

    // Sanity check
    return "sometime";
}

private mixed *
find_met_desc(string desc)
{
    string *ind, foobar;
    mixed   elems;
    int     i;

    desc = lower_case(desc);

    ind = m_indices(passer_by);

    if (!sizeof(ind))
	return ({});

    for(i = 0; i < sizeof(ind); i++)
    {
	elems = passer_by[ind[i]];

	// did we ask about the short description?
	if(desc == elems[2])
	    return elems;
	// else if they asked about the name, describe the
	// person ONLY IF WE HAVE MET THEM (so people
	// cannot obtain a name they should not be able to).
	else if((desc == ind[i]) && (elems[0] > 0))
	    return elems;
    }

    // Can't find it? Let's try once again, this time doing
    // a partial string comparison so we can catch
    // "gnome" in "blue-eyed male gnome".
    for(i = 0; i < sizeof(ind); i++)
    {
	elems = passer_by[ind[i]];

	if (sscanf(elems[2], "%s" + desc + "%s", foobar, foobar))
	    return elems;
    }

    return ({});
}

/*  
 * This makes the npc describe who it has met.
 */
private void
describe_met(string desc)
{
    int i, s;
    mixed elems;
    string *descs, ld;

    elems = find_met_desc(desc);

    // can't find the decription...
    if (!sizeof(elems))
    {
	command("ask "+ OB_NAME(this_player()) +
	    " Are you sure you mean \"" + desc + "\"?");
	command("whisper to "+ OB_NAME(this_player()) +
	    " I haven't seen anyone who looks like that.");
	return;
    }

    ld = elems[3];
    descs = convert_string_past(ld, elems[0], elems[4]);

    // describe how long ago we met...
    say(QCTNAME(this_object()) + " whispers something to "+
	QTNAME(this_player()) +".\n");
    write(this_object()->query_The_name(this_player()) +
	" whispers to you: I noticed this person " +
	time_met_desc(elems[1]) + "...\n");

    // Give the long description of the person...
    i = -1;
    s = sizeof(descs);
    while (++i < s)
    {
	write(descs[i] + "\n");
    }
    write("\n");
}

/*
 * VBFC to ask the NPC about the list of people I have met.
 */
public string
ask_about_encountered(void)
{
    if (IS_SYBARITE(this_player()) < SYB_LAY)
	return "shrug " + one_of_list(({"", ".", "indiff", "unknow"}));

    say(QCTNAME(this_object()) + " whispers something to "+
	QTNAME(this_player()) +".\n");
    write(this_object()->query_The_name(this_player()) + " whispers to you: "+
	"The only people of interest I have seen recently were: ");
    write(list_met() + ".\n");

    return "smile helpful";
}

/*
 * Function name: init_living
 * Description:   Make things happen when I come into contact
 *                with other things.
 */
public void
init_living(void)
{
    ::init_living();

    /* Check for seen - don't do any further actions if you cannot see */
    if (!CAN_SEE_IN_ROOM(this_object()) ||
	!CAN_SEE(this_object(), this_player()))
	return;

    if (query_interactive(this_player()))
    {
	/* greet them */
	if (!alarm_id)
	    alarm_id = set_alarm(2.0, 0.0, &check_meet(this_player()));
    }

    /* register them as someone I have met */
    meet_living(this_player());
}

/*
 * Function name:   add_introduced
 * Description:     Add the name of a living who has introduced herself to us
 * Arguments:       str: Name of the introduced living
 */
public void
add_introduced(string str)
{
    object who = present(str, environment(this_object()));

    if (!objectp(who))
	return;

    /*
     * Update our list of people to reflect that we know the
     * person's name
     */
    meet_living(who, 1);

    if (auto_intro && !who->query_met(this_object()))
    {
	set_alarm(itof(random(5) + 1), 0.0,
	    &command("introduce myself to "+ OB_NAME(who)));
    }
}


/*
 * Function name: catch_question
 * Description:   This function is called in each living being someone asks a
 *                question to.
 * Arguments:     question - The question as put
 */
public int
catch_question(string str)
{
    mixed ret;
    string person;

    // describe livings that we have encountered...
    if (parse_command(str, ({}), "[to] 'describe' [the] %s", person))
    {
	if (IS_SYBARITE(this_player()) >= SYB_LAY)
	    describe_met(person);

	return 1;
    }

    ret = ::catch_question(str);
    return ret;
}
