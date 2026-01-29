
/*
 *  Road running north of Gelan. 
 *  Fixed typo - Jaacar, May 2016
 */ 

#include <stdproperties.h>
#include "defs.h"

inherit (GELAN_ROOMS+"north_road_room"); 

void
create_room()
{
    set_short("Castle road"); 
    make_the_room("The ruins of an ancient castle lie off the road " +
                  "to your north, crumbled almost to rubble, eroded " +
                  "by the elements and overgrown with vegetation. " +
                  "A wooden signpost by the roadside painted with the " +
                  "word \"Firedrome\" points east.", "north"); 

    add_item(({"signpost", "sign", "post", "wooden post"}), 
             "The signpost, made of varnished maple, points east. " +
             "Written on it is the word \"Firedrome\".\n"); 
    add_cmd_item(({"sign", "signpost"}), "read", 
             "Written on it is the word \"Firedrome\".\n"); 
    add_item(({"walls", "towers", "ruins", "castle", 
               "ancient castle", "rubble"}), 
             "What was once seemingly a great structure is now mostly " +
             "collapsed. The bases of its walls and towers of " +
             "ancient grey stone are still discernible, albeit " +
             "eroded by wind and rain and overgrown with vegetation, " +
             "but most of the rest of the structure is just piles " +
             "of rubble.\n"); 

    add_item(({"vegetation"}), 
             "Creeping plants and weeds have taken up residence over " +
             "and around the ruins.\n"); 

    add_exit(GELAN_ROOMS+"north_road_s2", "south"); 
    add_exit(GELAN_ROOMS+"north_road_e0", "east"); 
}
