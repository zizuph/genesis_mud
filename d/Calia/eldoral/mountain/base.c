
/*
 * Fixed typo - Jaacar, May 2016
 */

#pragma strict_types

#include "defs.h"
#include <composite.h>

inherit "/std/room";
inherit HERBMASTER;

string extra;
int horn_found,
    kroug_killed;
object kroug;

public void
reset_room()
{
    ::reset_room();
    horn_found = 0;
    kroug_killed = 0;
}

public void
create_trail()
{
    
    if (!find_object(MOUNTAIN_BRAIN))
    {
        setuid();
        seteuid(getuid());
        (MOUNTAIN_BRAIN)->randomize_ruins();
    }

    set_short("a narrow trail through a mountain forest");
    set_long("You are on a narrow trail, winding through a tall, " +
        "thick forest atop the mountain. The trail itself could " +
        "be an animal trail, it's little more than a clear path " +
        "of deep grass that winds between the trees. The trees, mainly " +
        "firs and pines, stretch high into the sky, " +
        "branches interweaving above you turning this trail into " +
        "something resembling a tunnel of foliage. Occasionally, " +
        "the peace and solitude is interrupted by a songbird " +
        "calling from the trees, or a squirrel darting across the " +
        "trail, vanishing into the thick underbrush which blankets " +
        "the forest floor. " +
        (stringp(extra) ? extra : "") + "\n\n");

    add_item(({"underbrush","bushes","brush","shrubs", "ferns", "ground"}),
        "The forest ground is blanketed in a deep layer of thick, " +
        "green bushes, shrubs, brush, ferns, and countless " +
        "varieties of other forms of underbrush. Who knows what " +
        "could be concealed beneath?\n");
    add_item(({"trail", "path"}),
        "The trail you are on seems little more than a woodland animal " +
        "trail of some sort, however a slightly closer inspection of " +
        "it reveals ancient flagstones, now almost entirely overgrown, " +
        "forming the basis of this trail.\n");
    add_item(({"forest", "trees", "tree", "evergreens"}),
        "You are in a forest of what look like evergreen trees of some " +
        "sort, possibly firs. The trees here are healthy and brilliant " +
        "green, and the sweet scent of sap pervades the environment.\n");
    add_item(({"branches", "needles"}),
        "The branches of the trees are lush and green with " +
        "thick, healthy needles.\n");
    add_item(({"mountain"}),
        "You can't see a whole lot of the mountain from here, as you are " +
        "in a narrow valley, and the trees around you completely block " +
        "your line of sight for anything farther than a stone's throw.\n");
    add_item(({"grass"}),
        "The grass grows thick and lush here, deep in the remote forests " +
        "of this isolated valley. Peeking up from beneath the grass " +
        "along the trail, you note a wandering line of almost entirely " +
        "overgrown flagstones.\n");
    add_item(({"stones", "flagstones"}),
        "Largely buried beneath soil and grass, the flagstones look as " +
        "they were once part of a well constructed road or street of " +
        "some kind, but that must have been several generations ago, as " +
        "there's little, if any, sign of their original purpose left.\n");
    add_item(({"sky", "clouds"}),
        "The sky overhead is partly overcast, which seems to darken " +
        "further north. Back to the south, however, you see patches of " +
        "cloudless sky.\n");

    if ((MOUNTAIN_BRAIN)->query_ruin() == file_name(TO))
    {
        add_prop(OBJ_S_SEARCH_FUN, "horn_search");
        add_prop(OBJ_I_SEARCH_TIME, 5);
    }
    setup_my_herbs();
    add_prop(ROOM_I_NO_CLEANUP, 1);
    reset_room();
}

public void
kroug_killed()
{
    kroug_killed = 1;
}

