/*
 * West hallway in the balance puzzle.
 *
 * This is the first puzzle in the area:
 *   The hallway is balance on a torc on the center of the
 *   hallway. The amount of weight on either end of the
 *   hallway determines the level of the hallway. In the
 *   east enter of the hallway (~Avenir/union/tomb/tilt_hall_e)
 *   is a hole that the player needs to enter. If the hallway
 *   is too high in the east, then the floor of the hallway
 *   will be obscuring it. If it is too low, then the hole
 *   will be too high for the player to be able to enter. The trick
 *   is to drop the correct weight of objects on either end of the
 *   hall so that the hallway balances out and the player can enter
 *   the hall. Mass objects can be used in the form of the urns
 *   (~Avenir/union/tomb/obj/urn), a number of which can be
 *   found in the False Tomb (~Avenir/union/tomb/false_tomb), but
 *   any objects with weight will work. The puzzle is even
 *   more tricky, since, of course, the player himself counts
 *   as weight, so when the player moves back and forth, the
 *   wight on either end of the hallway will be recalculated
 *   and he can throw off the balance!
 *
 *       Cirion, May 28 1996
 */
#pragma strict_types
#include "defs.h"

inherit "/std/room";

#include <math.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

public object thalle;
public int level, /* Range from -200 - 200 (centimeters) */
	   weight_alarm,
	   weight_here,
	   weight_there;


public void
reset_room(void)
{
    object *stuff = FILTER_DEAD(all_inventory(TO));
    int size = sizeof(stuff);

    if (!size)
	return;

    tell_room(TO, "The room suddenly lurches, and "+
	COMPOSITE_DEAD(stuff) + "slide"+
	(size == 1 ? "s": "") +" down to the west.\n");

    object tomb = find_object(FALSE_TOMB);
    if (objectp(tomb)) stuff->move(tomb);
}

public void
create_room(void)
{
    set_short("west end of hallway");
    set_long("This is the west end of a long, straight hallway. "+
	"The hall does not seem to lead anywhere, and the walls to "+
	"both the north and south are made from smooth blocks "+
	"of grey stone. @@level_desc@@ To the west, the hall "+
	"tapers to a narrow slit that runs the from the floor "+
	"to the ceiling, just wide enough to squeeze through."+
	"@@see_east@@@@live_east@@\n");

    add_item(({"mark","marks","scrape marks"}),
	"The north, south, and west walls all have long vertical marks "+
	"against them, is if something heavy had been moving along them.\n");
    add_item(({"floor","ground"}), "The floor is made from wide stone "+
	"tiles. There is a strange protrusion rising from the floor "+
	"to the east.\n");
    add_item(({"protrusion","bump"}), "To the east, exactly halfway "+
	"between this end of the hall and the east end, the tiles are "+
	"slightly curved, as if there was something round beneath them.\n");
    add_item(({"tile","tiles","stone tiles"}),
	"The tiles are evenly spaced, made from a strong, dark stone.\n");
    add_item(({"wall","walls"}), "The walls to the north and south are "+
	"made from massive blocks of grey stone, placed together so "+
	"there are no seams.\n");
    add_item("slit", "The western of the end of the hallway tapers off "+
	"to a narrow slit running from floor to ceiling, through which "+
	"can be seen a large room.\n");

    add_cmd_item(({"tile","tiles","stone tiles","floor","ground"}),
	({"break","smash","destroy","lift","move","push","pull"}),
	"The stone tiles on the floor are hard and unyielding.\n");

    add_exit(THALLE, "east", "@@go_east@@");
    add_exit(FALSE_TOMB, "west", "@@go_west@@");
}

public string
see_east(void)
{
    if (!thalle && !objectp(thalle = find_object(THALLE)))
	return "";

    object *stuff = FILTER_DEAD(all_inventory(thalle));

    if (!sizeof(stuff))
	return "";

    return " At the east end of the hall, you can see "+
	COMPOSITE_DEAD(stuff) + ".";
}

