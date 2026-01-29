inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    set_short("Northwest corner of Courtyard");
    set_long("   You are standing in the northwestern corner of the "+
             "courtyard. Only few figures of monks are "+
             "seen around, since due to the hot sun the place is quite "+
             "warmed. Your attention attracts big carving on the inner "+
             "side of courtyard's wall. To the south there is a well.\n\n");

    add_exit(TEMPLE_DIR + "hallway_n", "west", 0);
    add_exit(TEMPLE_DIR + "court_w", "south", 0);
    add_exit(TEMPLE_DIR + "court_ne", "east", 0);
 
    add_item("carving", "The carving depicts a mourning of dead "+
                   "elf by some human warrior. The body of elf "+
                   "is lying on the floor in some big cave, and "+
                   "human is kneeling near it, holding the hand "+
                   "in his. There are barely noticable bodies of "+
                   "some humanoid monsters. You look closely "+
                   "but don't find any clue who was the master who "+
                   "carved this.\n");
}
