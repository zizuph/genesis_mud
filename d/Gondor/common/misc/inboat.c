/*
 * /d/Gondor/common/misc/inboat.c
 *
 * The room inside /d/Gondor/common/obj/boat_obj.c
 *
 * Original version by Elessar
 *
 * Modification log:
 *  3-Dec-1996, Olorin: General revision.
 * 31-Mar-1998, Gnadnar: allow to row with the single "oar" object, too,
 *			 as long as they have two of them
 * 27-May-1999, Gnadnar: wash 'em ashore if they try to park midstream.
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include <config.h>
#include "/d/Gondor/defs.h"

#define	WEST_SHORE	1
#define	WEST_EDGE	2
#define	MID_RIVER	3
#define	EAST_EDGE	4
#define	EAST_SHORE	5

#define	PLAYER_I_JUST_ROWED	"_player_i_just_rowed"

#define	MAX_TIME	120.0	/* max time to row across before 
				 * we intervene. this is generous.
				 */

// Prototypes
public string	long_func();
public void	set_boat_loc(int i);
public void	setup_locs();
public void	wash_ashore(string name);

// Global variables:
static int	Boat_loc,
		Wash_alarm_id,
		Target_shore;
static string	Shore_east, 
		Shore_west;
static object	Boat_obj;

public void
create_room()
{
    set_short("in a rowing boat");
    set_long(long_func);
    set_noshow_obvious(1);
    set_boat_loc(1);
    setup_locs();
    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(ROOM_I_HIDE, 50);
}

public string
long_func()
{
    string longstr = "You are sitting in a little wooden boat, currently ";
    
    if (Boat_loc == WEST_SHORE) 
	longstr += "by the western riverbank of the River Anduin.";
    else if (Boat_loc == EAST_SHORE) 
	longstr += "by the eastern riverbank of the River Anduin.";
    else 
	longstr += "out on the mighty River Anduin.";
    return BSN(longstr);
}

public int
leave_boat()
{
    if (Boat_loc == WEST_SHORE)
    {
	TP->move_living("ashore",Shore_west);
	TP->remove_prop(PLAYER_I_JUST_ROWED);
	return 1;
    }

    if (Boat_loc == EAST_SHORE)
    {
	TP->move_living("ashore",Shore_east);
	TP->remove_prop(PLAYER_I_JUST_ROWED);
	return 1;
    }

    write("You don't dare to leave the boat and dive into the river!\n");
    return 1;
}

public int
row(string str)
{
    object	*inv, pl;
    int		s, fat, maxfat;
    mixed	*alarm_info;

    if (!strlen(str))
    {
	NFN("Row in which direction?");
	return 0;
    }
    inv = all_inventory(TP);
    if (!sizeof(filter(inv, &->id("oars"))))
    {	
    	s = sizeof(inv = filter(inv, &->id("oar")));
	if (!s)
	{
	    NF0("How can you row without oars?\n");
	}
	if (s == 1)
	{
	    NF0("You need two oars to row the boat.\n");
	}
    }

    fat = TP->query_fatigue();
    maxfat = TP->query_max_fatigue();
    if (((fat * 100) / maxfat) < 20)
    {
	write("You are too tired to row.\n");
	return 1;
    }
    TP->add_fatigue((maxfat / -40));

    if (str == "east") 
    {
	if (Boat_loc >= EAST_SHORE) 
	{
	    write("You cannot row the boat any further east.\n"
               +  "You are already by the east bank of the river!\n");
	    return 1;
	}

	if (Boat_loc == EAST_EDGE)
	{
	    write("The boat lands at the east riverbank.\n");
	    say(QCTNAME(TP)+" rows the boat to the east riverbank.\n");
	    Boat_obj->move(Shore_east);
	    tell_room(Shore_east, QCNAME(TP)+" comes rowing in a boat.\n");
	    Boat_loc = EAST_SHORE;

	    s = TP->query_prop(PLAYER_I_JUST_ROWED);
	    if (s < 2)
	    {
		TP->add_prop(PLAYER_I_JUST_ROWED, ++s);
	    }
	    else
	    {
		/* N.B. this doesn't prevent triggers to
		 * land, leave boat, enter boat and row away again
		 */
		TP->set_fatigue(0);
		TP->remove_prop(PLAYER_I_JUST_ROWED);
	    }

	    if (Wash_alarm_id)
	    {
		if (sizeof(alarm_info = get_alarm(Wash_alarm_id)))
	    	{
		    remove_alarm(Wash_alarm_id);
		}
		Wash_alarm_id = 0;
	    }
	    return 1;
	}

	write("You row east across the mighty River Anduin, "+
		"braving the currents.\n");
	SAY(" rows the boat east across the river currents.");
	Boat_obj->move(OSG_DIR + "riverroom");

	if (Boat_loc == WEST_SHORE)
	{
	    /* launching boat */
	    tell_room(Shore_west,
		  "The boat leaves onto the waters of the Anduin.\n");

	    if (!Wash_alarm_id)
	    {
		Target_shore = EAST_SHORE;
		Wash_alarm_id = set_alarm(MAX_TIME, 0.0,
		    &wash_ashore(TP->query_name()));
	    }
	}
	++Boat_loc;
	return 1;
    }

    if (str == "west") 
    {
	if (Boat_loc <= WEST_SHORE)
	{
	    write("You cannot row the boat any further west.\n"
		+ "You are already by the west bank of the river!\n");
	    return 1;
	}

	if (Boat_loc == WEST_EDGE)
	{
	    write("The boat lands at the west riverbank.\n");
	    say(QCTNAME(TP)+" rows the boat to the west riverbank.\n");
	    Boat_obj->move(Shore_west);
	    Boat_loc = WEST_SHORE;
	    tell_room(Shore_west, QCNAME(TP)+" comes rowing in a boat.\n");

	    s = TP->query_prop(PLAYER_I_JUST_ROWED);
	    if (s < 2)
	    {
		TP->add_prop(PLAYER_I_JUST_ROWED, ++s);
	    }
	    else
	    {
		/* N.B. this doesn't prevent triggers to
		 * land, leave boat, enter boat and row away again
		 */
		TP->set_fatigue(0);
		TP->remove_prop(PLAYER_I_JUST_ROWED);
	    }

	    if (Wash_alarm_id)
	    {
		if (sizeof(alarm_info = get_alarm(Wash_alarm_id)))
	    	{
		    remove_alarm(Wash_alarm_id);
		}
		Wash_alarm_id = 0;
	    }
	    return 1;
	}

	write("You row west across the currents of the mighty "+
		"River Anduin.\n");
	SAY(" rows the boat west across the currents of the river.");
	Boat_obj->move(OSG_DIR  + "riverroom");

	if (Boat_loc == EAST_SHORE)
	{
	    /* launching boat */
	    tell_room(Shore_east,
		"The boat leaves onto the waters of the Anduin.\n");

	    if (!Wash_alarm_id)
	    {
		Target_shore = WEST_SHORE;
		Wash_alarm_id = set_alarm(MAX_TIME, 0.0,
		    &wash_ashore(TP->query_name()));
	    }
	}
	--Boat_loc;
	return 1;
    }

    if (str == "north" ||
	str == "upstream")
    {
	write("The current is too strong, you are unable to row upstream.\n");
	return 1;
    }
    if (str == "south" ||
	str == "downstream")
    {
	write(BSN("You row south for a while, but a swift and swirling "+
		  "current returns you to where you were."));
	return 1;
    }

    NFN("Row where?");
    return 0;
}

