/*
 * Ship cabin 
 * -- Finwe, January 2006
 */
#pragma save_binary

#include "defs.h"
#include "/d/Faerun/defs.h"


inherit SHIP_CABIN_BASE;

void
create_cabin()
{
    set_short("A small ship's cabin");
    set_long("This is a small cabin inside a ship. It is tight and stuffy " +
        "with some light coming in from the outside and from the lantern " +
        "hanging from the ceiling. A simple table sits at one end of " +
        "the room with some maps scattered across it. Some stairs lead " +
        "up to the deck.\n");

    add_item(({"stairs"}),
        "They are narrow and lead up to the deck.\n");
    add_item("lantern",
        "The lantern hangs from the ceiling. It is large and made from " +
        "brass. It swings back and forth, casting shadows everywhere.\n");
    add_item(({"table"}), 
        "It is small and made of wood. The table is strong looking and " +
        "secured to the floor to stop it from sliding around in rough " +
        "waters. There are visible scratches on it. Some maps are scattered " +
        "on it.\n");
    add_item(({"map", "maps"}),
        "The maps are hand drawn and look well used. They have various " +
        "marks on them, probably notes from the captain. They seem to " +
        "depict trade routes or places to avoid while sailing.\n");
    add_exit(SPARKLE_DIR + "deck", "up");
}