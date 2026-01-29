/*
 * Sample base file for outdoor rooms
 * By Finwe, September 2003
 *
 * Modification log:
 * Cleaned up file, Finwe, March 2005
 */

/* files to include */
#include "/d/Shire/sys/defs.h"  // domain definitions. Always include
#include "defs.h" // definitions for area. include in area files
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

/* files to inherit for outdoor rooms*/
inherit AREA_ROOM;  // defines all room functions
inherit HERB_SEARCH; // sets up herb searching in room
inherit "/d/Shire/std/room/room_tell"; // sets up room messages
inherit "/cmd/std/command_driver"; 

/* function to create actual room */
void create_road_room() {}

/* use create_area_room() instead of create_room() to use 
 * Shire room definitions. */
public void
create_area_room()
{
 /* these variables are defined in /d/Shire/lib/area_room.c
  * and inherited as AREA_ROOM. Change them to change the 
  * short and long description of room. It includes time in the 
  * long description.
  * 
  * These current settings will show this short description:
  *   A grassy field west of the Brandywine river in Eriador.
  *
  * The long description will be this, with time changing as needed:
  *  A grassy field west of the Brandywine river in Eriador. The sun 
  *  is almost at its peak on its way across the sky. It is noon in 
  *  the Brandywine river. 
  */

    areadesc = "field"; // eg "green, grassy field", "dense thicket"
    area = "west of";  // eg "northern" 
    areaname = "the Brandywine river"; // eg "the bridge", "the field", "Bree"
    land = "Eriador"; // eg "Shire", "Trollshaws"
    areatype = 1; // what type of area it is. see below.
    /*  0 = no type desc, 1 = Grass,    2 = Bushes,
     *  3 = Trees,        4 = Farmland, 5 = Rocky,
     *  6 = Snow,         7 = Forest,   8 = Road,
     *  9 = Barren,      10 = Village, 11 = Path,
     * 12 = Ruins,       13 = Marsh,   14 = Hills
     * 15 = Shore,       16 = Beach,   17 = Woods
     * Definitions found in ~Shire/sys/terrain.h
     * areas with area type have default items set except for 0
     */

    extraline = "Additional room descriptions go here and are added " +
        "to the end of the long description. Notice no \\n is needed. " +
        "This will be replaced when used in other rooms.";
    add_item(({"road", "ground"}),
        "The road is made of hard packed dirt. Wagon ruts run down " +
        "the middle of the road.\n");

/* turns on room tells. ROOM_TELL_TIME can be set in a def.h file 
 * or set manually.*/
    set_room_tell_time(ROOM_TELL_TIME); 
/* individual room tells. You may put as many here as necessary. */
    add_room_tell("A few birds fly overhead.");
    add_room_tell("Some clouds pass overhead.");

/* defines what kind of herbs can be found in this area. */
    add_std_herbs("trees");

/* use this instead of create_room() to make */
    create_road_room();
    
 
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
 
}    

void
init()
{   
/*
 * Used to initilaize some functions. Not needed, but nice to have in
 * each room.
 */
    ::init();
}
