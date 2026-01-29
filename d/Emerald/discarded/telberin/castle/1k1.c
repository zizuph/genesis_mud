/*
 * 1K1.c
 * This is on the bridge in front of the gate to Telberin Castle.
 * Originally by Jasmine
 * Re-Described by Xarguul July 25,1996
 *
 */
 
#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
   set_short("Bridge");

   set_long("\n"+
	    "   You stand atop a large wooden bridge amidst the sound "+
	    "of softly running water. It is a cool, light blue transluscent "+
	    "enough to permit you to see the dim outlines of several varieties "+
	    "of fish. Towering before you is the massive gate "+
	    "providing entry into the castle of Telberin. A calm feeling of "+
	    "peace and serenity overcomes you as you listen to the quiet "+
	    "stillness of the surrounding area and the soft, gentle breeze "+
	    "whistle a slow tune as it presses against the castle walls. Birds "+
	    "chirp contentedly off in the distance. Near the gate you notice "+
	    "an apparatus to enable this bridge to be raised and lowered. You "+
	    "examine the castle and can't help but admire the craftsmanship that "+
	    "went into the stone crossing above the gate for the militia and "+
	    "the stone block entrance.\n\n");

    
   add_item("bridge", "The bridge is made of thick dark wood.  It is " +
            "thirteen feet tall and is about nine feet wide.\n");
   add_item("crossing", "The crossing has holes in it for arrows. It " +
            "is tall enough that it would be nearly impossible to " +
            "attack.\n");
   add_item("water", "The water looks milky and foamy as it swirls " +
            "around.  There might even be a creature or two swimming " +
            "in this waterway.\n");
   add_item("militia","You can just see the arrows sticking out of " +
            "the holes in the crossing. There is no way to attack " +
            "them from this position.\n");
   add_item(({"bird","birds"}),"Some of the birds are perched on the " +
           "crossing. A few others are flying about the sky. They all " +
           "sound so peaceful.\n");
   add_item(({"block","blocks"}),"The blocks are made from light grey " +
             "stone. It looks very sturdy and impossible to remove.\n");
   add_item("gate","The gate entrance looks very inviting, and yet " +
            "something inside is telling you to leave now. The gate " +
            "looks well built.\n");
   

   add_prop(ROOM_I_INSIDE, 1);
   
   add_exit(CASTLE_DIR + "1k2", "east");
   add_exit(AVENUE_DIR + "ave01", "west");
   
}
