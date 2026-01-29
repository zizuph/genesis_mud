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
int door_found = 0;
int door_open = 0;
int do_open_door();
int gate_open = 0;
int do_open_gate();
int query_gate_open();

void
create_room()
{
    set_short("The east side of the manor");
    add_item(({"house","manor","building"}),"You take a closer look at the house. " +
        "This clearly is the main building of this farm. Once it must " +
        "have been a nice and proud building, but now years of " +
        "nonexcisting maintenance tas taken its toll. The white paint " +
        "has started to flake off and everything looks old and dirty.\n");
    set_long("You stand at the east side of the building. It looks like " +
        "the other sides. Around the house leads the gravel path and the " +
        "lawn spreads out to the fence and hedge surrounding it.\n");
    add_item(({"window","windows"}),"By looking at the windows of the " +
        "manor you notice they are all in quite a bad shape. Old and " +
        "dirty unless they are broken as some of them seems to be from " +
        "this position. On the second floor one window seems to " +
        "be missing. The hole for the window has been filled in, but " +
           "you can clearly see on the right side of the wall " +
        "where it used to have been.\n");
    add_item(({"lawn","grasslawn","grass"}),"You step out on the grass " +
        "lawn. It's uncut and weed has taken over almost completely. " +
        "You guess this hasn't always been like this and sadly wish you " +
        "could have seen the lawn in its glorious days. Around the lawn " +
        "is a wooden fence that cuts off the grass lawn from the " +
        "surrounding hedge. You also see some trees growing tall, " +
        "probably blocking the view from the windows on the second " +
        "floor. Across the lawn leads a small path towards the hedge. \n");
    add_item(({"fence","wooden fence"}),"You walk forward across the " +
        "lawn to the fence and take a closer look. It's about half the " +
        "height of a human and it stretches between the lawn and the " +
        "thick hedge.\n");
    add_item(({"paint","colour"}),"You scrape off some of the old " +
        "dry paint from the house wall. It has been white once long " +
        "ago but is now gray and dry and you see flakes constantly " +
        "drop to the ground from the worn wall.\n");
    add_item("flakes","The flakes are just flakes of old dry paint.\n");
    add_item("hedge","You narrow your eyes and focus the hedge. It's " +
        "high and well grown and it's impossible to see anything through " +
        "or behind it except at one place where you see a small opening " +
        "in the hedge. You can't see whats behind the opening.\n");
    add_item("opening","When you walk up to the fence and look closer " +
        "you see a small gate in it. Clearly there is a path through " +
        "the fence here, but you can't see where it leads.\n");
    add_item(({"tree","trees"}),"On the lawn are some high trees " +
        "growing. They look quite sad and tired from where you " +
        "stand.\n");
    add_item("gate","Hidden in the thick hedge is a small iron gate. "+
        "It has no lock so it is easy to open.\n");
    add_item("tower", "You look up at the tower. It is quite amazing " +
        "and you think the view from up there must be quite stunning.\n");
    add_item(({"path","gravel path"}),"@@gravel_path@@");
    set_terrain(TERRAIN_OPENSPACE);
    set_terrain(TERRAIN_OUTSIDE);
    add_exit("south_side","southwest");
    add_exit("north_side","northwest");
    reset_room();
}

void
reset_room()
{
    if (sizeof(FILTER_PLAYERS(all_inventory(TO))))
        return;
    door_found = 0;
    door_open = 0;
    remove_exit("down");
    gate_open = 0;
    remove_item("track");
    remove_exit("east");
}

void
init()
{

    ::init();
        add_action("search_grass","search");
        add_action("open_door","open");
        add_action("climb_wall","climb");
        add_action("enter_window","enter");
}

string
gravel_path()
{

    tell_room(("workroom"),"You hear someone walking in the gravel " +
        "outside the window.\n");
    tell_room(("south_side"),"You hear someone walking in the gravel " +
        "on the east side of the house.\n");
    tell_room(("north_side"),"You hear someone walking in the gravel " +
        "on the east side of the house.\n");
    return "You take a step on the gravel path. There is a rasping " +
        "sound from the gravel below your feet, and you decide to " +
        "go back to the grass.\n";
}

int
search_grass(string str)
{
    if (strlen(str) && (str == "grass") || (str == "lawn"))
    {
        write("You search the grass and feel something hard close " +
            "to the house wall. After digging with your bare hands " +
            "you see an overgrown wooden door in the grass.\n");
        add_item(({"door","wooden door"}),"You first barely see " +
            "the door " +
            "in the soil but now that you know about it, it's easy " +
            "to detect.\n");
        door_found = 1;
        return 1;
    }
    return 0;
}

int
open_door(string str)
{
    if (strlen(str) && (str == "door"))
    {
        if (door_found == 1)
        {
        write("You open the dirty door and look down into a dark passage. " +
            "From up here it looks like it may be some kind of a store " +
                "room for potatoes or other roots.\n");
        remove_exit("down");
        do_open_door();
        return 1;
        }
    }
    if (strlen(str) && (str == "gate"))
    {
 

    if (gate_open)
    {
        write("But the gate is already opened!\n");
        return 1;
    }
 
        write("You open the small gate and it easily swings open. " +
    "From here you can see a small track leading east " +
            "through the hedge.\n");
        say(QCTNAME(TP) + " swings up the gate in the hedge. On the " +
            "other side you see a small track leading east.\n");
        do_open_gate();
        return 1;
    }
    return 0;
}

int
query_door_open()
{
    return door_open;
}

int
do_open_door()
{
    door_open = 1;
    door_found = 1;
    add_exit("potato_cellar","down");
    return 1;
}
 
int
do_close_door()
{
    door_open = 0;
    remove_exit("down");
    return 1;
}
 
int
do_open_gate()
{
 
 
   add_item("track","You kneel down and examine the track closely. " +
        "It's a small path leading through the hedge. Without the " +
        "opening in the hedge it's hard to see the track which clearly " +
        "have been wider once long ago. Now it's almost completely " +
        "overgrown by the thick grass.\n");
   add_exit("track1","east");
   gate_open = 1;
   return 1;
}

int
query_gate_open()
{
    return gate_open;
}
 
 

int
climb_wall(string str)
{
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
