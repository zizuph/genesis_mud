/* -*- Mode: C -*-
 *
 * Root object obj/root_obj.c
 *
 * Skippern 20(c)04
 *
 * 
 *
 */
inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

object room;

void set_room(object o) { room = o; }

void
fade_me()
{
    tell_room(room, "The "+short()+" withdraws back underground.\n",
		     0, 0);
    remove_object();
}

void
grow()
{
    tell_room(room, "A large plants spurts up from the ground covering the " +
		     "area.\n", 0, 0);
}

void
create_object()
{
    set_short("large entangling plant");
    set_adj("large");
    add_adj("entangling");
    add_name("plant");
    set_long("A large plant have grown out of the ground here. The plant's " +
	     "leaves and branches entwine all objects in its way. It seems " +
	     "like a strange force is controlling the plant, as it is " +
	     "continuously moving in waves.\n");
    add_prop(OBJ_M_NO_GET, "You cannot pick up the plants covering the " +
	     "ground.\n");
    set_alarm(15.0,0.0,&fade_me());
}

int
do_entangle(string arg)
{
    object tp = this_player();
    int str = tp->query_stat(SS_STR);
    int dex = tp->query_stat(SS_DEX);
    int i;
    string verb = query_verb();
    string *dirs = environment(this_object())->query_exit_cmds();

    for (i = 0; i < sizeof(dirs); i++)
    {
	if (verb == dirs[i])
	{
	    // now, let us see if you fail
	    if (random(str)<(200-random(200)) || random(dex)<(200-random(200)))
	    {
		write("You try to move, but "+short()+" is holding you " +
		      "back.\n");
		say(QCTNAME(tp)+ " tries to move, but "+short()+" holds " + 
		    tp->query_objective() + " back.\n");
		return 1;
	    }
	}
    }
    // if you make it here, you'll make it out of it.
    return 0;
}

void
init()
{
    ::init();
    add_action(do_entangle, "", 1);
}
