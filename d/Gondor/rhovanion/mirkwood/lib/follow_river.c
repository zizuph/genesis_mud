/*
 *  /d/Gondor/rhovanion/mirkwood/lib/follow_river.c
 *
 *  Library to add commands for following the river up/downstream.
 *
 *  Created by Eowul, August 20th, 2015
 */

private string river_name = "river";
private mapping directions = ([ ]);
private mapping opposites = ([ "north": "south",
                               "northeast": "southwest",
                               "east": "west",
                               "southeast": "northwest",
                               "south": "north",
                               "southwest": "northeast",
                               "west" : "east",
                               "northwest": "southeast"
                               ]);

public void
set_river_name(string name)
{
    river_name = name;
}

public void
add_follow_direction(string place, string direction, string message)
{
    directions[direction] = ({ place, message });
}

private int
follow_cmd(string str)
{
    if(!str || !strlen(str))
    {
        notify_fail("Follow what?\n");
        return 0;
    }

    if ((str == "river") || (str == river_name))
    {
        notify_fail("Follow the " + str + " where?\n");
        return 0;
    }

    string direction;
    if (sscanf(str, river_name + " %s", direction) != 1 &&
        sscanf(str, "river %s", direction) != 1)
    {
        notify_fail("Follow the " + str + " where?\n");
        return 0;
    }

    if (member_array(direction, m_indices(directions)) == -1)
    {
        notify_fail("You can't follow the " + river_name + " " + direction + ".\n");
        return 0;
    }

    write("You follow the forest river " + directions[direction][1] + ".\n");
    tell_room(this_object(), ({
            this_player()->query_Met_name() + " follows the riverbank " + direction + ".\n",
            "The " + this_player()->query_nonmet_name() + " follows the riverbank " + direction + ".\n",
            ""
        }), ({ this_player() }), this_player());

    this_object()->set_dircmd(str);
    this_player()->move_living("M", directions[direction][0]);

    tell_room(environment(this_player()), ({
            this_player()->query_Met_name() + " arrives from the " 
                + opposites[direction] + ", following the " + river_name + ".\n",
            "A " + this_player()->query_nonmet_name() + " arrives from the " 
                + opposites[direction] + ", following the " + river_name + ".\n",
            ""
        }), ({ this_player() }), this_player());

    return 1;
}

void
init_follow_river()
{
    add_action(follow_cmd, "follow");
}