public string
kroug_block(object player)
{
    if (kroug_killed || !kroug || !present(kroug, TO))
        return "";

    if (kroug)
    {
        if (environment(kroug) && environment(kroug) != TO)
            return "";

        if (!CAN_SEE(kroug, player))
        {
            tell_object(player, "The kroug doesn't seem to be able " +
                "to see you, so you continue to search unchallenged.\n");
            return "";
        }

        if (kroug->query_prop(LIVE_I_STUNNED))
        {
            tell_object(player, "The kroug appears to be temporarily " +
                "unable to do anything to prevent your search, so you " +
                "continue with your search unimpeded.\n");
            return "";
        }
        else
            return "The kroug blocks your attempt to further search!\n";
    }
    return "";
}

public string
find_horn(object player, int ruin)
{
    object horn;
    string temp;

    if (horn_found)
        return "";

    else if (!kroug_killed && !kroug)
    {
        kroug = clone_object(NPC + "kroug");
//        kroug->arm_me();
        tell_room(TO, "Suddenly a dark figure crashes out of nowhere " +
            "and howls in insane fury!\n");
        kroug->move_living("M", TO);
        kroug->command("kill " + OB_NAME(player));
        return "If there is anything here, you'll have to wait " +
            "to find it!\n";
    }
    else if (strlen(temp = kroug_block(player)))
    {
        return temp;
    }
    else
    {
        horn = clone_object(OBJ + "horn");
        horn->move(player, 1);
        player->add_prop(LIVE_I_HORN_QUEST,
            player->query_prop(LIVE_I_HORN_QUEST) | HQ_FOUND_HORN);
        horn_found = 1;
        if (ruin)
            return "You search through the ruins, and find a hidden " +
                "compartment among them, and victoriously retrieve " +
                "a large ram's horn from within!\n";
        else
            return "You search through the underbrush, and find " +
                "a shallow depression beneath, within which you " +
                "discover a large ram's horn!\n";
    }
}

public string
horn_search(object player, string str)
{
    if (query_prop(ROOM_I_HAS_RUINS))
    {
        if (member_array(str, ({"ruins", "timbers", "flagstones",
            "walls", "stones", "flagstones", "foundation"})) >= 0)
            return find_horn(player, 1);
        else
            return "";
    }
    else
    {
        if (str == "underbrush")
            return find_horn(player, 0);
        else
            return "";
    }
    return "";
}

public string
ruins_item()
{
    string temp,
           *temparr;

    temp = "The ruins seem to be mainly comprised of ";
    temparr = ({});

    if (query_prop(ROOM_I_HAS_RUINS) & 1)
        temparr += ({"rotten timbers"});
    if (query_prop(ROOM_I_HAS_RUINS) & 2)
        temparr += ({"cracked flagstones"});
    if (query_prop(ROOM_I_HAS_RUINS) & 4)
        temparr += ({"a stone foundation of sorts"});

    if (!sizeof(temparr))
        return "There don't seem to be any real ruins here.\n";
    else
        return temp + COMPOSITE_WORDS(temparr) + ".\n";
}

public void
create_ruins(int ruin)
{
    if (!stringp(extra))
        extra = "";

    if (ruin == 3)
        ruin = 4;
    add_prop(ROOM_I_HAS_RUINS,
        (ruin | query_prop(ROOM_I_HAS_RUINS)));

    switch(ruin)
    {
        case 1:
            extra += "You notice a few stray timbers poking up through " +
                "the foliage, partially buried in the ground. " +
                "Looking more closely, you notice the timbers are " +
                "evenly spaced, as if they once formed the basis of " +
                "a wall. ";
            add_item(({"timbers", "wall"}),
                "There's not much left to see, just a few rotten timbers " +
                "leaning across each other at odd angles, roughly in " +
                "a straight line for a short distance.\n");
            break;
        case 2:
            extra += "Beneath the grass, you notice that there are " +
                "a large number of partially buried flagstones, " +
                "up through which some trees have grown, casting " +
                "what once might have been the floor of some long-" +
                "ruined building into a chaotic pattern " +
                "of cracked and scattered stones. ";
            add_item(({"cracked flagstones"}),
                "Much more widely spaced out than the narrow trail of " +
                "flagstones which brought you here, this just might " +
                "have been the floor of a building at some point in " +
                "time. Or perhaps a village square of some kind.\n");
            break;
        case 4:
            extra += "You see a large, rectangular-shaped formation " +
                "of roughly box-shaped stone blocks passing in and " +
                "out among the trees. It looks, perhaps, to be the " +
                "foundation of a building that had fallen " +
                "into ruin years past. ";
            add_item(({"foundation", "blocks", "stone blocks"}),
                "A generally rectangular formation of crumbling and " +
                "toppled stone blocks, this looks like it must have " +
                "been the foundation of a building a very long, long " +
                "time ago.\n");
            break;
        default:
            extra += "";
    }
    add_item(({"ruins"}), "@@ruins_item");
}

