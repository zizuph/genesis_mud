inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    set_short("Southeast corner of Courtyard");
    set_long("   You are standing in the southeastern corner of the "+
             "courtyard. Only few figures of monks are "+
             "seen around, since due to the hot sun the place is quite "+
             "warmed. Your attention attracts big carving on the inner "+
             "side of courtyard's wall. To the north you can see "+
             "a building of some sort.\n\n");

    add_exit(TEMPLE_DIR + "court_e", "north", 0);
    add_exit(TEMPLE_DIR + "court_sw", "west", 0);
 
    add_item("carving","The carving depicts the human warrior "+
            "standing in the tunnel of some sort of "+
            "dungeon. He holds a long sword in one hand and "+
            "a litten torch in another. You look closely but "+
            "don't find any clue who was the master "+
            "who carved this.\n");
}
