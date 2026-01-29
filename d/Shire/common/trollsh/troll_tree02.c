/* File: /d/Shire/common/trollsh/rivend5.c */
#include "defs.h"
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

inherit STAND_EROAD;

#define GER    TROLLSH_DIR + "rivend5"
#define NEED_CLIMB_SKILL    15

void up_tree();
void down_tree();

create_er_shaws()
{

    set_short("Up in a tree");
    set_long(
        "You are in the midst of an old tree. Many thick " +
        "branches spread out in all directions. They obstruct " +
        "most of your view from here but still enable you to " +
        "look down below. ");

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

    set_noshow_obvious(1);
    reset_shire_room();
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
        write("Do you want to climb up or down?\n");
        return 1;
    }

    if(str=="up")
    {
        if(player_climb_skill>NEED_CLIMB_SKILL)
        {
            up_tree();
        }
        else
        {
            write("You strugggle and try to climb the tree, but " +
                "are unable to do so.\n");
            say(QCTNAME(TP) + " struggles to climb the tree but " +
                "is unable to.\n");
        }
    }
    else if(str=="down")
       {
           down_tree();
       }

    else write("Climb what?\n");
    return 1;
}


void
up_tree()
{
    write("You reach up and grab an overhanging branch and pull " +
        "yourself up. With a great deal of effort, you climb " +
        "several branches and go farther up into the tree.\n");
    say(QCTNAME(TP) + " reaches up and grabs an overhanging branch. " +
        "With a great deal of effort, " + CAP(HE_SHE(TP)) + " climbs " +
        "several branches and goes farther up into the tree.\n");
    TP->move_living("M",TROLLSH_DIR + "troll_tree03");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from below.\n",TP);
}

void
down_tree()
{
    write("You carefully climb down several branches.\n");
    say(QCTNAME(TP) + " carefully climbs down several branches.\n");
    TP->move_living("M",TROLLSH_DIR + "troll_tree01");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from above.\n",TP);
}


void
reset_shire_room()
{
/*
    object harp;

        if (!present("_shire_harp_",TO))
    {
        harp = clone_object("/d/Shire/scav_hunt/harp");
        harp->add_prop(OBJ_I_HIDE, 10 + random(10));
        harp->move(TO);
    }
*/
}