public void
create_close_shore()
{
    if (!stringp(extra))
        extra = "";

    extra += "In rare breaks in the trees to the north, you can make " +
        "out what appears to be a lake or river of some sort, " +
        "apparently draped in fog. The water must be quite still, " +
        "as you can hear little more than the occasional ripple " +
        "as water sloshes across the shore.";

    add_item(({"lake", "river", "water"}),
        "You can see very little except patches of rippled patches of " +
        "darkness from here, but the water looks very cold and clear.\n");
    add_item(({"shore", "shoreline"}),
        "It's impossible to see from here.\n");
    add_item(({"fog", "mist"}),
        "A heavy, grey fog blankets the waters beneath its shifting " +
        "surface. The clouds of mist billow and churn with every " +
        "sudden change in the light breeze which sweeps the area.\n");
}
public void
create_shore()
{
    set_short("on a rocky shoreline of a calm lake");
    set_long("You are on the shoreline of a calm, misty lake. " +
        "The shore itself is comprised almost entirely of fist-sized " +
        "stones and water-worn pebbles of various sizes and " +
        "colours, acting as a fence between the thick green foliage " +
        "of the forest, and the glassy waters of the lake. " +
        "The lake spreads out northwards, at least as far as you " +
        "can tell. Its smooth, black surface is concealed quite " +
        "heavily beneath a thick layer of fog which drifts gently " +
        "on a calm breeze across the cold waters of the lake. " +
        (stringp(extra) ? extra : "") + "\n\n");

    add_item(({"sky", "clouds"}),
        "The sky overhead is partly overcast, which seems to darken " +
        "further north. Back to the south, however, you see patches of " +
        "cloudless sky.\n");
    add_item(({"fog", "mist"}),
        "A heavy, grey fog blankets the waters beneath its shifting " +
        "surface. The clouds of mist billow and churn with every " +
        "sudden change in the light breeze which sweeps the area.\n");
    add_item(({"water", "waters", "lake"}),
        "The waters of the lake are cold and clear, yet its depth " +
        "gives the appearance of water as black as coal. Its surface " +
        "is very still, with waves little more than ripples crossing " +
        "its glossy surface.\n");
    add_item(({"ground", "shore", "shoreline"}),
        "The shore around you is comprised mainly of small, grey " +
        "pebbles, and appears to be restricted to this small section " +
        "of the lake's edge. Much further east or west, and it " +
        "appears to vanish completely.\n");
    add_item(({"pebbles", "rocks", "grey pebbles"}),
        "These small pebbles vary slightly in size, from the size of " +
        "thumbnail up to the size of a fist. They're all relatively " +
        "uniform grey in colour, seemingly originating from the same " +
        "chunk of rock before wind, rain, water and time had their " +
        "way and eroded them down to pebbles.\n");
    add_item(({"trees", "forest", "tree"}),
        "South of you, the trees of a large forest stretch upwards " +
        "through the tendrils of mist creeping off the waters, " +
        "towards the cloudy sky beyond.\n");
}

public int
do_swim(string str)
{
    if (!str || !strlen(str))
        return 0;

    if (parse_command(str, TP, "[in] / [into] [the] 'lake' / 'water'"))
    {
        write("The lake water is far too cold for swimming in.\n");
        return 1;
    }

    return 0;
}

public void
init_shore()
{
    add_action(do_swim, "swim");
    add_action(do_swim, "dive");
}
