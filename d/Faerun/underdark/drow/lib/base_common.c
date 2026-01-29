/*
 * Common file Menzobarrazan Proper
 * By Finwe, April 2006
 * 
 * Modification log:
 *
 */


inherit "/d/Faerun/underdark/drow/lib/base_menzo";
inherit "/cmd/std/command_driver";
 
#include <ss_types.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"


/*
 * Function name : add_add_stalags
 * Description   : adds descr of stalagmites and stalactites
 */
void add_add_stalags()
{
    add_item(({"stalagmite", "stalagmites"}),
        "These are conical shaped deposits that have formed on the ground " +
        "from water dripping down off the ceiling above. They have been " +
        "carved into ornate shapes and columns by the Drow. The largest " +
        "have been carved into towers, others are linked together and " +
        "form fences around compounds in the city.\n");
    add_item(({"stalacite", "stalactites"}),
        "These are massive icicle shaped deposits that hang from the " +
        "ceiling above, They are intricately carved by the Drow into " +
        "spectacular shapes. The largest ones are linked into fences that " +
        "surround the greatest houses in the city.\n");
}

/*
 * Function name : add_stone_block
 * Description   : adds descr of stone blocks in the city
 */
void add_stone_block()
{
    add_item(({"stone block", "stone blocks", "blocks", "block"}),
        "They are grey and square shaped. They are used in buildings " +
        "throughout the city.\n");
}

/*
 * Function name : add_faerie_fire
 * Description   : adds descr of faerie fire 
 */
void add_faerie_fire()
{
    add_item(({"fire", "faerie fire"}),
        "They are magical lights that highlight columns, outline sculptures and decorate buildings. The lights vary in colors from purple and red to bright yellows and subtle blues and all shades in between.\n");
}

/*
 * Function name : add_statues
 * Description   : adds descr of statues scattered around the city
 */
void add_statues()
{
    add_item(({"statues"}),
        "They are carved from stalagmites, stalactites, and stones by Drow. many of the statues are gargoyles, important heros and citizens, and dieties of the Drow.\n");
    add_item(({"gargoyles"}),
        "These are hideous creatures carved from stone. Many of them stand as guardians before buildings. Others are set on top of buildings, like silent sentinels. They are all grotesque looking and many of them are of unfamiliar creatures.\n");
    add_item(({"deities"}),
        "They are statues of those gods and godesses the Drow worship. The statues look eerily lifelike and appear to watch you.\n");
}

/*
 * Function name : add_mantle
 * Description   : adds descr of 
 */
void add_mantle()
{
    add_item(({"mantle"}),
        "The mantle marks the edge of Menzobarranzan and rises above the city. It is the wall that surounds the cavern that the city sits in. The wall is patrolled by Drow who defend it against any enemies.\n");
}


/*
 * Function name : add_houses
 * Description   : adds descr of houses
 */
void add_houses()
{
    add_item(({"less noble houses", "less noble"}),
        "These are grander houses of the Drow. They are less ornate than " +
        "the villas of the noble houses and are set away from the road. " +
        "They are square shaped and surrounded by walls. The nicer ones " +
        "are marked with carved stalagmites.\n");
    add_item(({"noble houses", "villas"}),
        "These are grand houses of the Drow. They are set aside from " +
        "the rest of the other houses. The houses are ostentatious and " +
        "grand, and decorated with gargoyles and faerie fire. They belong " +
        "to the ruling class of the city or wealthy merchants\n");
    add_item(({"houses"}),
        "There are various houses visible. There are common, less noble, " +
        "and noble houses. They are scattered throughout the area. The " +
        "common houses line the road. The nicer, grander villas are walled " +
        "and set away in the distance.\n");
    add_item(({"common houses"}),
        "These are small houses tucked away. They are circular and " +
        "surrounded by walls. \n");
}



/*
 * Function name : add_all_rooms
 * Description   : adds descr of items and functions in all rooms
 *                 of outdoors Menzo
 */
void add_all_rooms()
{
    add_add_stalags();
    add_stone_block();
    add_faerie_fire();
    add_statues();
}
