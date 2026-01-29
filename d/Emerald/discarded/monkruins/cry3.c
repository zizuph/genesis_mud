/*
 * CRY3.c
 * Crypt outside/under the Ruins of Kamesh
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("A cold, dark crypt");
    set_long("   You find yourself in the middle of a dark, cold "+
	     "crypt. The soft sound of a cool breeze blowing between "+
	     "the coffins and sarcophagi sends a chill down your "+
	     "spine. The faint, flickering glow of the lamps to the "+
	     "west barely provides enough light for you to see the "+
	     "back of your hand. There are dozens of free-standing "+
	     "sarcophagi here, making it hard for you to avoid bumping "+
	     "into things in the darkness. You barely make out a rectangular "+
	     "structure of some kind lurking ominously in the distance "+
	     "to the east.\n\n");

    add_prop(ROOM_S_DARK_LONG, "You can't see much more than the hand "+
	     "in front of your face dimly illuminated by the flickering "+
	     "glow of a lamp.\n");

    add_prop(ROOM_S_DARK_MSG, "The light is too dim here to");

    INSIDE;
    LIGHT(-1);

    add_item( ({"coffins", "sarcophagi", "sarcophagus", "coffin"}),
	     "The coffins and sarcophagi are arranged neatly in ordered "+
	     "rows. You can't quite get an accurate count of them because "+
	     "of the darkness. Trying not to be superstitious, you can't "+
	     "help but feel uneasy around all of this death. The cold breeze "+
	     "blowing through the crypt and flickering, dim lamplight do "+
	     "not ease your mind any, either.\n");

    add_item("lamps",
	     "You can barely make out the flickering glow of one or two "+
	     "lamps to the west. You wonder why it is so hard to see "+
	     "them from here. They were quite visible when you were "+
	     "closer to them .... You wonder if there isn't something "+
	     "more to this darkness than you originally thought.\n");

    add_item( ({"structure", "rectangular structure", "rectangle"}),
	     "Peering through the darkness, you try and make out what "+
	     "the rectangular structure is. It is too difficult to "+
	     "determine what it is from here.\n");

    add_exit(MONKRUIN_DIR + "cry2", "west");
    add_exit(MONKRUIN_DIR + "cry6", "east");
}

    
