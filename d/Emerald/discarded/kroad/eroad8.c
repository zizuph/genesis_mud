/*
 * eroad8.c
 * Kahlen Road
 * by Alaron August 31, 1996
 * Noiseroom by Jaypeg - 13th Feb 97
 */

#include "defs.h"

inherit "/d/Emerald/kroad/vamp/lib/out_vamp_tellroom";


void
create_ov_road()
{
   set_short("Coastal dirt road");
   set_long("   A cool, ocean breeze blows up against the cliff face "+
	    "to the north, spreading a salty mist over the road. The road's "+
	    "southern edge is bordered by low bushes and vegetation, "+
	    "eventually giving way to an enormous, sprawling forest. The "+
	    "cliffs to the north fall off abruptly and descend at an "+
	    "almost vertical drop into the channel far below, where "+
	    "sounds of crashing waves echo. Small puddles of water and "+
	    "patches of mud fill the landscape on the north side of "+
	    "the road.\n\n");
      
   OUTSIDE;
   LIGHT(1);
      
   add_item( ({"mud", "water", "puddles", "patches of mud"}),
	    "The mud and puddles of water dot the landscape to the "+
	    "north between the road and the cliffs. The puddles most "+
	    "likely formed from collected water from the ocean spray.\n");

   add_item( ({"cliffs", "north", "cliff face"}),
	    "The cliffs to the north tower over the ocean channel below "+
	    "in stark contrast with the deep blue color of the water "+
	    "churning at their base. A large stone bridge can be seen "+
	    "spanning the gap between cliff faces to the northwest. "+
	    "Puddles of water and patches of mud fill the dirt between "+
	    "the road and the cliffs.\n");

         
   add_item( ({"bushes", "low bushes", "foliage", "green foliage",
	       "vegetation"}),
	    "The low bushes and vegetation border the road, seeming to "+
	    "stretch out onto the dirt toward the cliffs in search of "+
	    "the collected moisture. Various forms of plant life and "+
	    "flowers look familiar within the green mass. Further back, "+
	    "the greenery seems to rise up out of the ground and melt "+
	    "into the edge of an enormous forest.\n");
            
   add_item( ({"flowers", "plant life"}),
	    "Several kinds of flowers and plant life within the bushes "+
	    "seem vaguely familiar.\n");
               
               
   add_exit(PATH + "eroad7", "west", 0, 1);
    add_exit("coast1", "south", 0, 1);
}


