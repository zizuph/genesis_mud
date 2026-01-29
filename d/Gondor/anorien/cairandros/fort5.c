/*
 * Cair Andros - /d/Gondor/anorien/cairandros/fort5.c
 *
 * Varian 2016
 */

#pragma strict_types
#include "../defs.h"

inherit ANORIEN_STD_DIR + "room";
#include <stdproperties.h>
#include <macros.h>

object door;

/*
 * Function name:        create_anorien_room()
 * Description  :        Creates a room in Anorien
 */
nomask void 
create_anorien_room() 
{    
    set_short("Inside the fort at Cair Andros");
    set_long("Looking around, you see that you are inside the tall stone " +
        "fortress that guards the island and fords of Cair Andros. Running " +
        "east and west, there is a long stone hallway cutting through the " +
        "middle of the fort, while stone stairs climb up the southern wall " +
        "to read the parapet above. A sturdy wooden door stands in the " +
        "middle of the northern wall, while to the east, you can see the " +
        "Anduin River running shallow as a ford connects the island to the " +
        "forests and hills of Ithilien on the eastern bank.\n"); 

    add_item(({"stair","stairs","step","steps","stone stair","stone stairs",
            "staircase","stone staircase"}),
        "These sturdy stone stairs run up to the parapet atop the " +
        "fortress.\n");
    add_item(({"hall","hallway"}),
        "This stone hallway runs east and west through the middle of " +
        "the fort.\n");
    add_item(({"wall", "walls"}),
        "You are in the middle of a long hallway, with walls to both the " +
        "north and south. Which one did you want to examine?\n");
    add_item(({"east","southeast","northeast","horizon","eastern horizon"}),
        "Looking east, you see the Anduin River flowing past, separating " +
        "you from the wooded hills of Ithilien that stand in the shadow " +
        "of jagged mountains in the distance.\n");
    add_item(({"north", "northern wall"}),
        "The northern wall here is rather featureless, aside from the " +
        "strong wooden door in front of you.\n");
    add_item(({"west", "western hallway", "northwest","southwest"}),
        "Looking to the west down the hallway, you can see a few additional " +
        "doors in the distance, dimly illuminated by the torches that " +
        "hang on the southern wall.\n");
    add_item(({"south", "southern wall"}),
        "There is a stone staircase running up the southern wall, leading " +
        "to the parapet atop the fortress. Several torches have been " +
        "mounted along the southern wall, well spaced out in regular " +
        "intervals.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling up above is made of cold grey stone, much like almost " +
        "everything else in here.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor here is made from large blocks of grey stone, just like " +
        "pretty much everything else you can see in here.\n");
    add_item(({"river", "anduin", "bank", "banks", "waters", "great river"}),
        "This is the great river Anduin, whose legendary waters cut through " +
        "the lands of Middle-Earth for hundreds of miles, before emptying " +
        "out into the sea far to the south.\n");
    add_item(({"west bank", "western bank"}),
        "You are on the eastern edge of the fort, you can't see the " +
        "western bank of the Anduin from here!\n");
    add_item(({"east bank", "eastern bank"}),
        "The eastern bank of the Anduin is some distance away, on the " +
        "other side of the ford. The green hills of Ithilien are partially " +
        "hidden by the woods that grow against the riverside.\n");
    add_item(({"grasses", "grass", "ground", "field", "fields", "green grass"}),
        "The plains of Anorien are filled with fields of tall green " +
        "grass that stretch out to the west as far as the eye can see, " +
        "decorated with countless colourful wildflowers growing everywhere.\n");
    add_item(({"hill", "hills", "woods", "forest", "forests", "green hills"}),
        "The woods of Ithilien are visible to the east, covering the " +
        "rolling hills that spread out towards the mountains.\n");
    add_item(({"mountain", "mountains", "mountains of shadow", "ephel duath"}),
        "Peeking up above the trees along the eastern horizon, are the " +
        "jagged peaks of the mountains of shadow.\n");
    add_item(({"fort","fortress","fortifications","stone fort","stone",
            "stone fortress","stone fortifications","tall fortifications",
            "tall stone fort","tall stone fortifications","tall fort",
            "tall fortress","tall stone fortress"}),
        "You are standing inside the tall stone fortress that guards the " +
        "fords which cross the Anduin at Cair Andros. The fort is in " +
        "very good condition, and appears to be well tended by the " +
        "soldiers of Gondor. \n");
    add_item(({"stone","stones","stone block","stone blocks"}),
        "The entire fortress appears to have been made from massive stone " +
        "blocks, precisely cut and fit in a very sturdy formation.\n");
    add_item(({"gondor"}),
        "Gondor is the southern kingdom of the Numenoreans who settled " +
        "in Middle Earth. While still strong, it is but a shadow of " +
        "the power and glory it once enjoyed.\n");
    add_item(({"numenor","numenorians","dunedain","westernesse"}),
        "Numenor was a great island kingdom that existed a long time " +
        "ago, but sank into the sea. The survivors, known today as the " +
        "Dunedain, sailed to Middle-Earth where they established " +
        "great kingdoms such as Gondor.\n");
    add_item(({"anorien"}),
        "The land of anorien lies to the west, on the other side of the " +
        "Anduin.\n");
    add_item(({"ithilien"}),
        "The wooded hills of Ithilien are visible to the east, on the " +
        "far side of the river.\n");
    add_item(({"island","isle","caer andros"}),
        "You are currently on the island of Cair Andros, inside the " +
        "fortress which guards the fords which cross the Anduin here. " +
        "On the east side of the river are the lands of Ithilien, while " +
        "to the west, the rolling plains of Anorien can be found.\n");
    add_item(({"torch","torches"}),
        "You can see that there are several torches mounted in iron " +
        "brackets, stretched out along the southern wall in regular " +
        "intervals.\n");
    add_item(({"bracket","brackets","iron bracket","iron brackets"}),
        "These are simple iron brackets, mounted securely on the " +
        "southern wall, designed to hold torches to provide light.\n");

    set_no_exit_msg(({"northwest","northeast","southwest","southeast"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");
    set_no_exit_msg(({"south"}),
        "Perhaps you should try going up the stairs instead of through " +
        "them?\n");

    add_npc(CA_NPC_DIR + "captain");
    add_npc(CA_NPC_DIR + "soldier", 3);

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CAIRANDROS_DIR + "fort4", "west",0,0,0);
    add_exit(CAIRANDROS_DIR + "e_ford","east",0,0,0);
    add_exit(CAIRANDROS_DIR + "caf5","up",0,0,0);

    door = clone_object(AN_OBJ_DIR + "fort_door_in_se");
    door->move(TO);
}