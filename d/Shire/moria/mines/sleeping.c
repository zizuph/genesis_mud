#include "defs.h"

object cr;

CONSTRUCT_ROOM {
    set_short("Princess' sleeping room.");
    set_long("You're in the princess' sleeping room. A huge four-poster "+
	     "fills half the room. Silk draperies hang down from the bed-"+
	     "ceilings, which are made of a deep-red silk velvet. The bed "+
	     "looks soft and pleasant, and a tempting perfume puts you in a "+
	     "indescribable mood, completely different from the stinking "+
	     "dragon. A nice, but heavy wooden wardrobe covers the entire "+
	     "northern wall.\n");

    add_item(({"four-poster","draperies","bed","parfume"}),
	     "Oh.. what a bed!!");
    add_item(({"wardrobe","wall"}),
	    "You'll have a better look if you walk closer.");
    NORTH("wardrobe");
    SOUTH("losttrck");
    reset();
}

RESET_ROOM {
/*    if (!cr || !present(cr)) {
	cr =  clone_object(MORIA_ARM + "crown");
	cr -> move(this_object());
    } 
    */}
    
		    
