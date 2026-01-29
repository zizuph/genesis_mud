/*
 * base_common.c
 *
 * This file contains functions and routines that are used in
 * multiple files.
 * -- Finwe, February 2017
 */

#include "/d/Faerun/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_OUTDOOR_BASE;

void add_castle_never()
{
    add_item(({"ruins", "castle ruins", "castle never", "castle grounds", 
            "castle"}),
        "The castle is in ruins and hasn't been rebuilt. At one time " +
        "it looks like it was a large structure, but now it has been " +
        "reduced to toppled towers, collapsed walls and ceilings. " +
        "Stone rubble litters the grounds and a broken wall encircles " +
        "this once grand castle.\n");
    add_item(({"toppled towers"}),
        "The toppled towers of the castle ruins lay scattered around " +
        "the castle grounds. They look like they were once magnificent, " +
        "but now have been reduced to stone rubble.\n");
    add_item(({"collapsed walls", "castle walls"}),
        "The castle walls look like they were once strong and sturdy. " +
        "Now, they are collapsed and weak looking. Holes of all sizes " +
        "punctuate the walls. \n");
    add_item(({"holes", "large holes", "medium holes", "medium size holes", 
            "small holes", "holes of all sizes"}),
        "Holes of all sizes have been punched into the castle walls and, " +
        "causing them to weaken and collapse. Over time the smaller holes " +
        "have become larger, weakening the walls and ceilings even " +
        "further.\n");
    add_item(({"ceiling", "collapsed ceilings", "ceiling"}),
        "The ceilings look like they were once made of wood, but now " +
        "there is little left of them.\n");
    add_item(({"stone rubble", "rubble"}),
        "The stone rubble lays in heaps around the castle. Most of it " +
        "is cracked and broken stone blocks that once made up the castle.\n");
    add_item(({"stone", "stone blocks", "blocks"}),
        "The stone blocks are gray, and many cracked. They are weathered " +
        "and large. Many lay around the castle grounds, broken and " +
        "unusable.\n");
    add_item(({"grounds", "castle grounds"}),
        "The castle grounds was once a nice area of Neverwinter. It is " +
        "large and covered in fallen stones and collapsed walls. Toppled " +
        "towers litter the grounds.\n");
    add_item(({"wall", "broken wall", "toppled wall"}),
        "\n");

    add_room_tell("A creaking sound reverberates from somewhere in the " +
        "castle ruins.");
}


/*
 * Function name : add_river
 * Description   : adds descr of neverwinter river
 */
void add_river(string direction)
{
    add_item(({"river", "neverwinter river"}),
        "The river is " + direction + " of here and runs west through " +
        "Neverwinter. The river looks bright and feels warm, even this " +
        "far away. \n");
    add_room_tell("The sound of a river echos from below.");
}

/*
 * Function name : add_dolphin_bridge
 * Description   : adds descr of the Dragon Bridge
 */
void 
add_dolphin_bridge()
{
    add_item(({"bridge", "dolphin bridge", "large bridge"}),
        "It is wide and made from large white blocks of stone. Dolphins are carved into the sides of the bridge. It was once a grand bridge spanning the Neverwinter river, but now the bridge has fallen into disrepair and fewer people use it than they once did.\n");
    add_item(({"dolphins", "carved dolphins"}),
        "The dolphins are carved from stone and stretch horizontally acrossed the river. They are chipped and broken but still retain some beauty form days gone by.\n");
    add_item(({"white blocks of stone", "white stone blocks"}),
        "The white stone blocks are weathered and cracked. They are part of the Dolphin bridge. It looks like there have been attempts to fix the white stone blocks, but the work was shoddy. Dolphins have been carved into the blocks,\n");

    add_room_tell("Someone cautiously crosses over the bridge.");
    add_room_tell("River spray rises up from under the bridge.");
}


    add_item(({""}),
        "\n");
    add_item(({""}),
        "\n");
    add_item(({""}),
        "\n");
    add_item(({""}),
        "\n");
    add_item(({""}),
        "\n");

/*
 * Function name : add_XXX
 * Description   : adds descr of 
 */
void add_XX2()
{
    add_item(({"XXX"}),
        "\n");
    add_item(({"XXX"}),
        "\n");
    add_item(({"XXX"}),
        "\n");
}



//string add_light_descr(string str);
//string pr_time_descr(int i);


/*
 * Function name : add_XXX
 * Description   : adds descr of
 */