public string
live_east(void)
{
    if (!thalle && !objectp(thalle = find_object(THALLE)))
	return "";

    object *stuff = FILTER_LIVE(all_inventory(thalle));

    if (!sizeof(stuff))
	return "";

    return " Standing at the east end of the hall is "+
	COMPOSITE_LIVE(stuff) + ".";
}

public string
level_desc(void)
{
    switch(-level)
    {
    case -300 .. -150:
	return "The hallway rises steeply to the east, climbing "+
	    "at an almost impossible incline.";
    case -149 .. -100:
	return "The hallway rises sharply to the east, rising "+
	    "at a steep angle.";
    case -99 .. -50:
	return "The hallway rises back east at a steep angle.";
    case -49 .. -30:
	return "The hallway rises east at a steep slope.";
    case -29 .. -20:
	return "The hallway rises to the east at a slope.";
    case -19 .. -5:
	return "The hallway rises very slightly to the east.";
    case -4 .. 4:
	return "The hallway leads back east, perfectly straight "+
	    "and level.";
    case 5 .. 19:
	return "The hallway drops very slightly to the east.";
    case 20 .. 29:
	return "The hallway drops down to the east.";
    case 30 .. 49:
	return "The hallway leads east down a steep slope.";
    case 50 .. 99:
	return "The hallway drops down sharply to the east.";
    case 100 .. 149:
	return "The hallway drops very steeply to the east, "+
	    "making your footing here difficult.";
    case 150 .. 300:
	return "The hallway drops down to the east at an extremely "+
	    "steep angle, making footing here very treacherous.";
    }
}

public int
go_east(void)
{
    write("As you walk east, the hall floor beneath lurches "+
	"sickeningly.\n");
    return 0;
}

public int
go_west(void)
{
    if (TP->query_encumberance_volume() > 40)
    {
	write("You are carrying too much to fit through the "+
	    "narrow passage.\n");
	return 1;
    }

    write("You squeeze through the narrow slit to the west.\n");
    say(QCTNAME(TP) +" squeezes through the narrow slit to the west.\n");
    return 0;
}

/*
 * all_weight gives the weight of everything in the
 * room.
 */
public varargs int
all_weight(object what = this_object())
{
    int total;

    foreach(object inv: deep_inventory(what))
    {
	int mass = inv->query_prop(CONT_I_WEIGHT);
	if (!mass) mass = inv->query_prop(OBJ_I_WEIGHT);
	total += mass;
    }

    return max(0, total);
}

public varargs void
update_weight(int flag)
{
    int oldlevel = level;
    string str;

    weight_alarm = 0;
    weight_here  = all_weight();
    weight_there = THALLE->all_weight();

    if (!flag)
	THALLE->update_weight(1);

    level = (weight_here / 100) - (weight_there / 100);
    level = max(min(level, 200), -200);

    if (level == oldlevel)
	return;

    switch(ABS(level - oldlevel))
    {
    case 0 .. 10:	str = "slightly ";	break;
    case 11 .. 25:	str = "somewhat ";	break;
    case 26 .. 60:	str = "";		break;
    case 61 .. 100:	str = "steeply ";	break;
    case 101 .. 150:	str = "sharply ";	break;
    case 151 .. 250:	str = "drasticly ";	break;
    default:		str = "sickeningly ";	break;
    }

    if (level > -5 && level < 5)
    {
	tell_room(TO, "The hallway "+ (oldlevel < 0 ? "lowers" : "raises") +
	    " " + str + "until it is nearly level with the square hole "+
	    "in the east wall.\n");
    }
    else if (oldlevel < 0 && level > 0)
    {
	tell_room(TO, "This end of the hallway drops downwards, "+
	    "and the east end of the hallway rises.\n");
    }
    else if (oldlevel > 0 && level < 0)
    {
	tell_room(TO, "The hallway rises suddenly, "+
	    "and the east end of the hallway seems to drop down.\n");
    }
}

public void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);
    if (!weight_alarm)
	weight_alarm = set_alarm(1.0, 0.0, update_weight);
}

public void
leave_inv(object to, object from)
{
    ::leave_inv(to, from);
    if (to == find_object(THALLE))
	return;

    if (!weight_alarm)
	weight_alarm = set_alarm(1.0, 0.0, update_weight);
}
