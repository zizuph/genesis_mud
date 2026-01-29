/*
 * CRY6.c
 * Crypt outside/under the Ruins of Kamesh
 * Altar Room
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("A cold, dark crypt");
    set_long("   You are standing on a stone platform raised slightly "+
	     "above the rest of the crypt. Arranged in neat, rigid "+
	     "rows spreading out to the south of you are dozens of "+
	     "coffins and free-standing sarcophagi. As you pan from "+
	     "left to right across the seemingly endless shadowed "+
	     "outlines of coffins, a bonechilling shiver travels "+
	     "down your spine. Turning your attention to the platform "+
	     "on which you are standing, you look over an enormous, "+
	     "pitch-black marble altar. From this distance, you see "+
	     "hundreds of little markings on the altar, but can't "+
	     "tell what they are. Behind the altar you see a carefully "+
	     "arranged array of axes all hanging from rusted iron "+
	     "chains.\n\n");

    add_prop(ROOM_S_DARK_LONG, "   The room is pitch-black. Off in the "+
	     "distance somewhere you can make out the faint glimmer "+
	     "of a candle.\n\n");

    add_prop(ROOM_S_DARK_MSG,"There is not enough light here to");

    INSIDE;
    LIGHT(-4);

    add_item( ({"coffins", "sarcophagi", "sarcophagus", "coffin"}),
	     "The coffins and sarcophagi are arranged neatly in ordered "+
	     "rows. You can't quite get an accurate count of them because "+
	     "of the darkness. Trying not to be superstitious, you can't "+
	     "help but feel uneasy around all of this death. The cold breeze "+
	     "blowing through the crypt and flickering, dim lamplight do "+
	     "not ease your mind any, either.\n");

    add_item( ({"platform", "raised platform", "stone platform",
		"down", "ground", "floor"}),
	     "The platform beneath you is made of dark stone. The stone "+
	     "is riddled with dark stains of various shapes and sizes. In "+
	     "the darkness you can't quite tell what the stains are. From "+
	     "the slight glistening of the stains, you'd guess they "+
	     "could be blood.\n");

    add_item( ({"altar", "marble altar", "black altar", "pitch-black altar"}),
	     "The marble altar before you is incredibly large. It is "+
	     "made of the blackest marble you have ever seen in your life. "+
	     "You consider reaching out to touch the marble, to test "+
	     "its smoothness, but something about its darkness seems "+
	     "unnatural .... almost as if the altar is absorbing the "+
	     "light around it ... making it darker than it should be "+
	     "in here. There are hundreds of little markings littering "+
	     "the surface of the altar. Behind the altar you notice "+
	     "several axes hanging from rusted iron chains.\n");

    add_item( ({"axes", "chains", "iron chains", "rusted chains",
		"harnesses"}),
	     "The axes hanging from the ceiling are all arranged in "+
	     "ascending size order from little hatches to enormous "+
	     "double-bladed war axes. Each hangs from a set of two "+
	     "chains in a specially designed harness. You wonder what "+
	     "all of those axes could be hanging from the ceiling for.\n");

    add_item("markings",
	     "The markings in the surface of the altar, upon closer "+
	     "inspection, turn out to be slash marks. You guess that "+
	     "they were probably made from heavy, wide-bladed weapons. "+
	     "Possibly axes.\n");
		

    add_exit(MONKRUIN_DIR + "cry3", "west");
}

    
