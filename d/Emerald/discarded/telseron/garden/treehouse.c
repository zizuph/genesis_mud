/*
 * The treehouse in the tree in the garden
 * Coded by Finwe, September 1996
 * Modified by Jerusha Feb98..added meditation
 */
 
 
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Emerald/defs.h"
#include "garden.h"
#include <ss_types.h>
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
inherit "/lib/guild_support";
 
int climbtree, chance, fallchance;
string str;
 
void reset_room();
 
create_room() 
{
    reset_room();
    set_short("A treehouse");
    set_long("   You stand in the upper branches of the great tree. " +
        "This treehouse was built for the children of the King and " +
        "and Queen. Occasionally, they still come here to get " +
        "away from palace life and to relive their childhood memories. " +
        "Now, it stands empty except for the occasional visitor who " +
        "comes up here to meditate. The great tree grows up through " +
        "the center " +
        "of the tree house. You notice that some branches have been " +
        "removed to make room here. The leaves of the branches create "+
        "a beautiful ceiling. In a corner of the treehouse is a hole " +
        "with a ladder leading down.\n\n");
 
    add_item(({"tree", "great tree", "large tree"}),
        "It grows up through the center of the treehouse. It " +
        "grows up and its branches grow out here.\n");
    add_item(({"branch", "branches"}),
        "The branches of the tree are quite large. They stretch up " +
        "and out in all directions, blocking your view up here.\n");
    add_item("trunk",
        "The trunk is silver gray. The width of the trunk hasn't " +
        "diminshed up here. It is still immense.\n");
    add_item(({"leaf", "leaves"}),
        "The leaves are large, oval shaped. They are gold and silver " +
        "colored, and hang from the branches like stars. When the " +
        "breeze blows through them, it sounds like a gentle rain in " +
        "the springtime.\n");
    add_item(({"rail", "railing"}),
        "The rail is made of silver. It is beautifully handcrafted " +
        "by expert elven silversmiths. The balustrades, or vertical " +
        "supports of the rail, are fashioned into the images of many " +
        "trees, whose branches hold up the handrail.\n");
    add_item(({"sky", "canopy"}),
        "The branches block most of the sky, but there is a small " +
        "opening in the canopy.\n");
    add_item("opening",
        "The opening is small enough for a small elf to crawl thru.\n");
    add_item(({"planks", "ground", "floor"}),
        "The ground of the balcony is made from tight fitting planks " +
        "of wood. You notice that there aren't any cracks or crevices " +
        "in the floor. In the center here, is the hole from which you " +
        "climbed through to reach the balcony.\n");
    add_item("hole",
        "This large hole has been cut into the floor. There is a " +
        "ladder with rails on both sides of it which goes back " +
        "down to the garden.\n");
    add_item("ceiling",
        "The ceiling shimmers with the light of the leaves. The " +
        "leaves hang from the branches above protecting the " +
        "treehouse and creating a wave of beautiful sounds as they " +
        "rustle in the breeze.\n");

add_exit("/d/Emerald/finwe/workroom.c", "up", "@@block_me",0,1);
 
    create_guild_support();
}      
 
init()
{
    add_action("climb_tree", "climb");
    ::init();
    init_guild_support();
}

int
block_me()
{
 
    write("You hit your nose on a branch.\n");
    return 1;
}

int
climb_tree(string str)
{
    int climbtree;
    climbtree  = (TP->query_skill(SS_CLIMB));
    fallchance = 75 - (climbtree*5);
    chance     = random(100);
    if ( (member_array(str, ({"down", "tree", "down tree"})))==-1)
    {
	notify_fail("Climb what?\n");
	return 0;
    }
    if ((str == "tree") || (str == "down tree") || (str == "down"))
    {
        if (chance < fallchance) 
        {
            write("When you look down, you become scared. " +
                "You let go of the rail and fall from the tree.\n");
            TP->reduce_hit_point(50);
            TP->move_living("M", GARDEN_DIR + "tree", 1);
            return 1;
        }
        else
        {
            write("You manage to descend to the garden.\n");
            TP->move_living("M", GARDEN_DIR + "tree", 1);
            return 1;
        }
        return 1;
    }
    
}
    
 
void
reset_room()
{
}
