// Tunnel room, part of WOrm's lair
// Descriptions by Ilyian


inherit "/d/Avenir/common/dark/lair/lair_common";

#include "/d/Avenir/common/dark/dark.h"

void
create_room ()
{
    ::create_room();
  
    set_short ("in the lair");
    set_long("This fiery tunnel seems to go on forever, like "+
        "something out of a dark and hellish dream. Flames lick "+
        "upwards along the sides of the tunnel, sending gouts of "+
        "smoke into the air. There is a thick, heavy silence "+
        "here, through which you can almost make out a rhythmic "+
        "thrumming.\n");
  
    set_tell_time (120);
    add_tell ("You hear a strange sound, like loud but distant sigh.\n");
    add_tell ("Part of stalactite above your head suddenly falls down, "+
	"narrowly missing you!\n");
    add_tell ("You hear low scraping sound, like rough paper against "+
        "rock.\n");
    add_tell ("The earth trembles slightly.\n");
    add_tell ("Your blood freezes as you hear a distant shriek of agony!\n");
    add_tell ("Suddenly a wave of hot air envelopes you!\n");

    IN;
}





