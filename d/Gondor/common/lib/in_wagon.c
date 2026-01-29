/*
 *	/d/Gondor/minas/lib/in_wagon.c
 *
 *	Original version by Elessar.
 *	This version by Olorin, January 1997.
 *
 *	Modification log:
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public string  inside_long();
public string  exa_horses();
public string  exa_view();

static object  Wagon;

public void    set_wagon(object ob) { Wagon = ob; }
public object  query_wagon() { return Wagon; }

public void
create_wagon()
{
}

nomask void
create_gondor()
{
    create_wagon();

    set_short("inside a horse carriage");
    set_long(inside_long);

    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item("view", exa_view);
    add_item( ({"horse","horses"}), exa_horses);
}

public string
inside_long()
{
    string  long_descf = "You are inside a wooden horse carriage, currently ";

    if (Wagon->query_leavable()) 
	long_descf += "standing still in ";
    else 
	long_descf += "rambling along ";
    long_descf += ENV(Wagon)->short() + ". ";
    long_descf += "There is an old, skinny human driving the carriage, " +
	"controlling the " + LANG_WNUM(Wagon->query_horses()) + 
	" horses that are pulling it. ";
    if (Wagon->query_leavable())
	long_descf += "You may 'jump out' of the carriage here, " +
	    "as it is not moving now.";
    else 
	long_descf = "It could be dangerous to jump out of the "
	    + "carriage now, as it is moving.";
    return BSN(long_descf);
}

public int
leave_wagon(string str)
{
    object  room;
    string  vb = query_verb();

    if (!strlen(str)) 
    { 
	NFN(CAP(vb) + " what?");
	return 0;
    }

    switch (vb)
    {
    case "leave":
	if (!Wagon->id(str))
	{
	    NFN("Leave what? The wagon?\n");
	    return 0;
	}
	break;
    case "out":
	if ((str != "of wagon") && (str != "of carriage"))
	{
	    NFN("Out of what? Out of the wagon?");
	    return 0;
	}
	break;
    case "jump":
	if ((str != "out") && (str != "off") && (str != "off wagon")
	    && (str != "out of wagon"))
	{
	    NFN("Jump where? Off?"); 
	    return 0; 
	}
	break;
    case "exit":
	if (!Wagon->id(str))
	{
	    NFN("Exit what? The wagon?");
	    return 0;
	}
	break;
    }

    if (Wagon->query_leavable() || TP->query_wiz_level())
    {
	if (!objectp(Wagon))
	{
	    write("You jump out the emergency exit of the wagon.\n");
	    say(QCTNAME(TP) + " jumps out of the wagon.\n");
	    if (objectp(room = TP->query_prop(LIVE_O_LAST_ROOM)))
		TP->move_living("M", room);
	    else
		TP->move_living("M", TP->query_default_start_location());
	    write("There was a bug, please make a bug report.\n");
	    return 1;
        }
	write("You jump out of the carriage.\n");
	say(QCTNAME(TP) + " jumps out of the carriage.\n", TP);
	tell_room(ENV(Wagon), QCNAME(TP) +
		  " suddenly comes jumping out of the horse carriage!\n", TP);
	TP->move_living("M", ENV(Wagon));
	return 1;
    }
    write("No, you don't dare to do that - the wagon is moving, " +
	  "and you could get hurt!\n");
    return 1;
}

public string
exa_view()
{
    object  room,
           *objs,
           *dead;
    string  desc = "Outside of the wagon you see:\n";

    room = ENV(Wagon);
    if (TP->query_option(OPT_BRIEF))
	desc += CAP(room->short()) + ".\n";
    else
	desc += room->long();

    objs = all_inventory(room) - ({ Wagon });
		    
    if (sizeof(dead = FILTER_DEAD(objs)))
	desc += CAP(COMPOSITE_DEAD(dead)) + ".\n";
    if (sizeof(objs -= dead))
	desc += CAP(COMPOSITE_LIVE(objs)) + ".\n";

    return desc;
}

public string
exa_horses()
{
    int     nh;

    if (!(nh = Wagon->query_horses()))
	return "There are no horses pulling the wagon now.\n";
    else if (nh == 1)
	return BSN("There is only one horse pulling the wagon. It "
	  + "does not seem to have a problem doing the job, being "
	  + "a strong and fine horse, but the pace is not exactly "
	  + "great.");
    else 
	return BSN("There are " + LANG_WNUM(nh) + " horses pulling "
	  + "the wagon now. All look healthy and strong, and they "
	  + "pull the wagon at a fine pace.");
}

public void
init()
{
    ::init();
    add_action(leave_wagon, "jump");
    add_action(leave_wagon, "leave");
    add_action(leave_wagon, "out");
    add_action(leave_wagon, "exit");
}
