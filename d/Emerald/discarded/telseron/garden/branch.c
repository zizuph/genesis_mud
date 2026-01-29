/*
 * The large branch of the tree in the Garden of Telseron
 * Coded by Finwe, September 1996
 */
 
 
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Emerald/defs.h"
#include "garden.h"
#include <ss_types.h>
 
inherit "/std/room";
inherit "/d/Emerald/lib/room_tell";
#include "garden.h"
 
int climbtree, chance, fallchance;
string str;
 
void reset_room();
 
create_room() 
{
    reset_room();
    set_short("A large branch in the tree");
    set_long("   You deftly stand on a large branch in the " +
        "middle of the tree. This branch is quite large and looks " +
        "like it could hold quite a bit of weight. You notice two " +
        "large rings worn into the branch. They appear to be the " +
        "only remains of a swing that once hung here. Leaves " +
        "flutter in the wind around you, obscuring your view from " +
        "up here. You see a treehouse above you in another part " +
        "of the tree\n\n");
 
    add_item("trunk",
        "The trunk is silver gray. As you touch it, you notice the " +
        "bark to be soft. The width of the trunk is immense, a sign " +
        "of great age and wisdom of the tree.\n");
    add_item(({"leaf", "leaves", "up"}),
        "The leaves are large, oval shaped. The are gold and silver " +
        "colored, and hang from the branches like stars. When the " +
        "breeze blows through them, it sounds like a gentle rain in " +
        "the springtime. They obscure your vision.\n");
    add_item("branch",
        "The branch you stand on stretches out into the garden. " +
        "It seems to be the largest branch on the tree.\n");
    add_item(({"tree", "great tree", "large tree"}),
        "It grows in the center of the Royal Garden and has " +
        "seen many lifetimes. The top reaches for the deep blue sky. " +
        "The trunk and branches are both immense. Looking up, you " +
        "see nothing but a shifting kaleidoscope of leaves.\n");
    add_item(({"branches", "down"}),
        "Many branches spread out in all directions. They grow " +
        "up and out as they fill the garden.\n");
    add_item("treehouse",
        "The treehouse sits in the center of the tree. You can " +
        "see an opening in the floor. It looks large and " +
        "rather inviting.\n");
    add_item("rings",
        "The rings are large and seem to be worn away, perhaps " +
        "by rope or something.\n");
}
                 
init()
{
    add_action("climb_tree", "climb");
    ::init();
}
 
 
climb_tree(str)
{
    int climbtree;
    climbtree  = (TP->query_skill(SS_CLIMB));
    fallchance = 75 - (climbtree*5);
    chance     = random(100);
 
    if ((str == "down large branch") || (str == "down branch") 
        || (str == "down branch") || (str == "down"))
    {
        if (chance < fallchance) 
        {
            write("When you look down, you become scared. " +
                "You let go and fall from the branch.\n");
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
    return "What do you want to climb?";
}
    
 
void
reset_room()
{
}
