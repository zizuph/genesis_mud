/*
 * Cair Andros - /d/Gondor/anorien/cairandros/fort12.c
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
    set_long("You are standing inside the sturdy confines of the " +
        "large fortress that guards the island of Cair Andros. A long " +
        "stone hallway runs to the west and into the middle of the " +
        "fortress, while stone stairs march up the northern wall " +
        "to the parapet above. In the middle of the southern wall, you " +
        "can see a strong wooden door. This is the eastern end of the " +
        "corridor, and the only options available to leave here are up the " +
        "stairs, down the hallway or through the door.\n"); 

    add_item(({"stair","stairs","step","steps","stone stair","stone stairs",
            "staircase","stone staircase"}),
        "These sturdy stone stairs run up to the parapet atop the " +
        "fortress.\n");
    add_item(({"hall","hallway","corridor"}),
        "This stone hallway runs east and west through the middle of " +
        "the fort.\n");
    add_item(({"wall", "walls"}),
        "You are at the eastern end of a long hallway, with walls to both " +
        "the north and south. Which wall did you want to examine?\n");
    add_item(({"east","eastern wall","southeast","northeast"}),
        "There is a very solid looking stone wall at the end of the " +
        "hallway here.\n");
    add_item(({"south", "southern wall"}),
        "The southern wall here is rather featureless, aside from the " +
        "strong wooden door in front of you.\n");
    add_item(({"west", "western hallway", "northwest","southwest"}),
        "Looking to the west down the hallway, you can see a few additional " +
        "doors in the distance, dimly illuminated by the torches that " +
        "hang on the northern wall.\n");
    add_item(({"north", "northern wall"}),
        "There is a stone staircase running up the northern wall, leading " +
        "to the parapet atop the fortress. Several torches have been " +
        "mounted along the northern wall, well spaced out in regular " +
        "intervals.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling up above is made of cold grey stone, much like almost " +
        "everything else in here.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor here is made from large blocks of grey stone, just like " +
        "pretty much everything else you can see in here.\n");
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
    add_item(({"torch","torches"}),
        "You can see that there are several torches mounted in iron " +
        "brackets, stretched out along the northern wall in regular " +
        "intervals.\n");
    add_item(({"bracket","brackets","iron bracket","iron brackets"}),
        "These are simple iron brackets, mounted securely on the " +
        "northern wall, designed to hold torches to provide light.\n");
    add_item(({"ithilien"}),
        "The land of Ithilien lies to the east, on the other side of the " +
        "Anduin.\n");
    add_item(({"anorien"}),
        "The rolling plains of Anorien are west of the fortress, on the " +
        "other side of the river.\n");
    add_item(({"island","isle","caer andros"}),
        "You are currently on the island of Cair Andros, inside the " +
        "fortress which guards the fords which cross the Anduin here. " +
        "On the east side of the river are the lands of Ithilien, while " +
        "to the west, the rolling plains of Anorien can be found.\n");

    set_no_exit_msg(({"northwest","northeast","southwest","southeast","east"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");
    set_no_exit_msg(({"north"}),
        "Perhaps you should try going up the stairs instead of through " +
        "them?\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CAIRANDROS_DIR + "fort11", "west",0,0,0);
    add_exit(CAIRANDROS_DIR + "caf13","up",0,0,0);

    door = clone_object(AN_OBJ_DIR + "fort_door_in_ne");
    door->move(TO);

    add_npc(CA_NPC_DIR + "officer");
    add_npc(CA_NPC_DIR + "guard", 2);
    add_npc(CA_NPC_DIR + "guard2", 1);
}