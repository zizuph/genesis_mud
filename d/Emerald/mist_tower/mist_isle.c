/*
 * mist_path.c
 * 
 * This is the base room for the mist island.  Most of the functionality
 * deals with obscuring exits and restricting movement.  There are some
 * known holes, but it's rather difficult to address every inconsistency,
 * and this area simply isn't likely to get much traffic anyway.
 *
 * Known problems:
 * - Onlookers can see the exit direction when "proper" exits are used.
 *
 * Warning: what follows is some pretty ugly code ;)
 */

inherit "/d/Emerald/std/room";

#include "defs.h"

#include <stdproperties.h>
#include <filter_funs.h>


string *toward_shore_exits = ({}), *away_shore_exits = ({});

public string ground_desc();
public string sky_desc();
public string mist_desc();
public string shore_desc();

public void
create_mist_isle_room()
{
}

public string *
query_exit_descs()
{
    string *dirs = ({});

    if (sizeof(toward_shore_exits))
    {
        dirs += ({ "toward the shore" });
    }

    if (sizeof(away_shore_exits))
    {
        dirs += ({ "away from the shore" });
    }

    return dirs;
}

public string
query_exit_desc()
{
    string str, *dirs = query_exit_descs();

    if (sizeof(dirs) < 1)
    {
        str = "";
    }
    else if (sizeof(dirs) < 2)
    {
        str = dirs[0];
    }
    else
    {
        str = "either " + implode(dirs[..-2], ", ") + ", or " + 
            dirs[sizeof(dirs) - 1];
    }

    return str;
}

public int
all_block()
{
    if (CAN_SEE_IN_MIST(this_player()))
    {
        write("You cannot go farther in that direction.\n");
    }
    else
    {
        write("You find it impossible to judge exact directions in this " +
            "fog.  You realize that you will only be able to move " +
            query_exit_desc() + ".\n");
    }

    return 1;
}

public int
mist_block()
{
    if (CAN_SEE_IN_MIST(this_player()))
    {
        return 0;
    }

    write("You find it impossible to judge exact directions in this " +
          "fog.  You realize that you will only be able to move " +
          query_exit_desc() + ".\n");

    return 1;
}
    
public int
mist_nonobvious()
{
    return !CAN_SEE_IN_MIST(this_player());
}

nomask public void
create_emerald_room()
{
    set_short("In a dense fog");
    set_em_long("A heavy, dark mist hovers just above the rocky ground " +
        "here.@@extra_long@@");

    add_item(({ "down", "ground", "rocky ground", "rocks", "boulders",
        "boulder" }), ground_desc);
    add_item(({ "up", "sky" }), sky_desc);
    add_item(({ "fog", "mist", "brume", "dark fog", "dark mist", "dark brume",
                "drifting brume" }), mist_desc);
    add_item(({ "cliff", "cliffs", "prominence", "rocky cliff", "rock cliff",
                "rocky prominence", "rock prominence", "wall", "cliff wall" }),
                "");
    add_item(({ "shore", "rocky shore", "water", "ocean", "sea", "waves",
                "surf", "beach" }), shore_desc);
    add_item(({ "structure", "tower", "dark tower", "dark structure" }), "");

    add_prop("_room_i_free_vamp_dvis", 11);
    add_prop(ROOM_I_LIGHT, -10);

    // Would be nice if you could similarly mask the exit direction, not
    // just the entrance.
    add_prop(ROOM_S_EXIT_FROM_DESC, "from the dark mist.");

    create_mist_isle_room();

    map(({ "north", "northwest", "northeast", "south", "southwest",
	   "southeast", "east", "west" }) - query_exit_cmds(),
           &add_exit("", , all_block, 0, 1));

    add_prop(ROOM_I_NO_EXTRA_EXIT, 1);
}

public string
extra_long()
{
    if (CAN_SEE_IN_MIST(this_player()))
    {
        if (CAN_SEE_TOWER(this_player()))
	{
	    return "  Through the gently drifting brume, you can see the " +
                "dark shape of a rocky prominence in the distance.  In the " +
                "opposite direction, it is a short distance to the rocky " +
                "shore.\n";
	}

	return "  Through the gently drifting brume, you see the obscure " +
	    "outline of a tall structure in the distance, perched above " +
            "you atop a rocky prominence.  In the opposite direction, " +
            "it is a short distance to the rocky shore.\n";
    }

    return "  In this impenetrable fog, only the muted sound of crashing " +
        "waves nearby gives any sense of direction.\n";
}