public void
set_boat_loc(int i)
{
    Boat_loc = i;
}

public void
set_boat_obj(object obj)
{
    Boat_obj = obj;
}

public void
setup_locs()
{
    Shore_west = OSG_DIR + "boatplace";
    Shore_east = ITH_DIR + "osgiliath/boatplace";
}

public int
query_livings()
{
  return sizeof(FILTER_LIVE(all_inventory(TO)));
}

public void
enter_inv(object obj, object from)
{
    if (living(obj)) 
    {
	/* check for 3 here, not 2 -- for some reason, obj is
	 * already in the boat!
	 */
	if (query_livings() > 3)
	{
	    obj->move(from);
	    tell_object(obj,"The boat only holds three persons.\n");
	    tell_room(this_object(), QCNAME(obj)+
		" tried to enter the boat, but there's not enough room.\n");
	    return;
	}
    }
    ::enter_inv(obj,from);
}

int
do_light_update(string str)
{
  if (!str) 
      return 0;
  write("Please make a bug report. In the report, "+
	"please give these two numbers:\n");
  write("OBJ_I_LIGHT: " + TO->query_prop(OBJ_I_LIGHT) + 
	", ROOM_I_LIGHT: " + TO->query_prop(ROOM_I_LIGHT) + ".\n");
  TO->update_light();
  write("Hope this helped!\n");
  write("Please don't forget the bug report, "+
	"if you want to have this fixed for good!\n");
  return 1;
}

public void
init()
{
    ::init();
    add_action(row, "row");
    add_action(leave_boat, "leave");
    add_action(leave_boat, "exit");
    add_action(leave_boat, "out");
    add_action(leave_boat, "disembark");
    add_action(do_light_update, "_update_light");
}


/*
 * Function name:	wash_ashore
 * Description	:	they've loitered too long in mid-stream;
 *			wash 'em ashore
 * Arguments	:	string name -- the person who was rowing
 */
public void
wash_ashore(string name)
{
    object	pl, env;

    Wash_alarm_id = 0;
    if (Boat_loc <= WEST_SHORE ||
	Boat_loc >= EAST_SHORE)
    {
	return;
    }

    if (objectp(pl = find_living(LOW(name))))
    {
	env = ENV(pl);
	if (env == TO)
	{
	    tell_object(pl, "The effort of rowing exhausts you.\n");
	    pl->set_fatigue(0);
	}
	else if (file_name(env) == OWN_STATUE &&
		 pl->query_prop(LIVE_O_LAST_ROOM) == TO)
	{
	    name += " (netdead)";
	    pl->set_fatigue(0);
	}
    }

    Boat_loc = Target_shore;
    if (Target_shore == WEST_SHORE)
    {
	tell_room(this_object(),
	    "The currents of the mighty Anduin sweep the boat " +
	    "to the west riverbank.\n");
	Boat_obj->move(Shore_west);
	tell_room(Shore_west, QCNAME(pl)+" is swept ashore in a boat.\n");
    }
    else
    {
	tell_room(this_object(),
	    "The currents of the mighty Anduin sweep the boat " +
	    "to the east riverbank.\n");
	Boat_obj->move(Shore_east);
	tell_room(Shore_east, QCNAME(pl)+" is swept ashore in a boat.\n");
    }

} /* wash_ashore */
