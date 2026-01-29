#pragma strict_types
/*
 * ~/priv.c
 *
 * Inheritable for Private Rooms in the Bath.
 *
 * Revisions:
 *   Lucius, ??? 2007: Created - moved common code here.
 *   Lucius, Sep 2008: Removed host/invite code which never
 *                     worked properly. Also, teleport ban.
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "priv.h"

inherit BATH_ROOM;
inherit "/lib/commands";
inherit "/d/Avenir/inherit/emotes";

#define TP	this_player()


public int
query_prevent_snoop(void)	{ return 1; }

public int
clean_room(void)
{
    object *objs = all_inventory() - accept_here;

    // Player check.
    if (sizeof(filter(objs, query_interactive)))
	return 0;

    // Reset doors
    bath_door = bath_door->query_other_door();
    bath_door->auto_close(1);
    bath_door->set_key(random(10000) * -1);

#if 0
    // Room empty, clean it!
    objs->remove_object();

    // Re-fill the shelf.
    present("_ave_bath_shelf")->fill_shelf();
    return 1;
#else
    // Just unload the room.
    set_alarm(0.0, 0.0, remove_object);
    return 1;
#endif
}

public string
read_sign(void)
{
    return "You may leave this room whenever you wish using the "+
	"exit 'out' to take you back to where you were before. "+
	"You may also 'emote' freely here. Refreshments and bathing "+
	"supplies are on the shelf.\n\n    Pashat!\n";
}

static void
create_priv_bath(void)	{ }


static nomask void
create_bath_room(void)
{
    create_priv_bath();

    PRIV;

    if (file_name(this_object()) == BATH_PRIV)
	return;

    add_object(COM +"obj/bench");
    add_object(BATH +"obj/shelves", 1, &->fill_shelf());
}

public int
do_out(void)
{
    object last = TP->query_prop(LIVE_O_LAST_ROOM);

    if (!last || last == environment(TP))
	last = find_object(BATH + "outside");

    say(QCTNAME(TP) +" leaves out.\n");
    TP->move_living("X", last, 0);
    return 1;
}

/*
public int
do_emote(string str)
{
    if (!strlen(str))
	return notify_fail("Emote what?\n");

    write("You emote: "+ TP->query_The_name() +" "+ str + "\n");
    say(QCTNAME(TP) + " " + str + "\n");
    return 1;
}
 */

public int
do_swim(string str)
{
    if (!TP->query_prop(IN_POOL))
        return notify_fail("You aren't in the pool.\n");

    write("You swim around the pool at a languid pace.\n");
    say(QCTNAME(TP) + " swims lazily around the pool.\n");
    return 1;
}

public int
do_wash(string str)
{
    object ob;

    if (!TP->query_prop(IN_POOL))
        return notify_fail("You aren't in the pool.\n");

    write("You wash away the marks of battle and travel.\n");
    say(QCTNAME(TP) + " washes away layers of dirt and grime.\n");

    while(ob = present("dirty",TP))
    {
        TP->catch_tell("You feel much less dirty now.\n");
        ob->remove_object();
    }

    return 1;
}

public int
do_splash(string str)
{
    if (!TP->query_prop(IN_POOL))
        return notify_fail("You aren't in the pool.\n");

    if (!strlen(str))
    {
        write("You splash playfully in the water, feeling "
           +"like a child again.\n");
        all(" splashes noisily about in the pool.\n");
        return 1;
    }

    object *oblist = parse_this(str, "[water] [at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Splash who?\n");
        return 0;
    }

    target(" splashes water in your face.", oblist);
    actor("You splash", oblist, " in the face with water.");
    all2act(" splashes", oblist, " in the face with water.");
    return 1;
}

public int
do_paddle(string str)
{
    if (!TP->query_prop(IN_POOL))
        return notify_fail("You aren't in the pool.\n");

    write("You skillfully tread water.\n");
    say(QCTNAME(TP) + " looks like a dog paddling about in the pool.\n");
    return 1;
}

public int
do_dead(string str)
{
    if (!TP->query_prop(IN_POOL))
        return notify_fail("You aren't in the pool.\n");

    write("Rolling onto your back, you float contentedly in the water.\n");
    say(QCTNAME(TP) + " floats on the surface of the water.\n");
    return 1;
}

