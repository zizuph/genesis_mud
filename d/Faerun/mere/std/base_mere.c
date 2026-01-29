/*
 * Base Room for High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/d/Faerun/highroad/std/base_common.c";
inherit FAERUN_OUTDOOR_BASE;

void
create_mere()
{
}

void
create_faerun_room()
{
    ::create_faerun_room();
    add_prop(ROOM_S_MAP_FILE, "mere_map.txt");

    extraline = "Additional room descriptions goes here.";

    set_short("Along the High Road");    
   
    create_mere();

    add_item(({"mere", "swamp", "marsh", "ground"}),
        "This is a large, marsh flooded by seawater over the ages. The " +
        "mere is vast and full of unimaginable creatures. Twisted trees " +
        "and large, overgrown vegetation grow on hillocks in the swamp. " +
        "The water is black with mists twisting from the surface. The " +
        "smell of rot and death fills the air.\n");
    add_item(({"vegetation"}),
        "Growing over and around the ground are vines and other thick vegetation. The ground is covered with sickly looking grasses which has been trampled to the ground.\n");
    add_item(({"hillocks"}),
        "They are small hills scattered through the mere. Grass grows on them, hiding what they could be made of.\n");
    add_item(({"grass"}),
        "The grass looks trampled and is yellow colored. It grows in patches through the swamp, growing up around the trees. The grass looks sickly growing throughout the swamp.\n");
    add_item(({"water"}),
        "The water is dark, sickly looking, and smells horrid. Tendrils of mist rise from the pools and ground, coalescing into eerie figures. Corpses float in the water. Beneath the surface can be seen skeletons.\n");
    add_item(({"vines"}),
        "The vines climb over the trees and across the ground. They are thick and covered with leaves.\n");
    add_item(({"corpses", "floating corpses"}),
        "They float in the water and are partially submerged. They look partially decomposed and eaten. Many of them are of dead animals and unfortunate creatures that have wandered into the swamp and didn't get out alive.\n");
    add_item(({"mist", "mists"}),
        "The mists are damp and rise from the pools and the ground. They coalesce into eerie figures and dance around you hypnotically. The mists smell of death as they blow past you.\n");
    add_item(({"trees", "twisted trees"}),
        "The trees are dead and stand scattered throughout the swamp. They look diseased and broken. Many of the trees are twisted.\n");

    add_room_tell("Mists drift past you, swirling around and floating away.");
    add_room_tell("A rank stench floats by.");
    add_room_tell("Something rustles in the grass.");
    add_room_tell("A sinister shadow flies over head and disappears " +
        "into the distance.");
    add_room_tell("Ripples appear in a nearby pool.");

}

// Mere descriptions

string mere_descr1(string str)
{
    return "Twisted trees and other thick vegetation cover the surface " +
    "of the swamp. The air is thick with the stench of rot and the water " +
    "dark and oily looking. Thick fogs hide everything visible. "+ str;
}

string mere_descr2(string str)
{
    return "A thick stench fills the air. It smells like rotting bodies " +
    "and the sea. Thick vegetation dots the swamp's surface. "+ str;
}

string mere_descr3(string str)
{
    return "Pools of black water surround hillocks of vegetation. Threads " +
    "of mist rise from the cold saltwater pools. Vines and thick vegetation " +
    "cover twisted trees which dot the swamp. "+ str;
}

string mere_descr4(string str)
{
    return "Fogs swirl around the swamp, hiding dangers that lurk about. " +
    "A stench of dead bodies mix with the smell of saltwater, filling " +
    "the air with the stench of death. Pools of black, opaque water " +
    "surround hillocks of twisted trees, vines, and vegetation. "+ str;
}

string mere_descr5(string str)
{
    return "The black swamp water looks oily and hides rotting bodies. " +
    "The bodies look hideous and gnawed on. Mists float off the waters " +
    "and dance around the twisted trees and thick vegetation. "+ str;
}

string mere_descr6(string str)
{
    return "Twisted trees, vines, and thick vegetation cloak the mist-" +
    "shrouded surface of the cold saltwater swamp. Its air is foul with " +
    "rotting stenches, and its water is black and opaque. "+ str;
}


void add_road()
{
    add_item(({"road"}),
        "The road runs along the edge of the mere. It is well travelled " +
        "and snakes across the land running northwest and southeast.\n");
}
void add_claws_ground()
{
    add_item(({"claw marks", "marks", "narrow grooves", "grooves", "scratches"}),
        "They are deep, narrow grooves in the ground. They look like they were made by large animals. The ground is torn up from the clawing done here.\n");
}

void add_claws_trees()
{
    add_item(({"claw marks", "marks", "narrow grooves", "grooves", "scratches"}),
        "They are deep, narrow grooves in the trees. The grooves are vertical and seem to have been made by wild animalsThe ground is torn up from the clawing done to the trees.\n");
}

void add_footprints()
{
    add_item(({"prints", "footprints", "clawprints"}),
        "The clawprints are from countless animals that have wandered this way. Some are deep, others shallow or even faint. They all have multiple toes and some even have claw marks.\n");
}

