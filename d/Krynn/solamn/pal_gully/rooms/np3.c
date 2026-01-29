/* 
 * NP1, Crossroad leading to the Aghar or Dewar.
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_ROAD_BASE;

/*
 * Function name: reset_pal_road_room
 * Description  : Resets the room
 */
void
reset_pal_road_room()
{
	
}

/*
 * Function name: create_pal_road_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_road_room()
{
    set_short("Desolate Road");
    set_long("This road is certainly off the beaten path. Surrounding "
    +"either side of the road are tall trees which are set upon the "
	+"sheer stone walls which sit ominously on either side of the path."
    +"There are sounds of skirmishes all around you "
    +"as well as scuff marks, blood stains, and skid marks "
    +"along the ground. To the west you see a crossroads "
    +"and what appears to be a cavern and a mine. To "
    +"the east lies more of this same road.\n");
	
    
    add_item(({"mine", "mines", "abandoned mine","dump"}), "The mine "
    +"looks a bit clearer now. You can see the definition "
     +"of an unkept and abandoned mine.\n");
    add_item(({"cave", "caverns", "well-kept caverns", 
    "well-kept caves", "old cavern", "cavern", "well-lit cavern",
	"well-lit caverns"}), "The cavern looks a bit "
    +"clearer now. You can see some of the definition and see it "
    +"looks like a well-kept cavern system.\n");
	add_item(({"tree", "trees", "pine", "pines", "spruce", "spruces",
	"pine trees", "spruce trees", "spruce tree", "pine tree", "huge tree",
	"huge trees"}), "Tall pine and spruce trees with there evergreen needle "
	+"rest atop the sheer stone walls which line either side of this "
	+"road\n");
	add_item(({"wall", "sheer walls", "stone walls", "stone wall", 
	"sheer wall", "sheer stone wall", "sheer stone walls","stone"}),"Tall "
	+"stone walls rising about 20 feet up line either side of the road. "
	+"Sitting atop the walls are trees.\n");
    
           
    add_exit(RDIR + "np2","west",0);
    add_exit(RDIR + "np4","east",0);
    reset_pal_road_room();
    
}