public int
do_dive(string str)
{
    if (!TP->query_prop(IN_POOL))
    {
        notify_fail("Its too dangerous for you to dive into the pool from "+
	    "outside. It is too shallow.\n");
	return 0;
    }

    write("You dive under the water.\n");
    say(QCTNAME(TP) + " disappears beneath the water's surface.\n");
    return 1;
}

public int
do_dunk(string str)
{
    object *oblist;

    if (!TP->query_prop(IN_POOL))
        return notify_fail("You aren't in the pool.\n");

    if (!strlen(str))
    {
        write("You dunk beneath the water. You can hear "
            +"the sound of water lapping the pool's edge.\n");
        all(" dunks beneath the pool's surface.\n");
        return 1;
    }

    oblist = parse_this(str, "[beneath] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Dunk who?\n");
        return 0;
    }

    actor("You dunk", oblist, " underneath the water.");
    all2act(" dunks", oblist, " under the water.");
    target(" dunks your head beneath the water.", oblist);
    return 1;
}

public int
do_enter(string str)
{
    if (!strlen(str) || !parse_command(str, ({}),
	    " [the] 'pool' / 'bath' / 'water'"))
    {
	notify_fail("Enter what? Enter the pool?\n");
	return 0;
    }

    if (TP->query_prop(IN_POOL))
    {
	write("You're already in the pool!\n");
	return 1;
    }

    write("You sink slowly into the luscious warmth.\n"+
	"Perfumed with oils, the water's silken "+
	"caress is reminiscent of a lover's embrace.\n");
    say(QCTNAME(TP) + " enters the pool.\n");

    TP->add_prop(IN_POOL, 1);
    TP->set_no_show_composite(1);
    return 1;
}

public int
do_exit(string str)
{
    if (!strlen(str) || !parse_command(str, ({}),
	    " [the] 'pool' / 'bath' / 'water'"))
    {
	notify_fail("Exit what? Exit the pool?\n");
	return 0;
    }

    if (!TP->query_prop(IN_POOL))
    {
        write("You aren't in the pool.\n");
	return 1;
    }

    TP->remove_prop(IN_POOL);
    TP->unset_no_show_composite();

    write("You leave the warm embrace of the fragrant water.\n");
    say(QCTNAME(TP) + " exits the pool.\n");
    return 1;
}

static string
map_live(object pl)
{
    if (pl == TP)
        return "you";

    return pl->query_the_name(TP);
}

public string
pool_desc(void)
{
    int size;
    object *pls;
    string *who, str = "   ";

    pls = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), TP);
    pls = filter(pls, &->query_prop(IN_POOL));

    if (!(size = sizeof(pls)))
	return "\n";

    pls->set_no_show_composite(0);
    who = map(pls, map_live);
    pls->set_no_show_composite(1);

    if (size == 1 && pls[0] == TP)
    {
	str += "You are soaking yourself in the pool.";
    }
    else
    {
	str += capitalize(COMPOSITE_WORDS(who)) +
	    (size == 1 ? " is " : " are ") +
	    "soaking in the pool of warm, fragrant water.";
    }

    return str + "\n";
}

public void
leave_inv(object ob, object to)
{
    if (ob->query_prop(IN_POOL))
    {
        ob->remove_prop(IN_POOL);
        ob->unset_no_show_composite();
    }

    ::leave_inv(ob, to);
}

public void
init(void)
{
    ::init();

//    add_action(do_emote,  "emote");
//    add_action(do_emote,  ":");
    init_emotes();
    add_action(do_enter,  "enter");
    add_action(do_exit,   "exit");
    add_action(do_exit,   "leave");
    add_action(do_swim,   "swim");
    add_action(do_wash,   "wash");
    add_action(do_wash,   "bathe");
    add_action(do_splash, "splash");
    add_action(do_paddle, "paddle");
    add_action(do_paddle, "tread");
    add_action(do_dead,   "float");
    add_action(do_dive,   "dive");
    add_action(do_dunk,   "dunk");
    add_action(do_out,    "out");
}
