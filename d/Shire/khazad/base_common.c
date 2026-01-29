/*
 * This file file contains all the common items that players 
 * can examine in Khazad-dum such as arches, bridges, etc.. 
 * This way these routines aren't spread over several files 
 * and makes maintaining them much easier.
 * By Finwe, February 2003
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"
inherit AREA_ROOM;
//inherit "/d/Shire/std/room/room_tell";
inherit "/cmd/std/command_driver";
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>


/*
 * Each of these variables defines the respective
 * set_ routine within this file. To create a new 
 * routine, define it here.
 */

static string add_arch   = "",
              add_arches = "",
              add_walls = "",
              add_floor = "",
              add_ceiling = "",
              add_well = "",
              add_battles = "",
              add_smooth_walls = "",
              add_torches = "",
              add_west_gate_stairs = "",
              add_cobwebs = "",

              add_all_rooms ="";

/*
 * Messages for climb the stairs to and from the road and the boardwalk
 */

int climb_up_20()
{
    write ("You ascend the stairs, twenty at a time.\n");
    say(QCTNAME(TP) + " ascends the stairs, twenty at a time.\n");
}

int climb_down_20()
{
    write ("You descend the stairs, twenty at a time.\n");
    say(QCTNAME(TP) + " descends the stairs, twenty at a time.\n");
}

/******************************************************************************/
/* Item defs used in other rooms                                              */
/******************************************************************************/

/*
 * Function name : set_add_cobwebs
 * Arguments     : str: none
 * Description   : adds cobwebs
 */
void set_add_cobwebs(string str)
{
    add_item(({"cobwebs"}),
        "The cobwebs are thick and gray colored. They look rather old, " +
        "hanging from the ceiling, torch stands, and anything else in " +
        "the tunnels.\n");
}



/*
 * Function name : set_add_torches 
 * Arguments     : str: none
 * Description   : adds torch descrs on walls
 */
void set_add_torches()
{
    add_item(({"stands", "torch stands", "sconces", "torchstands"}),
        "The torch stands are circular and made of iron. They are " +
        "attached to both sides of the walls and designed to hold " +
        "large torches. Above the stands are black patches of soot.\n");
    add_item(({"soot", "patches of soot", "black patches of soot"}),
        "The soot is black and in large patches along the edge where " +
        "the ceiling meets the wall. It is the result of countless " +
        "burning torches that once lined the walls.\n");
    set_add_cobwebs("");
}




/*
 * Function name : set_add_all_rooms
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_all_rooms()
{
}

/*
 * Function name : set_add_arch
 * Arguments     : str: additional appended to end of arch descr
 * Description   : adds standard arch descriptions to rooms
 */

void set_add_arch(string str)
{

    add_item(({"arch", "arched opening", "large arch"}),
        "The arch is tall and carved from the rock. It's faced with " +
        "smooth stones with one crowning the keystone of the arch. "+str+"\n");
    add_item(({"keystone", "top of arch", "top of the arch",}),
        "The keystone is the central part of the arch. In this case, since " +
        "the stones face the arch, the keystone is purely decorative and " +
        "offers no support.\n");
    add_item(({"smooth stones", "facing stones"}),
        "The facing stones are smooth follow the edge of the arch, " +
        "forming an outline of the entrance.\n");
}

/*
 * Function name : set_add_arch
 * Arguments     : str: additional appended to multiple arch descr
 * Description   : adds standard descriptions for multiple arches
 */

void set_add_arches(string str)
{

    add_item(({"arch", "arched opening", "large arch", 
            "large arches", "arched openings", "arches"}),
        "The arches are tall and carved from the rock. They are faced with " +
        "smooth stones. A keystone is set into the top of each arch. "+str+"\n");
    add_item(({"keystone", "top of arch", "top of the arch",}),
        "The keystone is the central part of an arch. In this case, since " +
        "stones face the arches, the keystone is purely decorative and " +
        "offers no support.\n");
    add_item(({"smooth stones", "facing stones"}),
        "The facing stones are smooth, outlining each arch.\n");
}


