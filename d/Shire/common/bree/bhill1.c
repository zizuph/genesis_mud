inherit "/d/Shire/common/lib/rom";

#include "defs.h"

create_rom()
{
    set_short("Slope up to Bree-hill.");
    set_long("You are walking on a road going up the 'hill'. Just "
    	     +"north of here, further up the Bree-hill you can "
    	     +"see some hobbits working in a garden. There are "
    	     +"quite a lot of houses on the Bree-hill and most of them "
    	     +"have nice gardens surrounding the houses. Bree is mostly "
    	     +"inhabited by humans but there are hobbits living here "
    	     +"too. The road goes northeast further up "
    	     +"the hill and southwest down towards the center of Bree.\n");
    	     
     add_item("road","The road is paved with solid rock. This is truly an dwarven "
     		    +"arfifact. It looks well used.\n");
     		   
     add_item("hobbits","The hobbits seems to be working with a hedge. Cutting it and "
     		       +"tending it like only hobbits can do it.\n");
     		       
     add_item("house", "The houses in Bree looks just like every other house, with "
     		      +"a front door and windows on it.\n");
     		      
     add_item("view", "The view from here is excellent. North there is only waste lands "
     		     +"stretching out as far the eye can see. South more woods can be "
     		     +"seen.\n");
     		     
     NORTHEAST("bhill1b");
     SOUTHWEST("brroad1");
}