/*
string
add_light_descr(string district)
{
    string descr = "";
    switch(DAY_PART)
    {
        case "moondark":        // 1am - 3am (1)
            switch(district)
            {   // Protector Enclave
                case "pr":  descr = pr_time_descr(1);
            }
            return descr;
        case "night's end":     // 4am (2)
            switch(district)
            {
                case "pr": descr = pr_time_descr(2);
            }
            return descr;
        case "dawn":            // 5am (3)
            switch(district)
            {
                case "pr": descr = pr_time_descr(3);
            }
            return descr;
        case "early morning":   // 6am - 8am (4)
            switch(district)
            {
                case "pr": descr = pr_time_descr(4);
            }
            return descr;
        case "morning":         // 9am - 11am (5)
            switch(district)
            {
                case "pr": descr = pr_time_descr(5);
            }
            return descr;
        case "highsun":         // 12pm Noon (6)
            switch(district)
            {
                case "pr": descr = pr_time_descr(6);
            }
            return descr;
        case "afternoon":       // 1pm - 4pm (7)
            switch(district)
            {
                case "pr": descr = pr_time_descr(7);
            }
            return descr;


        case "evening":         // 5pm - 9pm (8)
            switch(district)
            {
                case "pr": descr = pr_time_descr(8);
            }
            return descr;
        case "night":           // 10pm - 11pm (9)
            switch(district)
            {
                case "pr": descr = pr_time_descr(9);
            }
            return descr;
        case "midnight":        // 12am Midnight(10)
            switch(district)
            {
                case "pr": descr = pr_time_descr(10);
            }
            return descr;

        case "day":             // Default (0)
            switch(district)
            {
                case "pr": descr = pr_time_descr(0);
            }
            return descr;
        default:                // default (0)
            switch(district)
            {
                case "pr": descr = pr_time_descr(0);
            }
            return descr;
    }
}
*/

/*
string pr_time_descr(int i)
{
    string descr = "";
    switch(i)
    {
        case 1:     // moondark, 1am - 3am
            descr = ONE_OF_LIST(({"All is quiet in the district.",
                "A drunk Neverwintan bumps into you then stumbles " +
                    "on their way.",
                "Dim lamp light spills out of a window onto the " +
                    "street.",
                "A night guard walks past, watching you suspiciously.",
                "Someone brushes past you and disappears into " +
                    "the shadows." }));
            return descr;
        case 2:     // night's end, 4am 
            descr = ONE_OF_LIST(( {"The moon sets, disappearing behind " +
                    "the horizon.",
                "The stars fade into the night sky.",
                "Mists rise up and begins to dance in the street.",
                "Clouds scuttle across the sky.",
                "A cold breeze blows down the street" ));
            return descr;
        case 3:     // dawn, 5am 
            descr = ONE_OF_LIST(( { "Streaks of sunlight shoot across the sky.",
                "Clouds glow in the dawn light",
                "Lights begin to twinkle on in the buildings.",
                "The dew on the ground melts away in the dawn light."}));
            return descr;
        case 4:     // early morning, 6am - 8am 
            descr = ONE_OF_LIST(( { "The city begins to stir as the " +
                    "citizens wake up.",
                "Early morning sunlight create pools of light on the " +
                    "road.",
                "Smells of fresh bread drift from nearby houses.",
                "Shadows evaporate in the early morning light."}));
            return descr;
        case 5:     // morning 9am - 11am
            descr = ONE_OF_LIST(( { "Neverwinter is awake and bustling.",
                "A Neverwintan pushes past you as they heads towards " +
                    "the White Dragon market.",
                "A street sweeeper waks past you as they clean the street.",
                "The sun casts shadows across the road and buildings.",
                "}));
            return descr;
        case 6:     // highsun, 12pm Noon 
            descr = ONE_OF_LIST(( { "xxx"}));
            return descr;
        case 7:     // afternoon, 1pm - 4pm 
            descr = ONE_OF_LIST(( { "xxx" } ));
            return descr;
        case 8:     // evening, 5pm - 9pm 
            descr = ONE_OF_LIST(( { "xxx"}));
            return descr;
        case 9:     // night, 10pm - 11pm 
            descr = ONE_OF_LIST(( { "The sound of revelry echos from " +
                "nearby buildings.",
            "Dark shadows fill the corners of the street.",
            "Stars sparkle above you.",
            "Light spills out onto the street from nearby buildings." }));
            return descr;
        case 10:    // midnight, 12am Midnight 
            descr = ONE_OF_LIST(( { "xxx"}));
            return descr;

        case 0: default:
            descr = "";
            return descr;
    }
}
*/