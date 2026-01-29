/*
 * Cair Andros - /d/Gondor/anorien/cairandros/bar2.c
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
    set_short("Inside some barracks at Cair Andros");
    set_long("You are currently standing inside some barracks that " +
        "have been clearly designed for the sodiers who serve in this " +
        "fortress. A sturdy wooden door stands in the middle of the " +
        "southern wall, while the barracks extend further to the " +
        "south where some more bunks have been laid out. The rest of " +
        "the room is very plain, with only a handful of bunks breaking " +
        "up the thick stone blocks that make up the walls, ceiling and " +
        "floor.\n"); 

    add_item(({"hall","hallway"}),
        "You are inside the barracks, there is probably a hallway on the " +
        "other side of the door however.\n");
    add_item(({"wall", "walls"}),
        "This is a room, and like most rooms, it has walls. Did you want " +
        "to examine a particular wall?\n");
    add_item(({"south", "southern wall"}),
        "The southern wall is at the far end of the barracks, but what " +
        "you can see from here suggests that it is made of stone like " +
        "all of the other walls. There appears to be a wooden door in the " +
        "middle of the wall, \n");
    add_item(({"west", "western wall","east","eastern wall"}),
        "This is a plain stone wall with several bunks for soldiers pushed " +
        "up against it.\n");
    add_item(({"north", "northern wall"}),
        "This is a fairly stout looking stone wall with a sturdy door made " +
        "of solid oak in the middle of it.\n");
    add_item(({"southeast", "southeastern wall","southeastern corner",
            "southwest", "southwestern wall","southwestern corner",
            "northeast", "northeastern wall","northeastern corner",
            "northwest", "northwestern wall","northwestern corner"}),
        "You don't see anything of interest in this corner of the " +
        "barracks.\n");
    add_item(({"corner", "corners"}),
        "Since this room is rectagular in shape, there are naturally four " +
        "corners. There is nothing interesting in any of them, but you " +
        "could probably examine them if you were really bored.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling up above is made of cold grey stone, much like almost " +
        "everything else in here.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor here is made from large blocks of grey stone, just like " +
        "pretty much everything else you can see in here.\n");
    add_item(({"bunk", "bunks"}),
        "These bunks are really not much to look at, just a place for " +
        "soldiers to sleep when off-duty.\n");
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
        "The land of Anorien lies to the west, on the other side of the " +
        "Anduin.\n");
    add_item(({"ithilien"}),
        "The land of Ithilien is east of the fort, on the other side of " +
        "the Anduin.\n");
    add_item(({"island","isle","caer andros"}),
        "You are currently on the island of Cair Andros, inside the " +
        "fortress which guards the fords which cross the Anduin here. " +
        "On the east side of the river are the lands of Ithilien, while " +
        "to the west, the rolling plains of Anorien can be found.\n");

    set_no_exit_msg(({"northwest","northeast","southwest","southeast",
            "east","west"}),
        "Those walls sure are solid! You will have to try moving in " +
        "a different direction.\n");

    add_npc(CA_NPC_DIR + "captain");
    add_npc(CA_NPC_DIR + "soldier", 3);
    add_npc(CA_NPC_DIR + "soldier2", 2);

    add_prop(ROOM_I_INSIDE,1);

    add_exit(CAIRANDROS_DIR + "bar1", "south",0,0,0);

    door = clone_object(AN_OBJ_DIR + "fort_door_out_ne");
    door->move(TO);
}