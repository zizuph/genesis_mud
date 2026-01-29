#pragma strict_types
// Tent Inside
// creator(s):   Zielia & Lucius 2007
// last update:
// purpose:      Fun tent players can carry around for roleplay.
// note:         some base code from Krynn army tents by Aridor
// bug(s):
// to-do:
/*
 *
 * To customize the look of the inner tent room, after inheriting mask
 * the tent_long() function to return the desired string description.
 *
 * 2021-01-21 - Cotillion
 * - Removed no scry and invis detection code which is entirely 
 *   unreasonable for a tent.
 */
#include "/d/Avenir/include/basic.h"

#include <config.h>
#include <stdproperties.h>

inherit "/std/room";
inherit "/d/Avenir/inherit/emotes";

#define PLAYER_S_LD_IN_ROOM "_player_s_ld_in_room"

public static int prop_locked;
public static object room, tent;
/*
 * Block functions disabling setting of calculated properties
 */
public nomask int add_prop_room_i_light(void)      { return prop_locked; }
public nomask int remove_prop_room_i_light(void)   { return 1; }
/*
 * Keep magical darkness outside the tent.
 * If there is light outside the tent, let in 'light / 2'.
 */
private int
tent_light(void)
{
    int val = room->light();
    return val = max(0, (val > 1 ? val / 2 : val));
}

public string
tent_long(void)
{
    string str = "You are inside a small camping tent. Made from thin, "+
	"breathable silk, it is a rather bare, but cozy shelter. ";

    if (tent_light())
	str += "Light filters through the silk, illuminating the tent. ";
	
    if (tent->query_closed())
    {
	str += "A silk tent flap leading out has been laced closed.";    
    }
    else
    {
	str += "A small gap in the silk reveals a tent flap which will "+
	"take you out. The tent flap can also be laced closed for more "+
	"security.";   
    }
	    
    return str +"\n";
}

public void
create_tent(void)
{
    /* Default / Sample tent. */
    set_short("inside a small camping tent");
}

static nomask void
create_room(void)
{
    setuid();
    seteuid(getuid());	

    prop_locked = 0;
    add_prop(ROOM_I_HIDE,  -1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
    add_prop(ROOM_I_LIGHT, tent_light);
    add_prop(ROOM_I_INSIDE, 1);
    prop_locked = 1;

    create_tent();

    set_long(&tent_long());
}

public int
exit_tent(void)
{
    if (tent->query_closed())
    {
	write("The tent flap is laced closed.\n"+
	    "You need to unlace it first.\n");
	return 1;    
    }

    return 0;
}

public object
set_tent_outside(object ob)
{
    tent = ob;	
    room = ENV(ob);

    add_exit(file_name(room), "out", exit_tent);
    add_prop(ROOM_S_EXIT_FROM_DESC, "from the "+ tent->short() +".");
}

public nomask object
query_tent_outside(void)	{ return tent;	}

public nomask object
query_room_outside(void)	{ return room;	}

public nomask int
query_syb_tent(void)		{ return 1;	}

public nomask int
f_lace(string str)
{
    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) +" what?\n");
	return 0;
    }

    if (!parse_command(str, ({ }), "[the] [tent] 'flap'"))
    {
	notify_fail(CAP(query_verb()) +" what?\n");
	return 0;
    }

    return tent->lace_syb_tent(TO);
}

public nomask int
f_unlace(string str)
{
    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) +" what?\n");
	return 0;
    }

    if (!parse_command(str, ({ }), "[the] [tent] 'flap'"))
    {
	notify_fail(CAP(query_verb()) +" what?\n");
	return 0;
    }

    return tent->unlace_syb_tent(TO);
}

/* Try to kick out people and things somewhat safely. */
public void
remove_object(void)
{
    string X = "from the tent";
    object *obs = all_inventory();

    foreach(object ob : obs)
    {
	if (!living(ob))
	{
	    if (ob->move(room))
		ob->move(room, 1);

	    continue;
	}

	if (ob->move_living(X, room) && ob->move(room, 1))
	{
	    if (query_interactive(ob))
		ob->move(ob->query_default_start_location(), 1);
	}
    }

    all_inventory()->remove_object();
    ::remove_object();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    /*
     * This is a cloned room that gets destroyed when tent is packed.
     * If a player linkdies here, have them recover at the room it was 
     * set up in.
     */
    if (living(ob) && objectp(to) && file_name(to) == OWN_STATUE)
	ob->add_prop(PLAYER_S_LD_IN_ROOM, file_name(room));
}

public  void
init(void)
{
    ::init();

    add_action(   f_lace, "lace"   );
    add_action(   f_lace, "close"  );
    add_action( f_unlace, "unlace" );
    add_action( f_unlace, "open"   );    

    init_emotes();
}

public nomask int
query_prevent_snoop(void)	{ return 1; }

