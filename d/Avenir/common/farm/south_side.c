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
    set_short("The south side of the manor");
    set_long("You stand right in front of the main entrance to a " +
        "large white manor. A small stone stair with two steps leads " +
        "up to the main door. Everything here has all signs of being abandoned " +
        "long long ago. Uncut grass, broken windows and not a living " +
        "soul in sight. The house colour, once shiny white, has almost all " +
        "scaled off from the burning sun.\n");
        add_item("entrance", "@@long");
    add_item(({"house","manor","building"}),"You take a closer look at the house. " +
        "This clearly is the main building of this farm. Once it must " +
        "have been a nice and proud building, but now years of " +
        "nonexistent maintenance has taken its toll. The white paint " +
        "has started to flake off and everything looks old and dirty.\n");
    add_item(({"door","main door"}), "You look at the old door. It looks " +
        "quite robust but as the rest of this place it suffers from " +
        "a total lack of maintenance.\n");
    add_item(({"paint","colour"}),"You scrape off some of the old dry paint " +
        "from the house wall. It has been white once long ago but is now gray " +
        "and dry and you see flakes constantly drop to the ground from the worn " +
        "wall.\n");
    add_item(({"window","windows"}),"By looking at the windows of the manor you " +
        "notice they are all in quite a bad shape. Old and dirty unless they " +
        "are broken as some of them seems to be from this position.\n");
    add_item(({"stair","stairs"}),"You take a step on the first stone step. A massive " +
        "stone slab made into a stair.\n");
    add_item(({"step","slab"}),"You touch the stone step with your hand. The outer " +
        "ends are smooth and straight, but the middle is a little worn down by " +
        "many years of use.\n");
    add_item(({"lawn","grasslawn","grass"}),"You step out on the grass lawn. " +
        "Its uncut and weed has taken over almost completely. You guess this " +
        "hasnt always been like this and sadly wish you could have seen the " +
        "lawn in its glorious days. Around the lawn is a wooden fence that cuts " +
        "off the grass lawn from the surrounding hedge.\n");
    add_item(({"fence","wooden fence"}),"You walk forward across the lawn to the " +
        "fence and take a closer look. Its about half the height of a human and " +
        "it stretches between the lawn and the thick hedge.\n");
    add_item("hedge","You narrow your eyes and focus the hedge. Its high and " +
        "well grown and its impossible to see anything through or behind it.\n");
    add_item("tower", "You look up at the tower. It is quite amazing " +
        "and you think the view from up there must be quite stunning.\n");
    set_terrain(TERRAIN_OPENSPACE);
    set_terrain(TERRAIN_OUTSIDE);
    add_exit("hall","in");
    add_exit("east_side","northeast");
    add_exit("west_side","northwest");
    add_exit("gate","south");

    reset_room();
}

void
reset_room()
{

}


