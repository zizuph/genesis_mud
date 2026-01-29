#include "valley.h"

create_valley() {
    set_short("The greenhouse");
    set_long("You are in the greenhouse. A multitude of plants grow here, "+
	     "and it is quite dark. To the north is an opening, and to the "+
	     "south the garden continues as far as you can see. The path "+
	     "south is small, but can still be used. ");
    NORTH("marvel");
    SOUTH("crossing");
}

		  
		    
