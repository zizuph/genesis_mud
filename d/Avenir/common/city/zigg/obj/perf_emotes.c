/*
 * - emotes.c
 *
 * Emotes for perfumes and colognes.
 */
#pragma strict_types
#pragma no_inherit
#pragma no_shadow

inherit "/std/object";
inherit "/lib/commands";

#include <macros.h>
#include <adverbs.h>
#include <cmdparse.h>
#include <language.h>
#include <stdproperties.h>

#define NO_BOTTLES
#define NO_PERFUMES

#include "perfume.h"

public void
create_object(void)
{
    set_no_show();
    set_name("perfumeob");
    add_prop(OBJ_M_NO_DROP, 1);
}

private static string oil;
private static string *data;

public void
set_perfume_oil(string str, string *arr)
{
    oil = str;
    data = arr;
}

private int
check_perfume(void)
{
    if (strlen(oil))
	return 0;

    TP->remove_perfume();
    set_alarm(0.5, 0.0, &remove_object());
    notify_fail("You don't seem to be wearing any "+
	(TP->query_gender() ? "perfume" : "cologne") + ".\n");

    return 1;
}

/****   E M O T E S   ****/

#define OBERROR(str) if (!sizeof(oblist)) { \
        if (strlen(parse_msg)) { write(parse_msg); return 1; } \
        return notify_fail(str);  }


public int
e_hold(string str)
{
    object *oblist;
    string *how, *arr;

    if (check_perfume())
	return 0;

    how = parse_adverb_with_space(str, "closely", 1);

    if (!strlen(how[0]))
    {
	notify_fail("You need to pick someone to phold.\n");
	return 0;
    }

    oblist = parse_this(how[0], "[the] %i", ACTION_CONTACT | ACTION_OLFACTORY);
    OBERROR("Phold whom/what [how]?\n");

    if (sizeof(oblist) > 1)
	str = "them";
    else
	str = HIM(oblist[0]);

    arr = one_of_list(({
	({ "enveloping "+ str +" in", "eveloping" }),
	({ "surrounding "+ str +" with", "surrounding" }),
	({ "encompassing "+ str +" in", "encompassing" }),
    }));

    actor("You hold", oblist, how[1] +", "+ arr[0] +" your "+
	data[SCENT] +" scent.");
    all2act(" holds", oblist, how[1] + ".",
	how[1], ACTION_CONTACT);
    target(" holds you"+ how[1] +", "+ HIS(TP) +" "+
	data[SCENT] +" scent "+ arr[1] +" you.",
	oblist, how[1], ACTION_CONTACT | ACTION_OLFACTORY);

    return 1;
}

public int
e_hug(string str)
{
    int ghug;
    object *oblist;
    string *how, *arr, pos;

    if (check_perfume())
	return 0;

    how = parse_adverb_with_space(str, BLANK_ADVERB, 1);

    ghug = (how[0] == "all");
    oblist = parse_this(how[0], "[the] %l", ACTION_CONTACT);
    OBERROR("Phug whom/what [how]?\n");

    pos = HIS(oblist[0]);

    arr = one_of_list(({
	({"lingering on "+ pos +" skin", "lingering on your skin"}),
	({"filling "+ pos +" senses", "filling your senses"}),
	({"lingering in the air", "lingering in the air"}),
    }));

    if (ghug && (sizeof(oblist) > 1))
    {
	pos = "their";
        actor("You engage in a group-hug with", oblist, " and hug them" +
            how[1] + ", your "+ data[SCENT] +" scent "+ arr[0] +".");
        all(" engages in a group-hug with everyone in the room and hugs you" +
            how[1] +", "+ HIS(TP) +" "+ data[SCENT] +" scent "+ arr[1] +".",
	    how[1], ACTION_CONTACT | ACTION_OLFACTORY);
        return 1;
    }

    actor("You hug", oblist, how[1] + ", your "+
	data[SCENT] +" scent "+ arr[0] + ".");
    all2act(" hugs", oblist, how[1] + ".", how[1],
	ACTION_VISUAL);
    target(" hugs you" + how[1] + ", "+ HIS(TP) +" "+
	data[SCENT] +" scent "+ arr[1] +".", oblist, how[1],
	ACTION_CONTACT | ACTION_OLFACTORY);

    return 1;
}

public int
e_smell(string str)
{
    string *how;
    object *oblist;

    if (check_perfume())
	return 0;

    if (!strlen(str))
	return notify_fail("Psmell whom [how]?\n");

    how = parse_adverb_with_space(str, "inquisitively", 1);
    oblist = parse_live(how[0], "[the] %o", ACTION_OLFACTORY);
    OBERROR("Psmell whom [how]?\n");

    actor("You sniff the air around", oblist, how[1] +".");
    all2actbb(" sniffs the air around", oblist, how[1] +".",
	how[1], ACTION_OLFACTORY);
    target(" sniffs the air around you"+ how[1] +".",
	oblist, how[1], ACTION_OLFACTORY);

    oblist->hook_smelled();

    if (strlen(str = oblist[0]->query_perfume_oil()))
    {
	actor("You place", oblist, "'s scent "+
	    "as being that of "+ str +" "+ (oblist[0]->query_gender() ?
		"perfume" : "cologne") + ".");
    }
    else
    {
	actor("You are unable to place any of the scents "+
	    "coming from", oblist);
    }

    return 1;
}

public int
e_waft(string str)
{
    if (check_perfume())
	return 0;

    if (strlen(str))
    {
	notify_fail("Just waft away, there are no arguments.\n");
	return 0;
    }

    write("You fill the air around you with "+
	LANG_ADDART(data[SCENT]) +" wafting scent.\n");
    say("You smell "+ LANG_ADDART(data[SCENT]) +" scent emanating "+
	"from "+ QTNAME(TP) +".\n");

    return 1;
}

public void
init(void)
{
    ::init();

    add_action(  e_hold, "phold"  );
    add_action(   e_hug, "phug"   );
    add_action( e_smell, "psmell" );
    add_action(  e_waft, "waft"   );
}
