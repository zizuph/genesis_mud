inherit "/std/object";
inherit "/lib/commands";
#include "/d/Gondor/defs.h"
#include "../erech.h"

#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
string short_desc();
string long_desc();
int    splash(string arg);
int    evaporate();
int    stain(object target);

/* Global variables */
int    size;
string content = "ink";

create_object() 
{
    set_short(&short_desc());
    set_long(&long_desc());
    set_name("pool");
    add_name("Erech_farm_pool");
    add_prop(OBJ_I_WEIGHT,57);
    add_prop(OBJ_I_VOLUME,25);
    add_prop(OBJ_I_VALUE,35);
    add_prop(OBJ_M_NO_GET,"Trying to pick it up you get all wet on your fingers.\n");

    size = 1;

    set_alarm(300.0, 0.0, &evaporate());

}

string
short_desc()
{
    if (size == 0)
        return "WARNING: ERROR IN SIZE!";
    else if (size == 1)
        return "small pool of "+content;
    else if (size == 2)
        return "pool of "+content;
    else if (size == 3)
        return "large pool of "+content;
    else if (size == 4)
        return "very large pool of "+content;
}

string
long_desc()
{
    if (size == 0)
        return "WARNING: ERROR IN SIZE, POOL SHOULD HAVE EVAPORATED BY NOW!\n";
    else if (size == 1)
        return "A small pool of "+content+".\n";
    else if (size == 2)
        return "A pool of "+content+".\n";
    else if (size == 3)
        return "A large pool of "+content+".\n"; 
    else if (size == 4)
        return "A very large pool of "+content+".\n";
}

void
init()
{
    ::init();
    add_action(splash, "splash");
}

int
splash(string arg)
{
    object target;
    object *present;
    object worker;

    string *names;

    worker = this_player();

    if (arg == "me" || arg == "myself")
        arg = worker->query_real_name();

    if (arg)
    {
	// find target
        names = map(FILTER_LIVE(all_inventory(environment(worker))), &->query_real_name());
	if (member_array(arg, names) == -1)
	{
	    notify_fail("Syntax: splash <player>\n");
	    return 0;
	}
	// make target == object of arg
	present = parse_this_and(arg, "%l", 1);
	target = present[0];
	if (worker->query_real_name() == arg)
	{
	    write("You splash some " + content + " all over yourself.\n");
	    say(QCTNAME(worker) + " splashes some " + content + " all over " +
		worker->query_objective()+"self.\n");
	    stain(worker);
	    return 1;
	}
	write("You splash some "+content+" all over "+target->query_name()+
	    ".\n");
	target->catch_tell(worker->query_The_name(target) + " splashes some " +
	    content + " all over you.\n");
	say(QCTNAME(worker) + " splashes some "+content+" all over " +
	    QTNAME(target) + " making " + target->query_objective() +
	    " all wet.\n", ({ target, worker }) );
	stain(target);
	return 1;
    }
    if (!arg)
    {
	write("You jumps in the pool of "+content+" and have lots of fun.\n");
	say(QCTNAME(worker) + " jumps up and down in the pool and splashes " +
	    content + " all over " + worker->query_objective() + "self.\n");
	return 1;
    }
    notify_fail("Syntax: splash <player>\n");
    return 0;
}

int
set_content(string arg)
{
    content = arg;
    return 1;
}

int
set_size(int arg)
{
    size = arg;
    return size;
}

int query_size() { return size; }
string query_content() { return content; }

int
evaporate()
{
    if (size > 1)
    {
	tell_room(environment(this_object()), "The pool of " + content + 
	    " becomes smaller.\n");
	size = size - 1;
	set_alarm(300.0, 0.0, &evaporate());
	return 1;
    }
    tell_room(environment(this_object()), "The pool of " + content + 
        " evaporates entirely.\n");
    remove_object();
    return 1;
}

int
stain(object target)
{
    object     stain;

    if (!target)
        return 1;

    if (random(4) == 1)
    {
        stain = clone_object(E_OBJ + "stain.c");
	stain->set_type(content);
	stain->move(target);
    }
    return 1;
}
