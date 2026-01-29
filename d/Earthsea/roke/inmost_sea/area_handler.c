 /* Jakob 1995-02-04
* area-handler for
* the Inmost Sea
*
* Napture did the
* grammar check
*/

inherit "/lib/area_handler";

#include "defs.h"
#include <stdproperties.h>

void create_area()
{
   set_map(INMOST_SEA + "inmostsea");
   if (file_size(INMOST_SEA + "inmostsea") <= 0)
     {
       write("BAD FILE " + file_size(INMOST_SEA + "inmostsea") + ": " + 
	     INMOST_SEA + "inmostsea" + ".\n");
     }
   add_desc("s", ({ ({ ROOM_IN_WATER, 0, 1, 4 }),
            ({ "open sea",
                  "The boat creaks gently as you continue your " +
                  "journey. The wind hisses, the waves lisp. On " +
                  "the almost empty sky above you see the bright "+
                  "flight of a lonesome hawk. " +
                  "The vastness and serenety around you dwarfs " +
                  "you. You feel alone and small.",
                  
                  "The ship rides low with her burden, yet dances " +
                  "a little on the lapping share-waves. Still the "+
                  "wind grows stronger, tearing the edges of the great " +
                  "waves into flying tatters of foam.",
                  
                  "The weather looks harsh. You have to bellow "+
                  "in order to make yourself heard through the wind "+
                  "and rain. You fear that only wizardry "+
                  " can bring you "+
                  "through this sea.",
                  
                  "The boat moves forward irregularly and slowly, "+
                  "following the fitful humour of the wind. Behind "+
                  "you the sun is rising and the wind howling, " +
                  "bearing the boat away from land, away from the "+
                  "world, out onto the open sea.",
                  
                  "You sail a rough chopping sea above which " +
                  "clouds droop and drift in vast mournful veils. "+
                  "Past the dim glimpse of land you have sailed. "+
                  "Now you are alone, vulnerable. Only the sound "+
                  "of waves lightly slapping the boat can be heard. "+
                  "Nothing moves but the ever-moving water and the "+
                  "drifting clouds. You feel chilled and weary." }),
            
            ({"boat", "On either side of its prow an eye is painted. "+
                  "It feels like the boat is staring at you. ",
                  
                  "waves", "The waves lap feebly around you. ",
                  
                  ({"sea", "ocean"}), "Out of the sea there rise storms and monsters, "+
                  "but no evil powers: evil is of earth." }),
            
         ({ }) }));
   
 add_desc("n", ({ ({ ROOM_IN_WATER, 0, 1, 2 }),
            ({ "Near land.",
                  "Land ahoy! Though you can't sea land it must "+
                  "be not far away. The waves are manifestly lower "+
                  "and the sea looks more shallow. ",
                  
                  "The boat rocks forward in what seems to be "+
                  "a less ferocious part of the ocean, leaving the "+
                  "blazing waves behind. Perhaps "+
                  "you are close to land?",
                  
                  "The boat hangs swaying on the water, the sail "+
                  "slack on the spar. The sun glares through a veil "+
                  "of haze, shaking and throbbing your weary head. "+
                  "Land can't be far away." }),
            
            ({"boat", "On either side of its prow an eye is painted. "+
                  "It feels like the boat is staring at you. ",
                  
                  "waves", "The waves lap feebly around you. ",
                  
                  "sea", "Out of the sea there rises storms and monsters, "+
                  "but no evil powers: evil is of earth.",
                  
                  "land", "In the distance you can make out a " +
                  "shallow crescent bay. "}),
            
            ({ }) }));
   
 add_desc("r", ({ ({ ROOM_IN_WATER, 0, 1, 2 }),
            ({ "shallow water",
                  "Hours has gone since you first set sail from "+
                  "the safe harbour. The sun beats down on you, "+
                  "the greyish heat wrapping around you. You sit "+
                  "unmoving. Suddenly there is a loud crash. A "+
                  "shiver goes through the boat. It looks l "+
                  "you have bumped into something...as well as that "+
                  "your luck has run out.",
                  
                  "A breath of cool air passes across your forehead. "+
                  "You have drifted far from the Roke island. A "+
                  "mist hides the sea, but you suspect it is "+
                  "shallow water hear, better beware." }),
            
            ({"boat", "On either side of its prow an eye is painted. "+
                  "It feels like the boat is staring at you. ",
                  
                  "waves", "The waves lap feebly around you. ",
                  
                  "sea", "Out of the sea there rise storms and monsters, "+
                  "but no evil powers: evil is of earth." }),
            
            ({ }) }));
   
   
   add_bound("R", THWIL + "R");
   add_bound("I", ISSEL + "I");
   add_bound("K", INMOST_SEA + "kamery/quay");
   add_bound("S", INMOST_SEA + "S");
   add_bound("H", INMOST_SEA + "hosk/quay");
}
