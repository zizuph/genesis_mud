/*
 * This file file contains all the common items that players 
 * can examine in the area, like different rivers, mountains, etc.
 * This way these routines aren't  spread over several files 
 * and makes maintaining these routines much easier.
 *
 * To use any of these routines, this file must be inherited 
 * by the base file, then simply call the routine(s) within 
 * the room definition.
 *
 * Example:

    void
    create_shire_room()
    {

        set_add_houses("They are two storied and made of brick " +
            "and appear well kept. ");
    }
    
 * To pass nothing to the routine, simply pass "" in place of text.
 * By Finwe, March 2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/lib/commands.c";

/*
 * Each of these variables defines the respective
 * set_ routine within this file. To create a new 
 * routine, define it here.
 */

static string add_all_rooms = "",
              add_river_far = "",
              add_river_near = "",
              add_river_close = "",
              add_misty_far = "", 
              add_misty_near = "", 
              add_misty_close ="",
              add_mirk_close = "",
              add_mirk_near = "",
              add_mirk_far = "",
              
              add_wildlife = "";


string
daylight_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "Moonlight";
        case LATE_NIGHT :
            return "Starlight";
        case EARLY_MORNING :
            return "Soft morning light";
        case MORNING:
            return "Gentle sunlight";
        case NOON:
            return "Noon sunlight";
        case AFTERNOON:
            return "Blazing afternoon sunlight";
        case EVENING:
            return "Evening light";
    }
}

 
string
day_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "early night";
        case LATE_NIGHT :
            return "late night";
        case EARLY_MORNING :
            return "early morning";
        case MORNING:
            return "morning";
        case NOON:
            return "noon";
        case AFTERNOON:
            return "afternoon";
        case EVENING:
            return "evening";
    }
}
 
string
light_type()
{
   switch(qhour())
    {
        case EARLY_NIGHT :
            return "moonlight";
        case LATE_NIGHT :
            return "starlight";
        case EARLY_MORNING :
            return "early morning light";
        case MORNING:
            return "gentle, morning sunlight";
        case NOON:
            return "bright sunlight";
        case AFTERNOON:
            return "blazing sunlight";
        case EVENING:
            return "soft, gentle nightlight";
    }
}

