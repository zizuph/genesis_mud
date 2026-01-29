/*
 * er_shaws.c
 *
 * This file contains all functions and variables which are
 * common to all rooms in the Trollshaw forest and also being
 * the Great Eastroad through the forest.
 *
 */


inherit "/d/Shire/common/trollsh/trollsh";

#include "defs.h"

/*
 * We will need all the function in this file, so we inherit it.
 */

/*
 * create_rom is the entry point at creation of a Trollshaw room.
 */

create_trollsh()
{
    add_item(({"road","sand"}), "The road is fairly wide and " +
        "covered with gravel.\n");

    add_item(({"forest", "trollshaws", "trollshaw", 
            "trollshaw forest", "shaws", "woods", "area", 
            "tree", "trees", "ground", "forest floor"}),
        "The forest is very dark, swallowing all light coming " +
        "into it.\n");

    add_item(({"spruces","spruce"}),
        "There are small spruces scattered around here and are " +
        "medium to tall in height.\n");

    add_item(({"pines","pine"}),"There are several pines here and there.\n");

    set_time_desc(
    	"day",
            "It is day now, and the sun shines from above, " +
            "lighting the scary forest and the Great Eastroad " +
            "running through it.\n",
    	"night",
	        "It is dark and scary as the night chokes out all light.\n",
    	"moon",
    	    "The moon shines coldly in blue on the scary woods " +
            "surrounding you.\n",
    	"early night",
	        "Still not long since the sun set, it is dark and " +
            "scary walking this place where the rumour tells " +
    	    "trolls are inhabitating.\n",
    	"early morning",
	        "The light gradually gets brighter as the sun " +
            "rises the East above the Misty Mountains.\n");
        TO->create_er_shaws();
}

reset_rom()
{
    TO->reset_er_shaws();
}

query_extra()
{
    return time_desc();
}
