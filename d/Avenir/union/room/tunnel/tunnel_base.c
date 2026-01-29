/*
 * Inheritable standard tunnel room that leads from
 * the Union hall to the park island.
 *
 *    Cirion, December 96
 *
 * Revisions:
 * 	Lucius, Aug 2017: Cleanups.
 */
#pragma strict_types

inherit "/std/room";
inherit "/d/Avenir/inherit/room_tell";

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "defs.h"

public static string north, south;
public static mapping opp = ([
       "up" : "down",  "down" : "up",
    "north" : "south", "east" : "west",
    "south" : "north", "west" : "west",
         "northwest" : "southeast",
         "northeast" : "southwest",
         "southeast" : "northwest",
         "southwest" : "northeast",
]);

public void
tunnel_room(void)
{
}

public nomask void
create_room(void)
{
    set_short("gloomy tunnel");

    add_item("ceiling", "The ceiling of the tunnel is smooth, similiar "+
	"to the ground, but not worn down.\n");
    add_item(({"ground","floor"}), "It is smooth and worn.\n");

    add_cmd_item(({"breeze","wind"}), "feel",
	"The currents of air are warm.\n");

    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);

    set_tell_time(100 + random(200));
    add_tell(FLICKER);
    add_tell(FLUTTER);

    tunnel_room();
}

public string
descending(void)
{
    string desc, *strs = query_exit_cmds();

    if (sizeof(strs) < 2)
	return "";

    desc = one_of_list(({ "tunnel", "passageway" }));
    return one_of_list(({
	    " The " + desc + " descends steeply "+ strs[1] +
		", and rises up to the " + strs[0],
	    " The " + desc + " rises to the "+ strs[0] +" and descends "+
		"sharply to the " + strs[1],
    })) + ".";
}

public string
ascending(void)
{
    string desc, *strs = query_exit_cmds();

    if (sizeof(strs) < 2)
	return "";

    desc = one_of_list(({ "tunnel", "passageway" }));
    return one_of_list(({
	    " The " + desc + " ascends steeply "+ strs[0] +
		", and descends to the " + strs[1],
	    " The " + desc + " ascends to the " + strs[1] + " and drops "+
		"sharply to the " + strs[0],
    })) + ".";
}

public varargs string
northern(string where, mixed efunc)
{
    object there;

    if ((there = find_object(where)) || (there = find_object(TUNNEL + where)))
	north = opp[there->get_south()];

    if (!north)
	north = one_of_list(({"north","northwest","northeast"}));

    add_exit(where, north, efunc);
    return north;
}

public varargs string
southern(string where, mixed efunc)
{
    object there;

    if ((there = find_object(where)) || (there = find_object(TUNNEL + where)))
	south = opp[there->get_north()];

    if (!south)
	south = one_of_list(({"south","southwest","southeast"}));

    add_exit(where, south, efunc);
    return south;
}

public string
get_north(void)		{ return north; }

public string
get_south(void)		{ return south; }

public object
get_torch(void)
{
    object *things = filter(deep_inventory(),
	&->query_prop(OBJ_I_HAS_FIRE));

    if (!sizeof(things))
	return 0;

    return one_of_list(things);
}

public string
flicker(void)
{
    object who, torch = get_torch();

    if (!torch || !living(who = ENV(torch)))
	return 0;

    who->catch_tell("Your "+ torch->short(who) +
	" flickers in the breeze.\n");
    tell_room(ENV(who), QCTPNAME(who) +" "+ QSHORT(torch) +
	" flickers in the breeze.\n", ({ who }));

    return "";
}

/* Start up the room tells now */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    start_room_tells();
}

public string
hflutter(void)
{
    object *new = ({ });

    foreach(object live: FILTER_LIVE(all_inventory()))
    {
	if (sizeof(filter(live->query_cmdsoul_list(),
		    &->exist_command("hflutter"))))
	{
	    new += ({ live });
	}
    }

    if (sizeof(new))
	one_of_list(new)->command("$hflutter");

    return "";
}

public int
emitting_light(object what)
{
    if (function_exists("create_container", what))
	return 0;

    return (what->query_prop(OBJ_I_LIGHT) > 0);
}

public object
find_light(void)
{
    object *stuff = filter(deep_inventory(), emitting_light);

    if (!sizeof(stuff))
	return 0;

    return one_of_list(stuff);
}

public string
light_desc(void)
{
    object light = find_light();
    string whose, fire, brightness, sdesc;

    if (!light)
	return "";

    if (ENV(light) == TP)
	whose = "your";
    else if (!living(ENV(light)))
	whose = "the";
    else
	whose = ENV(light)->query_the_possessive_name(TP);

    if (light->query_prop(OBJ_I_HAS_FIRE))
	fire = "flickering flames";
    else
	fire = one_of_list(({"luminescence","lambent glow"}));

    switch(light->query_prop(OBJ_I_LIGHT))
    {
    case 0:
	brightness = "nonexistent ";
	break;
    case 1:
	brightness = "";
	break;
    case 2:
	brightness = "bright ";
	break;
    default:
	brightness = "dazzling ";
	break;
    }

    sdesc = light->short(TP);
    if (!strlen(sdesc))
	sdesc = "light";

    return "The " + brightness + fire + " of " + whose + " " +
	light->short(TP) + " " + one_of_list(({ "illuminates the walls",
	"casts about long shadows that seem to make the walls feel alive",
	"illuminates the area"})) + ". ";
}
