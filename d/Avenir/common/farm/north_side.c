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

void
create_room()
{
    set_short("The north side of the manor");
    set_long("You stand at the north side of the building. It looks " +
        "like the other sides. Around the house leads the gravel " +
        "path and the lawn spreads out to the fence and hedge " +
        "surrounding it.\n");
    add_item(({"house","manor","building"}),"You take a closer look at the house. " +
        "This clearly is the main building of this farm. Once it must " +
        "have been a nice and proud building, but now years of " +
        "non existing maintenance has taken its toll. The white paint " +
        "has started to flake off and everything looks old and dirty.\n");
        add_item(({"paint","colour"}),"You scrape off some of the old " +
        "dry paint from the house wall. It has been white once long " +
        "ago but is now gray and dry and you see flakes constantly " +
        "drop to the ground from the worn wall.\n");
    add_item("flakes","The flakes are just flakes of old dry paint.\n");
    add_item(({"window","windows"}),"By looking at the windows of the " +
        "manor you notice they are all in quite a bad shape. Old and " +
        "dirty unless they are broken as some of them seems to be " +
        "from this position.\n");
    add_item(({"lawn","grasslawn","grass"}),"You step out on the " +
        "grass lawn. Its uncut and weed has taken over almost " +
        "completely. You guess this hasn't always been like this " +
        "and sadly wish you could have seen the lawn in its glorious " +
        "days. Around the lawn is a wooden fence that cuts " +
        "off the grass lawn from the surrounding hedge.\n");
    add_item(({"fence","wooden fence"}),"You walk forward across the " +
        "lawn to the fence and take a closer look. Its about half the " +
        "height of a human and it stretches between the lawn and " +
        "the thick hedge.\n");
    add_item("hedge","You narrow your eyes and focus the hedge. Its " +
        "high and well grown and it is impossible to see anything " +
        "through or behind it.\n");
    add_item("tower", "You look up at the tower. It is quite amazing " +
        "and you think the view from up there must be quite stunning.\n");
    add_item(({"path","gravel path"}),"@@gravel_path@@");
    set_terrain(TERRAIN_OPENSPACE);
    set_terrain(TERRAIN_OUTSIDE);
    add_exit("east_side","southeast");
    add_exit("west_side","southwest");

    reset_room();
}

void
reset_room()
{

}
 
void
init()
{
    ::init();
        add_action("climb_wall","climb");
        add_action("enter_window","enter");
}

string
gravel_path()
{

    tell_room((THIS_DIR + "west_side"),"You hear someone walking " +
        "in the gravel on the north side of the house.\n");
    tell_room((THIS_DIR + "east_side"),"You hear someone walking " +
        "in the gravel on the east side of the house.\n");
    return "You take a step on the gravel path. There is a rasping " +
        "sound from the gravel below your feet, so you decide to " +
        "walk back to the grass.\n";
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
