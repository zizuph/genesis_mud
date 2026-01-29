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
    set_short("The gate to the manor");
    set_long("You stand right in front of a small gate to a " +
        "large white manor. The gate hangs loose on two hinges " +
        "and is wide open for anyone to pass through. A small " +
        "gravel path leads up to the main entrance over the " +
        "grass lawn that surrounds the house.\n");
    add_item(({"house","manor"}),"You take a closer look at the house. " +
        "It is clearly the main building of this farm. From this " +
        "distance it looks as a nice and proud building, but it is " +
        "hard to tell from here.\n");
    add_item(({"lawn","grasslawn","grass"}),"From this side of the gate " +
        "it is looks like it is in a bad shape. Clearly it is uncut, " +
        "and as the rest of the farm it would probably need some work.\n");
    add_item(({"fence","wooden fence"}),"You walk forward to the fence " +
        "and take a closer look. It is about half the height of a human " +
        "and it stretches between the lawn and a thick hedge that grows " +
        "outside the fence.\n");
    add_item("hedge","You take a few steps back and examine the hedge. " +
        "It is high and well grown and it is impossible to see anything " +
        "through it. Trying to pass through is impossible.\n");
    add_item("gate","You try to swing the gate back and forth on its " +
        "hinges but stop at once. The hinges are very rusty and it " +
        "seems as the gate would fall down from another attempt. " +
        "Once, long ago, it must have been a nice and white painted " +
        "gate, but now there is no paint left and the gate is not " +
        "nice looking at all.\n");
    add_item("hinges","You cast a brief eye on the two hinges. They " +
        "are very rusty but they look as if they are securely stuck " +
        "to the two wooden poles that are surrounding the gate and " +
        "are the start of the wooden fence that surrounds " +
        "the manor.\n");
    add_item(({"poles","wooden poles"}),"The wooden poles are stuck " +
        "hard into the ground. When you step forward and shake them " +
        "they do not give after an inch. The gate hangs on two hinges " +
        "bolted into one of the poles.\n");
    set_terrain(TERRAIN_OPENSPACE);
    set_terrain(TERRAIN_OUTSIDE);
    add_exit("south_side","north","@@north");
    add_exit("yard","south");
    reset_room();
}

void
reset_room()
{

}

int
north()
{
    write("You pass through the open gate and across " +
        "the gravel path to the entrance.\n");
    return 0;
}
