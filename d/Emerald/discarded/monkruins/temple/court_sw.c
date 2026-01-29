inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    set_short("Southwest corner of Courtyard");
    set_long("   You are standing in the southwestern corner of the "+
             "courtyard. Only few figures of monks are "+
             "seen around, since due to the hot sun the place is quite "+
             "warmed. Your attention attracts big carving on the inner "+
             "side of courtyard's wall. To the north there is a well.\n\n");

    add_exit(TEMPLE_DIR + "hallway_s", "west", 0);
    add_exit(TEMPLE_DIR + "court_w", "north", 0);
    add_exit(TEMPLE_DIR + "court_se", "east", 0);
 
    add_item("carving","The carving depicts an male elf "+
            "drinking the water at the bank of some small "+
            "river. His bow and sword are lying on the ground "+
            "near him. You look more closely, but there is no "+
            "any clue who was the master who carved this.\n");
}
