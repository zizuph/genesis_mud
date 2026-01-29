/*
 * 1k2.c
 * This is the hallway right inside the castle of Telberin
 * Original re-work by Jasmine
 * Description update by Alaron August 15,1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Central Hall");
    set_long("   This is the central hall of Castle Telberin. It seems "+
	     "to go forever to the east. The smooth, polished marble "+
	     "floor branches out of the central hall to the north "+
	     "beneath a wooden sign denoting the armoury. There is a "+
	     "beautiful painting hanging here upon the side wall. The immense "+
	     "hall leads east out to an open courtyard in the center "+
	     "of Castle Telberin. A cool breeze drifts through the "+
	     "hall, whistling against the small grooves in the emerald "+
	     "green stone walls and exiting beneath the portcullis out "+
	     "to the west. From this vantage point, you can see around "+
	     "the massive columns in the courtyard to notice an enormous, "+
	     "lavishly decorated fountain.\n\n");

    add_item( ({"sign", "wooden sign"}),
             "It is a plain, wooden sign. Carved in it are the standard "+
             "elven symbols denoting an armoury. In addition, beneath the "+
             "symbols for the armoury, written in the elven alphabet, "+
                "is the word 'Telberin'.\n");

    add_item("painting", "The painting is a portrait of a throne room. " +
             "There is a Elven King and Queen sitting side by side on " +
             "the dais. The king is holding a sword and placing it on " +
             "the shoulder of a Elven Knight.\n");
    add_item("fountain", "You can barely make out the fountain from " +
             "here.  You can see glistening droplets of water pouring " +
             "from the center of it.\n");
    add_item("courtyard", "The courtyard has light pouring into it. " +
             "It appears to be very large and open to allow the sun " +
             "stream in.\n"); 
    add_item("portcullis",
	     "The enormous portcullis is raised at the moment, its massive "+
	     "black iron spikes hanging down from holes in the top of the "+
	     "stone entry arch.\n"); 


    add_exit(CASTLE_DIR + "1k9","east",0);
    add_exit(CASTLE_DIR + "1k1","west",0);
    add_exit(CASTLE_DIR + "1k3","north",0);

}




