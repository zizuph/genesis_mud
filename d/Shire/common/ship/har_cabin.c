#include "/d/Shire/common/defs.h"
#pragma save_binary

inherit "/d/Genesis/ship/cabin";

void
create_cabin()
{
    set_short("A small cabin inside the large ship");
    set_long("This cabin is small but still nicer than the others on board. A bed sits in one corner of the cabin. On a small table are some maps. The cabin is illuminated by round windows. Stairs lead above deck. A lantern hangs from the ceiling.");
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

    add_exit(SHIP_DIR + "har_deck", "up",0,3);
    add_prop(ROOM_I_LIGHT, 3);

    add_item(({"windows","window","portholes","porthole"}),
        "Due to the restricted view the narrow holes provide, all that "+ 
        "can be seen from the windows are the waves of the blue-green "+
        "sea.\n");
    add_item(({"stairs","stairway","stairwell"}),
        "The stairway turns about a central column in a short spiral "+
        "before reaching a short landing that terminates in the door "+
        "of the cabin. The stairs and railing are crafted of the same "+
        "wood as the rest of the cabin.\n");
    add_item(({"central column","column"}),
        "The column is thick, and obviously the lower part of a mast.\n");
    add_item("bedding","The bedding is composed of a sturdy cushion "+
        "covered with blankets and topped by a spongy, supportive pillow.\n");
    add_item(({"bed","beds"}),
        "Apparently growing out of the walls of the cabin like branches "+
        "from a tree, the beds are surely as sturdy as those same branches, "+
        "supplying a slight amount of springiness to the sleeper, which "+
        "helps absorb some of the rolling of the ship while at sea. "+
        "The beds line the starboard and port sides of the ship, being "+
        "stacked in three columns of two beds on each side. The bedding "+
        "itself is well padded and comfortable, comfortable enough to "+
        "idle away a long cruise sleeping on.\n");
    add_item(({"bench","benches"}),
        "These benches are provided for the comfort of passagers who "+
        "do not wish to stand but also have no desire to lay about on "+
        "one of the beds. They were obviously created by the loving hands "+
        "of a master woodscrafter, as the legs merge perfectly with "+
        "the floor of the cabin and the seats of the benches, "+
        "the whole construct being flawless and inviting.\n");
    add_item(({"deck","hull","crews quarters","quarters"}),
        "It would require X-ray vision to see that! Not even the vampyres "+
        "have X-ray vision yet!\n");
    add_item(({"wood","floor","ceiling","walls","wall"}),
        "All of the wooden components of the cabin are crafted from the "+
        "same expertly joined lengths of differing varieties of wood that "+
        "the deck, hull, and crews quarters are built from. The strips "+
        "are joined so well that no seams are visible from a casual inspection "+
        "and the shades blend from light to dark and back to light, "+
        "producing an almost hypnotic effect when combined with the swaying "+
        "of the ship.\n");
}