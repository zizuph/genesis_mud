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
    set_short("A small cabin");
    set_long("This small cabin is beneath the deck and at the base of a flight of stairs. A round table is secured in the center of the room. Scattered across it are several maps. A lamp swings from the ceiling, casting light and shadows around the cabin.\n");

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
    add_exit(FLOTSAM_DIR + "deck", "up");
}