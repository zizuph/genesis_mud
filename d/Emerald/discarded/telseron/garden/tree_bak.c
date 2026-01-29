/*
 * The Great Tree in the center of the Garden of Telseron
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
    set_short("The center of the garden");
    set_long("   You stand in the center of the garden. A wide lawn " +
        "is here rather than flowers, it contrasts nicely with the " +
        "rest of the garden. A feeling of peace, surpassing all " +
        "understanding is here. It descends on you, resting your mind " +
        "and body. Standing here, you feel refreshed and protected. A " +
        "great tree grows here. A power seems to emanate from it. Its " +
        "branches spread across the garden, as if protecting all who " +
        "come to enjoy this paradise. The air is cool and fresh as it " +
        "blows in from the garden.\n\n");
 
    add_item(({"tree", "great tree", "large tree"}),
        "It grows in the center of the Royal Garden. The tree is " +
        "magnificent. Judging from its size, this tree has seen " +
        "many lifetimes. It is the greatest tree you'll ever see. The" +
        "top reaches for the deep blue sky. The trunk and branches are " +
        "both immense. Looking up, you see nothing but a shifting " +
        "sea of leaves.\n");
    add_item(({"branch", "branches"}),
        "The branches of the tree are quite large. They stretch in " +
        "all directions.\n");
    add_item("trunk",
        "The trunk is silver gray. As you touch it, you notice the " +
        "bark to be soft. The width of the trunk is immense, a sign " +
        "of great age and wisdom of the tree.\n");
    add_item(({"leaf", "leaves"}),
        "The leaves are large, oval shaped. The are gold and silver " +
        "colored, and hang from the branches like stars. When the " +
        "breeze blows through them, it sounds like a gentle rain in " +
        "the springtime.\n");
    add_item(({"lawn", "grass"}),
        "The lawn is a verdant sea of lush green. It is clean and " +
        "soft, and smells fresh.\n");
    add_item("sky", 
        "The sky is a deep azure blue.\n");
 
 
    add_exit( GARDEN_DIR + "path04", "north");
    add_exit( GARDEN_DIR + "path11", "south");
    add_exit( GARDEN_DIR + "path08", "east");
    add_exit( GARDEN_DIR + "path07", "west");
    add_exit( GARDEN_DIR + "path05", "northeast");
    add_exit( GARDEN_DIR + "path03", "northwest");
    add_exit( GARDEN_DIR + "path12", "southeast");
    add_exit( GARDEN_DIR + "path10", "southwest");
  
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
 
    if ((str == "tree") || (str == "up tree") || (str == "up"))
    {
        if (chance < fallchance) 
        {
            write("You slip and fall from the tree.\n");
            TP->reduce_hit_point(50);
            TP->move_living("M", GARDEN_DIR + "tree", 1);
            return 1;
        }
        else
        {
            write("You manage to climb higher into the tree.\n");
            TP->move_living("M", GARDEN_DIR + "treehouse", 1);
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
void tree_msg ()
{ 
    write ("You climb the tree.");
    return; 
}
