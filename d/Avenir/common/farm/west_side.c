#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/room";
int ring_found = 0;

void
create_room()
{
    set_short("The west side of the manor");
    set_long("You stand at the west side of the building. It looks " +
        "like the other sides. Around the house leads the gravel " +
        "path and the lawn spreads out to the fence and hedge " +
        "surrounding it.\n");
    add_item(({"house","manor","building"}),"You take a closer look at the house. " +
        "This clearly is the main building of this farm. Once it must " +
        "have been a nice and proud building, but now years of " +
        "non-existant maintenance has taken its toll. The white paint " +
        "has started to flake off and everything looks old and dirty.\n");
        add_item(({"paint","colour"}),"You scrape off some of the old " +
        "dry paint from the house wall. It has been white once long " +
        "ago but is now gray and dry and you see flakes constantly " +
        "drop to the ground from the worn wall.\n");
    add_item("flakes","The flakes are just flakes of old dry paint.\n");
    add_item(({"window","windows"}),"By looking at the windows of the " +
        "manor you notice they are all in quite a bad shape. Old and " +
        "dirty unless they are broken as some of them seems to be from " +
        "this position.\n");
    add_item(({"lawn","grasslawn","grass"}),"You step out on the grass " +
        "lawn. Its uncut and weed has taken over almost completely. " +
        "You guess this hasn't always been like this and sadly wish you " +
        "could have seen the lawn in its glorious days. A couple of " +
        "apple trees wouldnt have hurt, but now there is only one " +
        "single tree growing on the lawn and its not an apple tree. " +
        "Around the " +
        "lawn is a wooden fence that cuts off the grass lawn from the " +
        "surrounding hedge.\n");
    add_item(({"fence","wooden fence"}),"You walk forward across the " +
        "lawn to the fence and take a closer look. Its about half the " +
        "height of a human and it stretches between the lawn and the " +
        "thick hedge.\n");
    add_item("hedge","You narrow your eyes and focus the hedge. Its " +
        "high and well grown and its impossible to see anything " +
        "through or behind it.\n");
    add_item(({"path","gravel path"}),"@@gravel_path@@");
    add_item(({"tree","trees"}),"You walk up to the only tree on " +
        "this side of the house. A tall tree with branches so " +
        "high making it impossible to climb.\n");
    add_item("tower", "You look up at the tower. It is quite amazing " +
        "and you think the view from up there must be quite stunning.\n");
    set_terrain(TERRAIN_OPENSPACE);
    set_terrain(TERRAIN_OUTSIDE);
    add_exit("south_side","southeast");
    add_exit("north_side","northeast");

    reset_room();
}

void
reset_room()
{
    ring_found = 0;
}

void
init()
{

    ::init();
        add_action("shake_tree","shake");
        add_action("shake_tree","kick");
        add_action("climb_tree","climb");
        add_action("enter_window","enter");
    add_action("cut_tree","cut");

}

string
gravel_path()
{

    tell_room((THIS_DIR + "library"),"You hear someone walking in " +
        "the gravel outside the window.\n");
    tell_room((THIS_DIR + "south_side"),"You hear someone walking " +
        "in the gravel on the west side of the house.\n");
    tell_room((THIS_DIR + "north_side"),"You hear someone walking " +
        "in the gravel on the west side of the house.\n");
    return "You take a step on the gravel path. There is a rasping " +
        "sound from the gravel below your feet, so you decide to " +
        "go back to the grass.\n";
}

 
int
cut_tree(string str)
{
    object weapon;
 
    if (str == "tree")
    {
        weapon = (TP->query_weapon(W_RIGHT));
        if (!(weapon))
            weapon = (TP->query_weapon(W_LEFT));  
 
        if (weapon)
        {
            write("You start to cut down the tree with your " +
            weapon->short() + " but stop after a short " +
                "while. Its a nice tree after all. Maybe it is " +
                "another way to get what you are looking for.\n");
                return 1;
        }
        write("Cutting down trees would not please the " +
            "owner of this place. Maybe there are other means " +
            "to get what you are looking for.\n");
        return 1;
    }
    return 0;
}
 
int
shake_tree(string str)
{
    object ring;

    if (strlen(str) && (str == "tree"))
    {
        if (ring_found == 0)
        {
                write("You take a step closer to the tree and grab "+
                "it with both hands and " +query_verb()+ " it violently. " +
                      "After a short while something falls down " +
                      "from the treetop.\n");
                say(QCTNAME(TP) + " walks up to a tree and "
                    +query_verb()+ "s it violently.\n");
                ring_found = 1;
                ring = clone_object(THIS_DIR + "obj/ring");
                ring->move(TO);
                return 1;
        }
        write("You take a step closer to the tree and grab "+
                "it with both hands and " +str+ " it violently. " +
              "After a short while you give up. Nothing " +
              "happens!\n");
        say(QCTNAME(TP) + " walks up to a tree and "
            +query_verb()+ "s it violently.\n");
        return 1;
    }
    return 0;
}
 
int
kick_tree(string str)
{

    if (strlen(str) && (str == "tree"))
    {
        write("You take a step closer to the apple tree " +
            "and kick it hard! This doesnt make you any " +
            "happier, but your foot hurts a lot.\n");
        say(QCTNAME(TP) + " Walks up to a tree and kicks " +
            "it hard.\n");
        return 1;
    }
    return 0;
}
 
int
climb_tree(string str)
{
    if (strlen(str) && (str == "tree"))
    {
        say(({METNAME + " tries to climb the tree but fails.\n",
            TART_NONMETNAME + " tries to climb the tree but fails.\n",
            ""}), TP);
        write ("You try to climb the tree but as there are no " +
            "branches to get a grip on, it does not work. " +
            "When you give up the tree shakes a bit. It does not " +
            "seem to be a robust tree at all.\n");
        return 1;
    }
 
 

    if (strlen(str) && ((str == "walls") || (str == "house")))
    {
        say(({METNAME + " tries to climb the house walls but fails.\n",
            TART_NONMETNAME + " tries to climb the house walls but fails.\n",
            ""}), TP);
        write ("You try to climb the walls but as there is nothing " +
           "to get a good grip on, and it does not work.\n");
        return 1;
    }
    return 0;
 
}
 
int
enter_window(string str)
{
 
    if (strlen(str) && ((str == "window") || (str == "windows")))
    {
 
        write("There is no way you can enter a window from " +
            "down here.\n");
            return 1;
    }
    return 0;
 
 
}
 
int
query_ring()
{
    return ring_found;
}
