/*
 * /d/Gondor/anorien/std/bsmt_base.c
 * Base room for lower levels in Cair Andros
 *
 * Varian - February, 2020
 *
 */

#include "../defs.h"

inherit ANORIEN_STD_DIR + "room";

#include <macros.h>
#include "/d/Gondor/anorien/std/descriptors.c"

void set_items_hall();
void set_items_barracks();

/*
 * Function name:        create_bs_room
 * Description  :        Use create_bs_room() to make rooms in the
 *                       lower levels of Cair Andros which use 
 *                       information from this file
 */
void create_bs_room() 
{
}

nomask void create_anorien_room() 
{
    create_bs_room();
    reset_room();
}

/*
 * Function name:        set_items_hall
 * Description  :        Items added to lower level rooms in Cair Andros
 *                       hallways when you include the line
 *                       set_items_fort(); 
 *                       Use for all hallway rooms below Cair Andros
 */
void
set_items_hall()
{
    add_item( ({"intersection", "large intersection"}),
        "There is a large intersection where the corridor and " +
        "hallway meet in the middle of the lower levels here.\n");
    add_item( ({"corridor", "corridors"}),
        "There is a long corridor running east and west across " +
        "the lower levels of Cair Andros.\n");
    add_item( ({"hall", "hallway"}),
        "There is a wide hallway running north and south across " +
        "the lower levels of Cair Andros.\n");
    add_item( ({"torch", "torches", "sconce", "sconces", "light"}),
        "There are several torches mounted in sconces along the " +
        "walls nearby, each one burning brightly to provide " +
        "light in the lower levels of Cair Andros.\n");
    add_item( ({"fortress", "fortifications", "stone fort", "fort",
            "stone fortress", "stone fortifications", "tall fort",
            "tall stone fort", "tall stone fortifications",
            "tall fortifications", "tall fortress",
            "tall stone fortress"}),
        "You are currently in the lower levels of Cair Andros. the " +
        "tall stone fortress which guards Gondor at the fords " +
        "which cross the Anduin at the northern edge of Ithilien.\n");
    add_item( ({"stone", "stones", "stone block", "stone blocks",
            "grey stone", "grey stones", "grey stone block",
            "grey stone blocks", "rock", "rocks", "granite",
            "granite block", "granite blocks", "block", "blocks"}),
        "It seems like the whole fortress has been made from massive " +
        "blocks of granite, precisely cut and fit in a very sturdy " +
        "formation. The walls, floor and ceiling all seem to be " +
        "cut from the same grey stone.\n");
    add_item( ({"gondor", "kingdom"}),
        "Gondor is the southern kingdom of the Numenoreans who " +
        "settled in Middle Earth. While still strong, it is but a " +
        "shadow of the power and glory it once enjoyed.\n");
    add_item( ({"numenor", "numenorians", "dunedain", "westernesse"}),
        "Numenor was a great island kingdom that existed a long time " +
        "ago, but sank into the sea. The survivors, known today as " +
        "the Dunedain, sailed to Middle-Earth where they established " +
        "great kingdoms such as Gondor.\n");
    add_item( ({"anorien", "plains", "plains of anorien"}),
        "The plains of Anorien lies to the west, on the other side " +
        "of the Anduin.\n");
    add_item( ({"ithilien", "forest", "forests"}),
        "The forests of Ithilien is east of the fort, on the other " +
        "side of the Anduin.\n");
    add_item( ({"anduin", "river"}),
        "The Anduin is the great river, flowing north to south, " +
        "surrounding the rocky island of Cair Andros.\n");
    add_item( ({"ford", "fords"}),
        "A wide ford passes across Cair Andros, connecting the " +
        "plains of Anorien with the forest of Northern Ithilien.\n");
    add_item( ({"island", "isle", "cair andros"}),
        "You are currently on the island of Cair Andros, inside the " +
        "fortress which guards the fords which cross the Anduin " +
        "here. On the east side of the river are the lands of " +
        "Ithilien, while to the west, the rolling plains of Anorien " +
        "can be found.\n");
    add_item( ({"level", "levels", "lower level", "lower levels"}),
        "You are currently on the lower levels within the fortress " +
        "of Cair Andros. The lower levels primarily seem to be " +
        "designed as spare sleeping quarters for the soldiers " +
        "who man the fort.\n");
    add_item( ({"upper level", "upper levels"}),
        "The upper levels of Cair Andros are where most of the " +
        "soldiers serve when on duty. A stone staircase at the " +
        "southern end of the hallway will take you back there.\n");
    add_item( ({"up", "ceiling"}),
        "The ceiling up above is made of cold grey stone, much like " +
        "almost everything else in here.\n");
    add_item( ({"down", "ground", "floor"}),
        "The floor here is made from large blocks of grey stone, " +
        "just like pretty much everything else you can see in here.\n");
}
/*
 * Function name:        set_items_barracks
 * Description  :        Items added to lower level rooms in Cair Andros
 *                       barracks when you include the line
 *                       set_items_fort(); 
 *                       Use for all barracks rooms below Cair Andros
 */