/*
 * Function name : set_add_mine_walls
 * Arguments     : str: additional text added to start of descr
 * Description   : adds standard bridge descriptions to rooms
 */

void set_add_walls(string str)
{
    add_item(({"walls"}),
        "The walls are smooth to the touch, square shaped and dark " + 
        "looking. Torch stands are attached to the walls in regular " +
        "intervals. " + str + "\n");
    set_add_torches();    

}


/*
 * Function name : set_add_mine_floor
 * Arguments     : str: additional text added to start of descr
 * Description   : adds standard mining floor descrs
 */
void set_add_floor(string str)
{
    add_item(({"floor", "ground"}),
         "The ground is dark and carved from the mountain. It is smooth, " +
        "probably well worn from countless feet that have travelled " +
        "this way." + str + "\n");
}

/*
 * Function name : set_add_mine_ceiling
 * Arguments     : str: additional text added to start of descr
 * Description   : adds standard descr to rooms
 */
void set_add_ceiling(string str)
{
    add_item(({"up", "ceiling"}),
        "The ceiling is high above your head. It was carved from dark " +
        "rock and looks smooth to the touch. Along the edges, soot " +
        "is visible from torches burned here. " + str + "\n");
}

/*
 * Function name : set_add_well
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_well(string str)
{
    add_item(({"well"}),
        "The well is a circular hole in the ground. It was once used " +
        "for drawing water from a fountain below. Well Stones surround " +
        "it, preventing anyone from accidentally falling in\n");
    add_item(({"well stones"}),
        "The stones are smooth with some chips and cracks on them. They " +
        "are stacked on top of each other to about the height of your " +
        "waist and surround the well.\n");
    add_item("bucket",
        "There is no bucket by the well.\n");
}


/*
 * Function name : set_add_battles
 * Arguments     : str: none
 * Description   : adds standard items to all rooms.
 */
void set_add_battles(string str)
{
    add_item(({"corpses", "skeletons", "fallen warriors"}),
        "They are decomposed bodies of fallen warriors. Rusted armours " +
        "and weapons surround most of the fallen bodies. Some appear " +
        "to be the bodies of fallen dwarves, while others look like " +
        "orcs, trolls, and other enemies of the dwarves. "+ str + "\n");
    add_item(({"dead dwarf", "dwarf corpse", "dwarf corpses", "dead dwarves"}),
        "These are corpses of dwarves who died defending the mines. " +
        "Little remains of them except for broken bones. Some are " +
        "sitting up against walls, others are face down, and others are " +
        "piled together, scattered about the area. The corpses have " +
        "been hacked and butchered badly by enemies, and rusted armours " +
        "and weapons lay next to the corpses.\n");
    add_item(({"enemies", "dead enemies", "dead orcs", "dead trolls"}),
        "These corpses lie in piles, scattered about the area. Their " +
        "twisted corpes are mixed in with those of the dwarves. The "+
        "bodies look like they have been gnawed on. Little remains " +
        "except for broken bones.\n");
    add_item(({"rusted armours", "broken armours"}),
        "It is broken and rusted, lying about the corpses. Some of " +
        "it looks like it was high quality, and this was probably worn " +
        "by the dwarven warriors. the lesser quality items look like " +
        "it was once sued by trolls and orcs. Now all of it is broken " +
        "or rusted, and pretty useless.\n");
    add_item(({"rusted weapons", "broken weapons"}),
        "They are broken and rusted, buried beneath the corpses or " +
        "lying. Some look like they were once high quality, and " +
        "these were probably used by the dwarves. The others look " +
        "like they were used by the trolls and orcs.\n");

}

/*
 * Function name : set_add_west_gate_stairs
 * Arguments     : str: none
 * Description   : adds 
 */
void set_add_west_gate_stairs(string str)
{
    add_item(({"stairs"}),
        "They are carved from the mountain and are broad and shallow, " +
        "unbroken despite their age. The stairs are smooth and run up " +
        "into the mountain and down to the West Gate of Moria. " +str + "\n");  
}


