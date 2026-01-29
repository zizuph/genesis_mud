#include "valley.h"

create_valley() {
    set_short("The Slide");
    set_long("This is the Slide, a slippery downgoing passage with steep "+
	     "walls. Damp & smooth stones make it possible to slide down "+
	     "a windy passage, but I'll doubt if you'll be able to climb up "+
	     "again. There is an opening to the south. ");
    SOUTH("junction");
    DOWN("trolls_treasure");
}

		  
		    
