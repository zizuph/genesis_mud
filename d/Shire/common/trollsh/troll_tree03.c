/* File: /d/Shire/common/trollsh/rivend5.c */
#include "defs.h"
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

inherit STAND_EROAD;

#define GER    TROLLSH_DIR + "rivend5"
#define NEED_CLIMB_SKILL    15
#define RNPC_DIR "/d/Shire/rivendell/npc/"
#define MAX_ELVES 3

static object *elf_guard = allocate(MAX_ELVES);


object elladan;
//object elf_guard;

void down_tree();

create_er_shaws()
{

    set_short("The top of a tree");
    set_long(
        "You are in the top of a tall tree. The tree's crown " +
        "rises farther into the sky but looks inaccessable from " +
        "here. Unlike the rest of the tree, the view from up here " +
        "is pretty good, enabling anyone to see below quite clearly. \n");

    add_item(({"eastroad", "road" }),
        "The road winds its way through the forest below. " +
        "@@road_desc@@ \n");
    add_item("tree", 
        "The tree is large and reaches for the sky. Thick " +
        "branches reach out from its trunk, providing a " +
        "stable place to stand on.\n");
    add_item("trees", 
        "Some trees are tall and reach for the sky while " +
        "others look like they have been shattered or " +
        "broken by something of immense strength.\n");
    add_item(({"branches", "branches"}),
        "The branches are thick with age and stretch out " +
        "in all directions. They provide shelter to those " +
        "hidden in them.\n");
    add_item("forest",
        "The forest looks old and full of ancient trees. It " +
        "is large and seems to spread out in all directions.\n");
    add_item(({"crown", "tree's crown", "tree top", "top", "top of the tree"}),
        "The crown, or top of the tree, reaches up into the sky. " +
        "It is approximately twice the height of a man and " +
        "reaches a point at the top.\n");
    set_noshow_obvious(1);
    reset_er_shaws();
}

void reset_er_shaws()
{
    int index;

    setuid();
    seteuid(getuid());

    if(!objectp(elladan))
    {
        elladan = clone_object(RNPC_DIR + "elladan");
        elladan->move(TO);
    }
    /* Loop over all elements in the array. */
    for(index = 0; index < MAX_ELVES; index++)
    {
        if (!objectp(elf_guard[index]))
        {
            elf_guard[index] = clone_object(RNPC_DIR + "guard");
            elf_guard[index]->move(TO);
 
        }
    }
 

}



public void
init()
{
    ::init();
    add_action("do_climb", "climb");
}

string
road_desc()
{
    object other_room;
    mixed opeople;
 
    if (!LOAD_ERR(GER))
        other_room = find_object(GER);
    else
        return "Some sort of magic is plaguing the road. Contact " +
            "a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        return "It looks quiet and deserted.";
    else
        return "From up here you see "+COMPOSITE_LIVE(opeople)+
            " on the road below.";
}


int do_climb(string str)
{
    int player_climb_skill;
    if(!str)
    {
        write("Climb what? \n");
        return 1;
    }

    player_climb_skill = TP->query_skill(SS_CLIMB);

    if(str =="tree" || str == "branch")
    {
        write("Do you want to climb up or down?");
        return 1;
    }

    if(str=="down")
       {
           down_tree();
       }

    else write("Climb what?\n");
    return 1;
}

void
down_tree()
{
    write("You carefully climb down several branches.\n");
    say(QCTNAME(TP) + " carefully climbs down several branches.\n");
    TP->move_living("M",TROLLSH_DIR + "troll_tree02");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from below.\n",TP);
}
