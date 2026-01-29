// Part of worm lair.
// Descriptions by Ilyian.

inherit "/d/Avenir/common/dark/lair/lair_common";

#include "/d/Avenir/common/dark/dark.h"

void
create_room ()
{
    ::create_room();
    set_short ("in the worm lair");
    set_long ("You can almost feel the weight of the world "+
        "above you pressing down on the hot, dry air here. "+
        "The tunnel continues with its uniform circular " +
        "shape into the unnatural light of the fires around "+
        "you.\n");

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
