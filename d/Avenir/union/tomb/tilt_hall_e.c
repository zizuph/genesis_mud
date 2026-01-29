/*
 * East Hallway, where the hole is.
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
#include <language.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>


public object thallw;
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
    set_short("east end of hallway");
    set_long("This is the east end of a long, straight hallway. "+
      "The hall does not seem to lead anywhere, and the walls to "+
      "both the north and south are made from smooth blocks "+
      "of grey stone.@@see_hole@@@@level_desc@@@@see_west@@"+
      "@@live_west@@\n");

    add_item(({"wall","east wall"}), "The east wall is made from "+
      "large, smooth blocks of a dull grey stone. There are marks "+
      "along the wall, as if something has been scraping against it."+
      "@@see_hole@@@@see_west@@\n");
    add_item(({"mark","marks","scrape marks"}),
      "The north, south, "+"and east walls all have long vertical "+
      "marks against them, is if something heavy had been moving "+
      "along them.\n");
    add_item(({"floor","ground"}), "The floor is made from wide stone "+
      "tiles. There is a strange protrusion rising from the floor to "+
      "the west.\n");
    add_item(({"protrusion","bump"}), "To the west, exactly halfway "+
      "between this end of the hall and the west end, the tiles are "+
      "slightly curved, as if there was something round beneath them.\n");
    add_item(({"tile","tiles","stone tiles"}),
      "The tiles are evenly spaced, made from a strong, dark stone.\n");
    add_item(({"hole","tunnel"}), "@@hole_desc@@");
    add_item(({"wall","walls"}), "The walls to the north and south are "+
      "made from massive blocks of grey stone, placed together so "+
      "there are no seams.\n");

    add_cmd_item(({"up the wall","wall","up wall","east wall"}),"climb",
      "The wall is too steep and smooth for you to climb.\n");
    add_cmd_item(({"tile","tiles","stone tiles","floor","ground"}),
      ({"break","smash","destroy","lift","move","push","pull"}),
      "The stone tiles on the floor are hard and unyielding.\n");

    add_exit(THALLW, "west", "@@go_west@@");
}

public string
see_west(void)
{
    if (!thallw && !objectp(thallw = find_object(THALLW)))
	return "";

    object *stuff = FILTER_DEAD(all_inventory(thallw));

    if (!sizeof(stuff))
	return "";

    return " At the west end of the hall, you can see "+
	COMPOSITE_DEAD(stuff) + ".";
}

public string
live_west(void)
{
    if (!thallw && !objectp(thallw = find_object(THALLW)))
	return "";

    object *stuff = FILTER_LIVE(all_inventory(thallw));

    if (!sizeof(stuff))
	return "";

    return " Standing at the west end of the hall is "+
	COMPOSITE_LIVE(stuff) + ".";
}

public string
level_desc(void)
{
    switch(-level)
    {
    case -300 .. -150:
	return "The hallway rises steeply to the west, climbing "+
	    "at an almost impossible incline.";
    case -149 .. -100:
	return "The hallway rises sharply to the west, rising "+
	    "at a steep angle.";
    case -99 .. -50:
	return "The hallway rises back west at a steep angle.";
    case -49 .. -30:
	return "The hallway rises west at a steep slope.";
    case -29 .. -20:
	return "The hallway rises to the west at a slope.";
    case -19 .. -5:
	return "The hallway rises very slightly to the west.";
    case -4 .. 4:
	return "The hallway leads back west, perfectly straight "+
	    "and level.";
    case 5 .. 19:
	return "The hallway drops very slightly to the west.";
    case 20 .. 29:
	return "The hallway drops down to the west.";
    case 30 .. 49:
	return "The hallway leads west down a steep slope.";
    case 50 .. 99:
	return "The hallway drops down sharply to the west.";
    case 100 .. 149:
	return "The hallway drops very steeply to the west, "+
	    "making your footing here difficult.";
    case 150 .. 300:
	return "The hallway drops down to the west at an extremely "+
	    "steep angle, making footing here very treacherous.";
    }
}

public string
see_hole(void)
{
    if (level > 5)
    {
	return " A square hole leads into the east wall, "+
	    "high above your head.";
    }
    else if (level < -5 && level > -10)
    {
	return " At the base of the east wall, part of a square "+
	    "hole can be seen, but it is mostly covered by the "+
	    "edge of the floor.";
    }
    else if (level >= -5 && level <= 5)
    {
	return " Leading into the east wall is a perfectly square hole, "+
	    "made from smoothed blocks of masonry.";
    }
    else return "";
}

public string
hole_desc(void)
{
    if (level > 5)
    {
	return "High above your head, a square hole leads into the "+
	    "east wall. Very little can be made out about it from here. "+
	    "You estimate that it is about "+
	    LANG_WNUM(level + random((200 - TP->query_stat(SS_WIS)) / 5)) +
	    " centimeters above your head.\n";
    }
    else if (level < -5 && level > -10)
    {
	return "At the base of the east wall is the top of a square "+
	    "hole made from smoothed blocks of grey masonry. The hole "+
	    "seems to extend for a way into the darkness, but you "+
	    "cannot get a very good view from here.\n";
    }
    else if (level >= -5 && level <= 5)
    {
	return "In the center of the east wall is a square hole made "+
	    "from large blocks of masonry. The hole extends for a ways "+
	    "into the darkness, and in the distance you think you can "+
	    "see a small flickering light at the other end.\n";
    }
    else return "You can see no hole here.\n";
}

public int
query_level(void)
{
    return level;
}

public int
go_west(void)
{
    write("As you walk west, the hall floor beneath "+
	"lurches sickeningly.\n");
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
    weight_there = THALLW->all_weight();

    if (!flag)
	THALLW->update_weight(1);

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

    if (level >= -5 && level <= 5)
    {
	tell_room(TO, "The hallway "+ (oldlevel < 0 ? "lowers" : "raises") +
	    " " + str + "until it is nearly level with the square hole "+
	    "in the east wall.\n");
    }
    else if (oldlevel < 0 && level > 0)
    {
	tell_room(TO, "This end of the hallway drops downwards, "+
	    "and the west end of the hallway rises.\n");
    }
    else if (oldlevel > 0 && level < 0)
    {
	tell_room(TO, "The hallway rises suddenly, and the west end "+
	    "of the hallway seems to drop down.\n");
    }

    tell_room(HOLE, "A deep rumble can be heard from the west.\n");
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
    if (to == find_object(THALLW))
	return;

    if (!weight_alarm)
	weight_alarm = set_alarm(1.0, 0.0, update_weight);
}

public int
enter(string str)
{
    NF(CAP(query_verb())+" what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}), "[through] [into] [in] [the] 'hole'"))
	return 0;

    /* The taller you are, the higher you can reach */
    if (level > (TP->query_prop(CONT_I_HEIGHT) / 10))
    {
	write("The hole is too high up for you to reach, "+
	    "let alone enter.\n");
	return 1;
    }

    if (level < -5 && level > -10)
    {
	write("The hole is too blocked by the floor. You cannot "+
	    "squeeze through it.\n");
	return 1;
    }

    if (level <= -10)
    {
	write("You can see no hole here.\n");
	return 1;
    }

    object hole = find_object(HOLE);
    if (hole && sizeof(filter(all_inventory(hole), query_interactive)))
    {
	write("The seems to be someone in the hole already, "+
	    "there is not enough room for two.\n");
	say(QCTNAME(TP) +" tries to enter the hole, but there is "+
	    "not enough room.\n");

	tell_room(hole, "Someone seems to be trying to enter the hole "+
	    "from the west, but there is not enough room for both of you.\n");

	return 1;
    }

    if (level > 5)
    {
	write("You are tall enough to reach up and pull yourself "+
	    "into the hole.\n");
	say(QCTNAME(TP) +" manages to reach up and pull "+
	    HIM(TP) +"self into the hole.\n");
    }
    else write("You climb into the square hole.\n");
    TP->move_living("climbing through the hole", HOLE, 1);
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(enter, "enter");
    add_action(enter, "climb");
}
