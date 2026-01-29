/*
 * Cair Andros - /d/Gondor/anorien/cairandros/fort6.c
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
    set_long("You are currently wandering around a fortress guarding the " +
        "island and fords of Cair Andros. It seems as if everything inside " +
        "the fort is rather plain and lacking decoration, having been made " +
        "for functionality rather than beauty. Heavy blocks of grey stone " +
        "have been used to build the walls of the corridor you are walking " +
        "along, the same stone that has been used to build the floor and " +
        "ceiling. At both the northern and southern ends of the hallway, " +
        "you can see thick doors of oak offering security and protection " +
        "against any potential invaders..\n"); 

    add_item(({"stair","stairs","step","steps","stone stair","stone stairs",
            "staircase","stone staircase"}),
        "You do not see any stairs here, but you do recall seeing some " +
        "in the corner of the fortress.\n");
    add_item(({"hall","hallway","corridor"}),
        "This stone hallway runs north to the other side of the fortress.\n");
    add_item(({"wall", "walls"}),
        "You are at the southern end of a long hallway, with walls to both " +
        "the east and west. Which wall did you want to examine?\n");
    add_item(({"east","eastern wall"}),
        "The eastern wall seems rather plain and boring, as it is largely " +
        "unadorned and made up of nothing but large blocks of grey stone " +
        "with the occasional torch mounted upon it.\n");
    add_item(({"south", "southern wall","southeast","southwest"}),
        "The corridor ends at the southern wall, where there is nothing " +
        "but a sturdy door made of solid oak that provides passage into " +
        "another corridor.\n");
    add_item(({"west", "western wall"}),
        "The western wall seems rather plain and boring, as it is largely " +
        "unadorned and made up of nothing but large blocks of grey stone " +
        "with the occasional torch mounted upon it.\n");
    add_item(({"north", "northern hallway","northwest","northeast",
            "northern corridor"}),
        "Looking to the north, you can see the long stone hallway ending " +
        "at a solid wooden door.\n");
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
        "brackets, stretched out along the walls on either side of you " +
        "in regular intervals.\n");
    add_item(({"bracket","brackets","iron bracket","iron brackets"}),
        "These are simple iron brackets, mounted securely on the " +
        "walls, designed to hold torches to provide light.\n");
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

    set_no_exit_msg(({"northwest","northeast","southwest","southeast",
            "east","west"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CAIRANDROS_DIR + "fort7","north",0,0,0);

    door = clone_object(AN_OBJ_DIR + "hall_door_out_s");
    door->move(TO);
}