string sun_moon()
{
    switch(qhour())
    {
       case EARLY_NIGHT :
            return "moon";
        case LATE_NIGHT :
            return "stars";
        case EARLY_MORNING :
            return "rising sun";
        case MORNING:
            return "early sun";
        case NOON:
            return "sun";
        case AFTERNOON:
            return "sun";
        case EVENING:
            return "setting sun";
    }
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
 * Function name : set_add_river_far
 * Arguments     : str: none
 * Description   : adds standard descr for the Anduin as seen
 *                 far away
 */

void set_add_river_far()
{
    add_item(({"river", "anduin", "the great river", "great river"}),
    "The river, Anduin, appears as a thin ribbon in the distance.\n");
}

/*
 * Function name : set_add_river_near
 * Arguments     : str: none
 * Description   : adds standard descr for the Anduin as seen
 *                 nearby
 */

void set_add_river_near()
{
    add_item(({"river", "anduin", "the great river", "great river"}),
        "The Anduin River flows north and south. The sound of " +
        "it in its bed can be heard nearby.\n");
}


/*
 * Function name : set_add_river_near
 * Arguments     : str: none
 * Description   : adds standard descr for the Anduin as seen
 *                 upclose and personal
 */

void set_add_river_close()
{
    add_item(({"river", "anduin", "the great river", "great river", "water"}),
        "This is the mighty Anduin. It is the greatest river " +
        "in Middle-earth as it flows south from its many " +
        "tributaries in the northern mountains. The water looks " +
        "surprising calm here as it flows past reeds, grasses, " +
        "and other water plants. @@daylight_desc@@ sparkles " +
        "on the river's surface.\n");
    add_item( "water plants",
        "Tall grasses, water flowers, reeds, rushes, and " +
        "other tall plants grow at the edge of the Anduin. " +
        "They probably offer some refuge for small animals.\n");
    add_item(({"water flowers"}),
        "They grow at the edge of the river. They are yellow, " +
        "blue, purple and other colors.\n");
    add_item(({"reeds", "rushes"}),
        "They grow at the river's edge and are healthy looking " +
        "with arrow shaped ends. Some are bent over, floating " +
        "in the river.\n");
}

/*
 * Function name : set_add_misty_far
 * Arguments     : str: none
 * Description   : adds standard descr for the misty mountains
 *                 as seen far away
 */

void set_add_misty_far()
{
    add_item(({"mountains", "misty mountains"}),
        "The Misty Mountains rise to the west. Their jagged " +
        "tops are covered with  clouds and look imposing, even " +
        "from this distance.\n");
}


/*
 * Function name : set_add_misty_near
 * Arguments     : str: none
 * Description   : adds standard descr for the misty mountains
 *                 as seen near
 */

void set_add_misty_near()
{
    add_item(({"mountains", "misty mountains"}),
        "The Misty Mountains tower above you to your west. They " +
        "are a great chain of mountains that run north and " +
        "south through Middle-earth. Their peaks are shrouded " +
        "with clouds and are imposing. Rumours speak of goblins " +
        "and orcs inhabiting the Misty mountains.\n");
}


/*
 * Function name : set_add_misty_close
 * Arguments     : str: none
 * Description   : adds standard descr for the misty mountains
 *                 as seen near
 */

void set_add_misty_close()
{
    add_item(({"mountains", "misty mountains"}),
        "The Misty Mountains dominate your view as you stand " +
        "at their feet. Large boulders and rocks have tumbled " +
        "down from the mountain and lay strewn about.\n");
}

/*
 * Function name : set_add_mirk_close
 * Arguments     : str: none
 * Description   : adds descr of mirkwood forest close up
 */
void set_add_mirk_close()
{
    add_item(({"forest", "mirkwood", "mirkwood forest", "greenwood", 
            "greenwood forest", "greenwood the great", "wood", 
            "the great wood", "taur e-ndaedelos"}),
        "Large trees dominate the forest to the east, known as Mirkwood. " +
        "It is the largest forest in Middle-earth stretching from " +
        "the north to the south. Mirkwood is dark and foreboding, " +
        "and only the bravest enter it.\n");
    add_item(({"large trees", "trees"}),
       "The trees are dark and ancient looking. Their trunks are dark " +
       "green to black colored and are twisted. They grow close together, " +
       "preventing travel into the forest.\n");
    add_item(({"branches", "tree branches"}),
       "The branches are very thick and twisted. They are dark green " +
       "to black colored and are covered with countless black leaves.\n");
    add_item(({"leaves", "dark leaves", "dark leaf", "leaf"}),
        "The dark leaves hang silently from the branches. They " +
        "are large and teardrop shaped.\n");
}

/*
 * Function name : set_add_mirk_near
 * Arguments     : str: none
 * Description   : adds descr of mirkwood forest nearby
 */
void set_add_mirk_near()
{
    add_item(({"forest", "mirkwood", "mirkwood forest", "greenwood", 
            "greenwood forest", "greenwood the great", "wood", 
            "the great wood", "taur e-ndaedelos"}),
        "The forest spreads north and south. It is large, as it spreads " +
        "before you. Large trees are visible which are crowned with " +
        "dark leaves.\n");
    add_item(({"large trees", "trees"}),
       "The trees of the forest are dark and ancient looking. They " +
       "grow close together, creating a black wall in the distance.\n");
    add_item(({"branches", "tree branches"}),
       "The branches of the trees of the forest are very thick and " +
       "twisted. Dark leaves hang from the branches.\n");
    add_item(({"leaves", "dark leaves", "dark leaf", "leaf"}),
        "The dark leaves are large and teardrop shaped.\n");
}

/*
 * Function name : set_add_mirk_far
 * Arguments     : str: none
 * Description   : adds descr of mirkwood forest far away
 */
void set_add_mirk_far()
{
    add_item(({"forest", "mirkwood", "mirkwood forest", "greenwood", 
            "greenwood forest", "greenwood the great", "wood", 
            "the great wood", "taur e-ndaedelos"}),
        "It is a large carpet of dark trees and spread out to the " +
        "east. The forest stretches north and sout, blocking your view " +
        "beyond it.\n");
    add_item(({"large trees", "trees"}),
       "The trees are of the forest are difficult to look at, but they look ancient and twisted, and all look black colored.\n");
    add_item(({"branches", "tree branches"}),
       "The branches of the forest are difficult to see, but the " +
       "largest ones look dark and twisted.\n");
    add_item(({"leaves", "dark leaves", "dark leaf", "leaf"}),
        "The leaves are difficult to see, but they all look black " +
        "and evil looking.\n");
}
/*
 * Function name : set_add_wildlife
 * Arguments     : str: none
 * Description   : adds proof of wildlife in the Vale
 */
void set_add_wildlife()
{
    add_item(({"wildlife", "animals"}),
        "Wildlife is evident in the vale by animal tracks that dot the " +
        "land. However, the animals remain hidden from your view, " +
        "probably watching you.\n");
    add_item(({"tracks", "animal tracks"}),
        "They are prints left behind by animals that have travelled " +
        "this way. Some are fresh while others are faint and older.\n");
}


