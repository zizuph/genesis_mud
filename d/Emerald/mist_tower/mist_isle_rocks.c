#include "defs.h"

inherit MIST_ISLE_BASE;

static string *left_rock_exits = ({}), *right_rock_exits = ({});

public string cliff_desc();

public string *
query_exit_descs()
{
    string *dirs = ::query_exit_descs();

    if (sizeof(left_rock_exits))
    {
        dirs += ({ "left along the rocks" });
    }

    if (sizeof(right_rock_exits))
    {
        dirs += ({ "right along the rocks" });
    }

    return dirs;
}

public void
create_mist_rock_room()
{
}

public nomask void
create_mist_isle_room()
{
    remove_item("cliff");
    add_item(({ "cliff", "cliffs", "prominence", "rocky cliff", "rock cliff",
                "rocky prominence", "rock prominence", "face", "sheer face",
                "cliff face", "wall", "cliff wall" }), cliff_desc);

    add_item(({ "structure", "tower", "dark tower", "dark structure" }),
        "Only the top portion of the tower is visible from this angle, " +
        "and in the darkness, it is impossible to see any details of its " +
        "structure.\n");

    create_mist_rock_room();
}

public string
cliff_desc()
{
    if (CAN_SEE_IN_MIST(this_player()))
    {
        if (CAN_SEE_TOWER(this_player()))
	{
            return "The large, rock prominence looms approximately twenty " +
        	"meters above you.  The sheer face of the cliff is clearly " +
        	"unclimbable.  The top portion of a dark tower is visible " +
        	"beyond the edge of the cliff wall.\n";
	}

        return "The large, rock prominence looms approximately twenty " +
            "meters above you.  The sheer face of the cliff is clearly " +
            "unclimbable.\n";
    }

    return "In the dense fog, it is impossible to see more than a few " +
        "feet of the cliff wall.  The face of the cliff seems unclimbable.\n";
}

public string
extra_long()
{
    if (CAN_SEE_IN_MIST(this_player()))
    {
        if (CAN_SEE_TOWER(this_player()))
	{
	    return "  Through the gently drifting brume, you see the obscure " +
		"outline of a tall structure nearby, perched above you atop " +
                "a rocky prominence.  In the opposite direction, it is a " +
                "short distance to the rocky shore.\n";
	}

	return "  Through the gently drifting brume, you see the obscure " +
	    "outline of a tall structure in the distance, perched above " +
            "you atop a rocky prominence.  In the opposite direction, " +
            "it is a short distance to the rocky shore.\n";
    }

    return "  You have managed to find your way through the mist to the " +
        "sheer face of a rocky cliff.  In this impenetrable fog, only the " +
        "muted sound of crashing waves nearby gives any sense of direction.\n";
}

/*
 * Only certain pseudo-items are going to be visible to those who
 * cannot see through the mist.
 */
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
        case "cliff":
	case "cliffs":
	case "prominence":
	case "rocky cliff":
        case "rock cliff":
        case "rocky prominence":
        case "rock prominence":
        case "face":
        case "sheer face":
        case "cliff face":
	case "wall":
	case "cliff wall":
            return 1;
        default: 
	    return 0;
    }
}

public void
add_mist_exit(int dirs, string path, string cmd)
{
    ::add_mist_exit(dirs, path, cmd);

    if (dirs & LROCK_EXIT)
    {
        left_rock_exits += ({ path });
    }
    else if (dirs & RROCK_EXIT)
    {
        right_rock_exits += ({ path });
    }
}

public void
walk_left_rocks()
{
    int i = sizeof(left_rock_exits);
    if (i)
    {
        walk_mist(left_rock_exits[random(i)]);
    }
    else
    {
        write("You can't find a path in that direction.\n");
    }
}

public void
walk_right_rocks()
{
    int i = sizeof(right_rock_exits);
    if (i)
    {
        walk_mist(right_rock_exits[random(i)]);
    }
    else
    {
        write("You can't find a path in that direction.\n");
    }
}

public int
walk(string str)
{
    string *preps = ({ "right", "left" });
    if (!strlen(str) ||
        !parse_command(str, ({}), "[to] [the] %p [along] / [following] " +
        "[the] 'rock' / 'rocks' / 'cliff' / 'cliffs'", preps))
    {
        return ::walk(str);
    }

    if (preps[0] == "left")
    {
        walk_left_rocks();
    }
    else
    {
        walk_right_rocks();
    }

    return 1;
}