void
set_items_barracks()
{
    add_item( ({"torch", "torches", "sconce", "sconces", "light"}),
        "Several torches have been mounted on sconces in this room, " +
        "keeping the room bright with their flickering light.\n");
    add_item( ({"level", "levels", "lower level", "lower levels"}),
        "You are currently on the lower levels within the fortress " +
        "of Cair Andros. The lower levels primarily seem to be " +
        "designed as spare sleeping quarters for the soldiers " +
        "who man the fort.\n");
    add_item( ({"upper level", "upper levels"}),
        "The upper levels of Cair Andros are where most of the " +
        "soldiers serve when on duty. A stone staircase at the " +
        "southern end of the hallway will take you back there.\n");
    add_item( ({"stair", "stairway", "stairs", "stone stairway",
            "stone stair", "stone stairway", "stone staircase",
            "staircase"}),
        "There is a stone staircase at the southern end of the " +
        "hallway, leading to the upper levels of Cair Andros.\n");
    add_item( ({"wall", "walls"}),
        "There are four walls here, each of them boasting several " +
        "torches mounted on them. Did you want to examine one " +
        "in particular?\n");
    add_item( ({"southeast", "southeastern wall","southeastern corner",
            "southwest", "southwestern wall","southwestern corner",
            "northeast", "northeastern wall","northeastern corner",
            "northwest", "northwestern wall","northwestern corner"}),
        "You don't see anything of interest in this corner of the " +
        "barracks.\n");
    add_item( ({"corner", "corners"}),
        "Since this room is rectagular in shape, there are naturally " +
        "four corners. There is nothing interesting in any of them, " +
        "but you could probably examine them if you were really " +
        "bored.\n");
    add_item( ({"up", "ceiling"}),
        "The ceiling up above is made of cold grey stone, much like " +
        "almost everything else in here.\n");
    add_item( ({"down", "ground", "floor"}),
        "The floor here is made from large blocks of grey stone, " +
        "just like pretty much everything else you can see in here.\n");
    add_item( ({"wood", "wooden box", "wooden boxes", "wood box"}),
        "This is just a wooden box, constructed for the purpose " +
        "of making a soldier's pallet.\n");
    add_item( ({"straw", "bundle of straw", "bundle"}),
        "There is a large bundle of straw inside each of the " +
        "wooden boxes here, providing a little bit of comfort " +
        "for the soldiers when they sleep.\n");
    add_item( ({"linen", "blanket", "thick blanket", "linen blanket",
            "thick linen blanket"}),
        "There is a thick linen blanket covering each of the " +
        "pallets here.\n");
    add_item( ({"fortress", "fortifications", "stone fort", "fort",
            "stone fortress", "stone fortifications", "tall fort",
            "tall stone fort", "tall stone fortifications",
            "tall fortifications", "tall fortress",
            "tall stone fortress"}),
        "You are currently in the lower levels of Cair Andros. the " +
        "tall stone fortress which guards Gondor at the fords " +
        "which cross the Anduin at the northern edge of Ithilien.\n");
    add_item( ({"stone", "stones", "stone block", "stone blocks",
            "grey stone", "grey stones", "grey stone block",
            "grey stone blocks", "rock", "rocks", "granite",
            "granite block", "granite blocks"}),
        "It seems like the whole fortress has been made from massive " +
        "blocks of granite, precisely cut and fit in a very sturdy " +
        "formation. The walls, floor and ceiling all seem to be " +
        "cut from the same grey stone.\n");
    add_item( ({"gondor", "kingdom"}),
        "Gondor is the southern kingdom of the Numenoreans who " +
        "settled in Middle Earth. While still strong, it is but a " +
        "shadow of the power and glory it once enjoyed.\n");
    add_item( ({"numenor", "numenorians", "dunedain", "westernesse"}),
        "Numenor was a great island kingdom that existed a long time " +
        "ago, but sank into the sea. The survivors, known today as " +
        "the Dunedain, sailed to Middle-Earth where they established " +
        "great kingdoms such as Gondor.\n");
    add_item( ({"anorien", "plains", "plains of anorien"}),
        "The plains of Anorien lies to the west, on the other side " +
        "of the Anduin.\n");
    add_item( ({"ithilien", "forest", "forests"}),
        "The forests of Ithilien is east of the fort, on the other " +
        "side of the Anduin.\n");
    add_item( ({"anduin", "river"}),
        "The Anduin is the great river, flowing north to south, " +
        "surrounding the rocky island of Cair Andros.\n");
    add_item( ({"ford", "fords"}),
        "A wide ford passes across Cair Andros, connecting the " +
        "plains of Anorien with the forest of Northern Ithilien.\n");
    add_item( ({"box", "boxes"}),
        "These boxes are just frames for the bunks here.\n");
    add_item( ({"island", "isle", "cair andros"}),
        "You are currently on the island of Cair Andros, inside the " +
        "fortress which guards the fords which cross the Anduin " +
        "here. On the east side of the river are the lands of " +
        "Ithilien, while to the west, the rolling plains of Anorien " +
        "can be found.\n");
}