public string
ground_desc()
{
    string str = "";

    if (!CAN_SEE_GROUND(this_player()))
    {
        str = "You bend down to get a clearer view of the ground through " +
            "the mist....\n";
    }

    return str + "The ground is covered with stones and boulders, smoothed " +
            "and rounded by the surf.  Some of the boulders are quite " +
            "large, and many are wet with ocean spray.  Walking around " +
            "could be quite treacherous.\n";
}
	
public string
sky_desc()
{
    return "";
}

public string
mist_desc()
{
    return "";
}

public string
shore_desc()
{
    return "";
}

public void
add_mist_exit(int dirs, string path, string cmd)
{
    add_exit(path, cmd, mist_block, 0, mist_nonobvious);

    if (dirs & ASHORE_EXIT)
    {
        away_shore_exits += ({ path });
    }
    else if (dirs & TSHORE_EXIT)
    {
        toward_shore_exits += ({ path });
    }
}

public int
can_see_in_mist(object ob)
{
    return CAN_SEE_IN_MIST(ob);
}

public void
walk_mist(string where)
{
    string msg;
    object *ppl, *see;

    ppl = FILTER_OTHER_LIVE(all_inventory());
    see = filter(ppl, can_see_in_mist);

    if (sizeof(see))
    {
        string dir = "";
        msg = " wanders off to the " + dir + ".\n";
        see->catch_msg(({
            this_player()->query_met_name() + msg,
            this_player()->query_nonmet_name() + msg,
            "" }));
    }

    msg = " wanders off into the fog.\n";
    (ppl - see)->catch_msg(({
        this_player()->query_met_name() + msg,
        this_player()->query_nonmet_name() + msg,
        "" }));

    this_player()->move_living("M", where, 1);

    ppl = FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
    see = filter(ppl, can_see_in_mist);

    if (sizeof(see))
    {
        string dir = "";
        msg = " emerges from the dark mist.\n";
        see->catch_msg(({
            this_player()->query_met_name() + msg,
            this_player()->query_nonmet_name() + msg,
            "" }));
    }

    msg = " emerges from the dark mist.\n";
    (ppl - see)->catch_msg(({
        this_player()->query_met_name() + msg,
        this_player()->query_nonmet_name() + msg,
        "" }));
}
 
public void
walk_tower()
{
    int i = sizeof(away_shore_exits);
    if (i)
    {
        walk_mist(away_shore_exits[random(i)]);
    }
    else
    {
        write("You can't find a path in that direction.\n");
    }
}

public void
walk_shore()
{
    int i = sizeof(toward_shore_exits);
    if (i)
    {
        walk_mist(toward_shore_exits[random(i)]);
    }
    else
    {
        write("You can't find a path in that direction.\n");
    }
}

public int
walk(string str)
{
    string *preps = ({ "toward", "to", "away", "from" });

    // This parse_command allows for some strange syntax, but it also
    // catches pretty much everything that makes sense.  If someone
    // wants to type "walk to from the sound surf", we'll let him ;)
    if (!strlen(str) || !parse_command(str, ({}),
        "%p [from] [the] [sound] [of] [the] 'shore' / 'water' / 'surf'", preps))
    {
        return 0;
    }

    if ((preps[0] == "toward") || (preps[0] == "to"))
    {
        walk_shore();
    }
    else
    {
        walk_tower();
    }

    return 1;
}

public void
init()
{
    ::init();

    add_action(walk, "move");
    add_action(walk, "walk");
    add_action(walk, "go");
}

public int
item_id(string item)
{
    if (!::item_id(item))
    {
        return 0;
    }

    if (CAN_SEE_IN_MIST(this_player()))
    {
        switch (item)
	{
            case "structure":
            case "tower":
            case "dark tower":
            case "dark structure":
                return CAN_SEE_TOWER(this_player());
            default:
                return 1;
	}
    }

    switch (item)
    {
        case "up":
        case "sky":
        case "fog":
	case "mist":
        case "brume":
        case "dark fog":
        case "dark mist":
	case "dark brume":
        case "drifting brume":
        case "shore":
        case "rocky shore":
        case "water":
        case "ocean":
        case "sea":
        case "waves":
        case "surf":
        case "beach":
            return 1;
        default: 
	    return 0;
    }
}

