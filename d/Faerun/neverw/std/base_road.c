/*
 * Base Room for Neverwinter roads
 * -- Finwe, February 2017
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit FAERUN_OUTDOOR_BASE;


void
create_road()
{
}


// Specifics for Protector Enclave District

string pr_rd01()
{
    return "The road winds past houses and various buildings. It is paved with bricks and looks well used. The houses are neat looking and the buildings solid looking. ";
}

string pr_rd02()
{
    return "Stout houses and solid looking buildings line the road. The houses and builds look solid and well maintained. They crowd the road, blocking your view. The road looks neat and well traveled. ";
}

string pr_rd03()
{
    return "The paved road passes under trees. It winds past houses and buildings. The road looks well maintained and the houses and buildings neat looking. ";
}

string pr_rd04()
{
    return "The houses and other buildings crowd the road. They are one and two stories tall, and some even taller. The road is paved and disappears in the distance. ";
}

string pr_rd05()
{
    return "DESCR ";
}

string pr_rd06()
{
    return "DESCR ";
}

void add_castle_never()
{
    add_item(({"ruins", "castle ruins", "castle never", "castle grounds", 
            "castle"}),
        "The castle is in ruins and hasn't been rebuilt. At one time " +
        "it looks like it was a large structure, but now it has been " +
        "reduced to toppled towers and collapsed walls and ceilings. " +
        "Stone rubble litter the grounds of this once grand castle.\n");
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
        "Holes of all sizes have been punched into the castle walls, " +
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

    add_room_tell("A creaking sound reverberates from somewhere in the " +
        "castle ruins.");
}




/*
 * Function name : add_XXX
 * Description   : adds descr of 
 */
void add_plain_road()
{
    add_item(({"road", "plain road"}),
        "The \n");
    add_item(({"XXX"}),
        "\n");
    add_item(({"XXX"}),
        "\n");
}

/*
 * Function name : add_XXX
 * Description   : adds descr of 
 */
void add_XX1()
{
    add_item(({"XXX"}),
        "\n");
    add_item(({"XXX"}),
        "\n");
    add_item(({"XXX"}),
        "\n");
}

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




// Creates the road room
void
create_faerun_room()
{
    setuid(); 
    seteuid(getuid());

//    string light_desc = add_light_descr("pr");
    
    ::create_faerun_room();
    add_prop(ROOM_S_MAP_FILE,"XXX.txt");

    set_short("A grassy meadow");

    extraline = "EXTRA_DESCRS_GO_HERE_OR_THIS_CAN_BE_LEFT_BLANK";

    set_room_tell_time(240);
       

    create_road();
}