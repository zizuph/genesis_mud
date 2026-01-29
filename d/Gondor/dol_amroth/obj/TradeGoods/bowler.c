/* -*- Mode: C -*-
 *
 * bowler.c
 *
 * A bowler hat sold in Dol Amroth.
 * 
 * By Skippern 20(c)01
 */
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/commands";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

public nomask void
create_object()
{
    set_name("bowler");
    add_name("hat");

    set_long("This hat looks like half a baloon with a thin " +
	     "rim on it. It is made out of black cloth.\n");

    set_slots(A_HEAD);

    set_layers(2);
    set_looseness(0);

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE,   75);

}


int
hroll(string arg)
{
    if (this_object()->query_worn() == 0)
    {
        notify_fail("You have to wear the hat to do that.\n");
	return 0;
    }
    write("You roll your bowler elegantly down the arm.\n");
    all(" rolls "+this_player()->query_possessive()+" bowler " +
	"elegantly down "+this_player()->query_possessive()+" arm.\n");
    return 1;
}

int
hgreet(string arg)
{
    object    *ob;

    if (this_object()->query_worn() == 0)
    {
        notify_fail("You have to wear the hat to do that.\n");
	return 0;
    }
    if (!arg)
    {
        write("You lift your hand to the rim of your bowler as a greeting.\n");
	all(" lifts "+this_player()->query_possessive()+" hand to the rim " +
	    "of "+this_player()->query_possessive()+" bowler.\n");
	return 1;
    }
    ob = parse_this(arg,"%l");
    if (!sizeof(ob))
    {
        notify_fail("Greet whom?\n");
	return 0;
    }
    actor("You lift your hand to the rim of your bowler and greets" ,
	  ob, ".\n");
    targetbb(" greets you by lifting "+this_player()->query_possessive()+
	" hand to the rim of "+this_player()->query_possessive()+
	" bowler.\n", ob);
    all2actbb(" greets", ob, "by lifting "+
	this_player()->query_possessive()+" hand to "+
	this_player()->query_possessive()+" bowler.\n", ob);
    return 1;
}

void
init()
{
    ::init();
    add_action("hgreet","hgreet");
	add_action("hgreet", "htip");
    add_action("hroll","hroll");
}

/*
 * We need to override leave_env() so that we can be sure to remove the
 * hat if it gets moved from the wearer while it is still worn.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}

/*
 * We need to override appraise_object() so that we can be sure that the
 * player can appraise it properly.
 */
void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}
