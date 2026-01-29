/*
 * hall2.c
 * 
 * Skippern 20(c)02
 *
 * The living room.
 */
#include "../../defs.h"
inherit DOL_STD + "inside";
inherit DOL_LIB + "fire_noise";

#include <macros.h>
#include <stdproperties.h>

/* Global Variables */
       int      F_alrm;
/* Prototypes */
       string   fireplace();
       int      fire(string arg);
       int      ext_fire(string arg);
       mixed    no_attack();
       mixed    no_steal();

void
create_inside()
{
    set_short("a living room");

    set_long("This is a lavish furnished living room, which also " +
	     "seem to be used as an office. Most of the west wall " +
	     "is occupied by a large bookshelf, and in front of the " +
	     "bookshelf stands a large desk. The desk covered with " +
	     "papers and scrolls of parchment. On the wall in front " +
	     "the desk hangs a map over Middle Earth marked with small " +
	     "red and blue pins stuck into it. Along the north and " +
	     "east walls are several large windows with long white curtains " +
	     "covering the view.\n");

    add_prop(ROOM_M_NO_ATTACK, &no_attack());
    add_prop(ROOM_M_NO_STEAL, &no_steal());
    add_prop(ROOM_I_NO_MAGIC, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_item( ({ "fireplace", "fire", "fire place" }), &fireplace() );
    add_item( ({ "shelf", "bookshelf", "large shelf", "large bookshelf" }),
	      "This large bookshelf occupy most of the west wall. " +
	      "The books looks boring, like books about trading, " +
	      "contact persons in various harbors and accounting.\n");
    add_item( ({ "desk", "large desk", "papers", "scrolls", "perchments", 
		     "perchment" }),
	      "This large desk is filled with papers and perchment scrolls " +
	      "showing what cargo various ships carry. The desk itself " +
	      "is made out of oak, and looks extremely sturdy.\n");
    add_item( ({ "map", "maps" }), "A large map showing Middle Earth hangs " +
	      "on the wall in front of the desk. Red and blue pins are put " +
	      "into the map showing important ports, and ports with regular " +
	      "traffic. Some lines are drawn on the map between some of " +
	      "the ports.\n");
    add_item( ({ "window", "windows", "north wall", "east wall" }), 
	      "Along the north and east walls " +
	      "are several large windows with long white curtains covering " +
	      "the view. The windows are reach all the way from the floor " +
	      "to the ceiling. You examine the glass closely and notice " +
	      "they are newly polished as there are not a single spot " +
	      "on them.\n");
    add_item( ({ "curtain", "curtains", "long curtains", "white curtains",
		     "long white curtains", "long white curtain", 
		     "long curtain","white curtain" }), 
	      "Long white curtains covers the " +
	      "windows. The curtains are of the same length as the windows " +
	      "and they are made of a very light cloth. The slightest " +
	      "movement in the air moves the curtains.\n");
    add_item( ({ "lavish furnished living room", "office" }),
	      "This is a lavish furnished living room, which also " +
	      "seem to be used as an office. Most of the west wall " +
	      "is occupied by a large bookshelf, and in front of the " +
	      "bookshelf stands a large desk. The desk covered with " +
	      "papers and scrolls of parchment. On the wall in front " +
	      "the desk hangs a map over Middle Earth marked with small " +
	      "red and blue pins stuck into it. Along the north and " +
	      "east walls are several large windows with long white " +
	      "curtains covering the view.\n");
    add_item( ({ "pins", "small pins", "red pins", "blue pins",
		     "small red pins", "small blue pins", 
		     "small red and blue pins" }), "This is small red and " +
	      "blue pins. They have a small needle as base with a small " +
	      "ball of red or blue painted wood attached to it. These " +
	      "pins are used to symbolise ports of importance on the maps.\n");
    add_item("walls", "Most of the west wall is occupied by a large " +
	     "bookshelf, and in front of the bookshelf stands a large desk. " +
	     "Along the north and east walls are several large windows with " +
	     "long white curtains covering the view.\n");

    add_exit(DOL_HILLS + "m-11/hall1", "south", 0, 1);

    reset_room();
}

void
reset_room()
{
    object ob;

    ::reset_room();
    if (!present("master"))
    {
        ob = clone_object(DOL_NPC + "m11-isaac");
	ob->move(this_object());
    }
}

void
init()
{
    ::init();
    add_action(fire, "light");
    add_action(fire, "fire");
    add_action(ext_fire, "extinguish");
}

mixed
no_attack()
{
    string r;

    switch(random(3))
    {
    case 1:
	r = "As you think of attacking you feel it would be to bad to break " +
	    "all this fine art on the walls. You decide not to attack.\n";
	break;
    default:
	r = "You are just about to attack when you get a feeling that your " +
	    "opponent is much stronger than you.\n";
    }
    return r;
}

mixed
no_steal()
{
    string r;
    switch(random(3))
    {
    default:
	r = "You feel bad about stealing while somebody is watching.\n";
    }
    return r;
}

int
fire(string arg)
{
    string verb = query_verb();

    if ( ((arg == "fireplace" || arg == "fire" || arg == "fire place") && 
	  verb != "fire") || (verb == "fire" && !arg))
    {
	if (FIREMASTER->query_smoke_n())
	{
	    notify_fail("It is allready burning.\n");
	    return 0;
	}
	write("You put some logs on the fire and lights a match. The dry " +
	      "wood ignites easily and the warmth from the fire comforts " +
	      "your body.\n");
	say(QCTNAME(this_player()) + " puts some logs into the fireplace " +
	    "and lights it.\n");
	FIREMASTER->fire_north();
	return 1;
    }
    notify_fail(CAP(verb) + " what?\n");
    return 0;
}

int
ext_fire(string arg)
{
    string verb = query_verb();

    if (arg == "fireplace" || arg == "fire" || arg == "fire place")
    {
        if (FIREMASTER->query_smoke_n() == 0)
        {
            notify_fail("What? Its allready extinguished.\n");
            return 0;
        }
        write("You put out the fire in the fireplace and cools down the " +
	      "ashes with a glass of water.\n");
        say(QCTNAME(this_player()) + " extinguishes the fireplace.\n");
	FIREMASTER->extinguish_north();
        return 1;
    }
    notify_fail(CAP(verb) + " what?\n");
    return 0;
}

string
fireplace()
{
    if (FIREMASTER->query_smoke_n())
	return "The fireplace is burning.\n";
    else
	return "The fireplace looks cold.\n";
}

void
do_noise()
{
    fire_noise("fireplace");
    F_alrm = set_alarm(itof(10+random(150)), 0.0, &do_noise());
}

void
start_noise()
{
    F_alrm = set_alarm(5.0, 0.0, &do_noise());
}

void
stop_noise()
{
    remove_alarm(F_alrm);
}
