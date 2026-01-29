#pragma strict_types

inherit "/std/room";
inherit "/d/Avenir/inherit/room_tell";

#include "hob.h"

public static int l1, l2, l3, need_exit;
public static string *long1, *long2, *long3;
public static string *shorts, extra_long = "";

private static mapping room_opp = ([
	 "down" : "up",                "up" : "down",
	   "in" : "out",              "out" : "in",
	"north" : "south",          "south" : "north",
	 "east" : "west",            "west" : "east",
    "northeast" : "southwest",  "southwest" : "northeast",
    "northwest" : "southeast",  "southeast" : "northwest",
]);

static void
update_long(void)
{
    set_long(long1[l1] +" "+ long2[l2] +" "+
	long3[l3] + extra_long +"\n");
}

static void
update_items(void)
{
}

static void
update_noise(void)
{
}

/*
 * Extra fatigue for exits, because of needing to be
 * careful due to rubble and pitted and damaged walking surfaces.
 */
static int
ran_tired(void)
{
    return random(3) + 1;
}
/*
 * Just some random messages for extra flavour.
 */
public static string *moves = ({
    "You stumble your way through the rubble.",
    "You nearly twist your ankle on a shallow depression.",
    "You manage to sidestep some dangerous looking depressions.",
    "You avoid stumbling over a pile of rubble.",
});

static int
ran_move(void)
{
    if (!random(5)) {
	write(one_of_list(moves) + "\n");
    }
    return 0;
}

static string *
ran_exit(string room, string *dirs)
{
    if (!strlen(room) || !sizeof(dirs))
	return ({});

    string dir = one_of_list(dirs);

    if (!strlen(dir))
	return ({});

    set_alarm(0.0, 0.0, &(room)->add_exit(
	    file_name(this_object()), room_opp[dir],
	    ran_move, ran_tired));

    add_exit(room, dir, ran_move, ran_tired);
    return dirs - ({ dir });
}

static void
config_random(void)
{
    /* This is a stub to be redefined by actual rooms. */
}

static nomask void
make_me_random(void)
{
    config_random();

    /* Don't try to load unless we've been set. */
    if (!sizeof(shorts))
	return;

    set_short(one_of_list(shorts));
    /*
     * long1, long2, long3 are defined inside include files.
     */
    l1 = random(sizeof(long1));
    l2 = random(sizeof(long2));
    l3 = random(sizeof(long3));

    update_long();
    update_items();
    update_noise();
}

public void
hob_room(void)  { /* Placeholder */ }

static nomask void
create_room(void)
{
    set_long("ERROR: This is a BUG!\n");
    set_short("ERROR: This is a BUG!");

    /* Constant properties. */
    IN; LIGHTER;

    /* For the magic map. */
    add_prop(ROOM_S_MAP_FILE, "utterdark_hobs.txt");

    /* Generate short + long */
    make_me_random();
    /* Customize */
    hob_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
	start_room_tells();
}
