#pragma save_binary

inherit "/d/Genesis/ship/cabin";
#include "/d/Gondor/common/lib/time.h"

#include "/d/Gondor/defs.h"

void
create_cabin()
{
    set_short("A small cabin inside the large ship");
    set_long("This cabin is small but still nicer than the others on board. " +
        "On a small table there are some maps. The cabin is illuminated " +
        "by a lantern in the ceiling. A set of plain wooden stairs leads " +
        "up to the deck, while another set of even plainer stairs leads below.");
    add_item("lantern", 
        "The lantern is secured in the ceiling. It is a large brass " +
        "lantern with a large oil container that should last quite a while.");
    add_item(({"table", "small table"}), 
        "Long ago, the surface of the table must have been polished. Now " +
        "there is little left of that. Scratches and cuts from nautical " +
        "intruments and eating knives have left their traces among ink " +
        "stains and circular spots that were made by glasses and bottles.");
    add_item(({"map", "maps"}), 
        "The maps are nautical maps and there seem to be several doublets, " +
        "some being riddled with marks lines and notations while others " +
        "seem brand new. The maps show the western coast of Middle-earth " +
        "and look well used.");
    add_exit(SHIP_DIR + "deck8",      "up", 0);
    add_exit(SHIP_DIR + "slavedeck8", "down", 0);
}
