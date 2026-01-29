/*
 * Cair Andros - /d/Gondor/anorien/cairandros/storsw.c
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
    set_long("You are in a small storage room that is inside the fortress " +
        "set on the island of Cair Andros. Several barrels and boxes " +
        "containing provisions for the garrison have been stacked here. " +
        "The walls are made from large blocks of grey stone, with a " +
        "large wooden door that stands in the middle of the southern " +
        "wall. A flickering torch mounted on the western wall provides " +
        "plenty of light for you to see by. On the other side of the door, " +
        "you can go back into the hallway that brought you here and into " +
        "the rest of the fort.\n"); 

    add_item(({"stair","stairs","step","steps","stone stair","stone stairs",
            "staircase","stone staircase"}),
        "You do not see any stairs here, but you do recall seeing some " +
        "in the corner of the fortress.\n");
    add_item(({"hall","hallway","corridor"}),
        "You are in the middle of a storage room! But there is a " +
        "hallway on the other side of the door.\n");
    add_item(({"wall", "walls"}),
        "There are indeed four walls in this room, did you want to " +
        "examine one in particular?\n");
    add_item(({"west", "western wall"}),
        "The eastern wall is rather plain, aside from the torch that hangs " +
        "on the wall, there is nothing much to look at.\n");
    add_item(({"north", "northern wall"}),
        "The northern wall is rather plain, with nothing much to look " +
        "at.\n");
    add_item(({"east", "eastern wall"}),
        "The western wall is rather plain, with nothing much to look " +
        "at.\n");
    add_item(({"south", "southern wall"}),
        "There is a large wooden door in the middle of the southern wall, " +
        "providing access into the rest of the fortress.\n");
    add_item(({"northeast","northeastern corner"}),
        "There is nothing interesting to see in the northeastern corner of " +
        "this storage room.\n");
    add_item(({"northwest", "northwestern corner"}),
        "There is nothing interesting to see in the northwestern corner of " +
        "this storage room.\n");
    add_item(({"southwest", "southwestern corner"}),
        "There is nothing interesting to see in the southwestern corner of " +
        "this storage room.\n");
    add_item(({"southeast", "southeastern corner"}),
        "There is nothing interesting to see in the southeastern corner of " +
        "this storage room.\n");
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
        "This torch is burning brightly, providing light from its perch " +
        "in the iron bracket that holds it to the western wall.\n");
    add_item(({"bracket","brackets","iron bracket","iron brackets"}),
        "This iron bracket holds a burning torch tight against the " +
        "western wall, where it provides light for the entire storage " +
        "room.\n");
    add_item(({"boxes","box"}),
        "There are several boxes of provisions stacked neatly in the " +
        "middle of the storage room. They are presumably here to supply " +
        "the garrison of Gondorian soldiers.\n");
    add_item(({"barrels","barrel"}),
        "These barrels have been stacked beside the boxes, and appear to " +
        "be carrying provisions for the Gondorian soldiers stationed in " +
        "the fort.\n");
    add_item(({"provisions","food","supplies"}),
        "This storage room appears to be used to hold all of the provisions " +
        "stored here in the barrels and boxes.\n");
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
            "north","east","west"}),
        "Those walls sure are solid! It does not look like there is any " +
        "way out except by using the door in the southern wall.\n");

    add_prop(ROOM_I_INSIDE,1);

    door = clone_object(AN_OBJ_DIR + "storage_door_out_sw");
    door->move(TO);
}