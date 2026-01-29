/*
 * File:     statuette
 * Created:  Cirion, 1999.01.10
 * Purpose:  small ebony statuette the sphere of diplomacy is
 *           able to give people as a token of gratitude.
 * Modification Log:
 *
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

public string giftee;


public string
statue_who(void)	{ return CAP(giftee); }

public void
create_object()
{
    reset_euid();

    set_name("statuette");
    add_name("_union_statuette");
    set_adj(({ "small", "ebony", "statuette" }));

    set_short("small ebony statuette");
    set_long("This small ebon statuette depicts a number of "+
	"tiny figures engaging in a Bacchanalian revel. There "+
	"is an inscription upon the bottom in Old Sybarite, "+
	"which reads: 'To @@statue_who@@, a show of appreciation "+
	"of the Union of the Warriors of Shadow.'\nThese "+
	"statuettes are given as tokens of the Shadow Union's "+
	"esteem. You are quite fortunate to be holding one.\n");

    add_prop(OBJ_I_VOLUME, 160);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VALUE, 106);

    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, "The only way to get rid of the "+
	"statuette would be to break it. No one would purchase "+
	"such a thing.\n");
    add_prop(OBJ_M_NO_DROP, "The only way to get rid of the "+
	"statuette would be to break it.\n");
    add_prop(OBJ_M_NO_GIVE, "The only way to get rid of the "+
	"statuette would be to break it.\n");
}

public string
query_auto_load(void)	{ return MASTER; }

public int
do_break(string str)
{
    object glass, ob;

    notify_fail(CAP(query_verb()) + " what?\n");

    if (!strlen(str))
	return 0;

    if (str != "union_force_break")
    {
	if (!parse_command(str, TP, "[the] %o", ob) || ob != TO)
	    return 0;
    }

    write("You smash the "+ short() +" against the ground, shattering "+
	"it completely.\n");
    say(QCTNAME(TP) +" smashes "+ LANG_ADDART(short()) +" against the "+
	"ground, shattering it completely.\n");

    glass = clone_object("/std/heap");
    glass->set_name("shard");
    glass->add_name("ebony");
    glass->set_adj("broken");
    glass->set_short("shards of broken ebony");
    glass->set_pshort("shards of broken ebony");
    glass->set_long("It is a shard of ebony, broken from some "+
	"delicate work.\n");
    glass->set_heap_size(random(10)+1);
    glass->add_prop(HEAP_S_UNIQUE_ID, "broken ebony fragment");
    glass->add_prop(OBJ_I_VALUE, 1);
    glass->add_prop(OBJ_I_WEIGHT, 2);
    glass->add_prop(OBJ_I_VOLUME, 8);
    glass->move(ENV(TP));

    all_inventory(TO)->move(ENV(TP), 1);
    set_alarm(0.0, 0.0, remove_object);
    return 1;
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!from && !giftee && living(to)) // cloned either by ugift command or auto-laod
	giftee = to->query_real_name();
    else if (to->query_real_name() != giftee)
	do_break("union_force_break"); // make it break
}

public void
init(void)
{
    ::init();

    if (environment() != TP)
	return;

    add_action(do_break, "break");
    add_action(do_break, "smash");
}
