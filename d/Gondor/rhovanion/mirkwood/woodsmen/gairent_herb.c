/*
 * Gairent
 * Varian - March 2015
 */

#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MIRKWOOD_STD_DIR + "room";

static object wayruth;

void

create_room()

{
    set_short("An old building full of herbs");
    set_long("You have entered a very crowded old building, filled with the " +
        "pungent aroma of herbs wafting through the air. This building is " +
        "filled with shelves and racks of all sorts, each carrying an " +
        "abundance of boxes, jars and other containers which are filled " +
        "with an endless variety of herbs. Hanging from the rafters above, " +
        "strings of herbs have been tied and dried in anticipation of " +
        "potential customers. Tucked away against the south wall is a small " +
        "desk, which the herbalist is using as her sales counter. Two " +
        "large windows have been placed on either side of the door in the " +
        "western wall, giving you a view of the village outside.\n");
  
    add_item_light(({"herbs", "herb"}),
        "Everywhere you look in this hut, you see herbs! Fresh herbs, dried " +
        "herbs, herbs of all sorts! You could probably speak with the " +
        "herbalist to get a detailed list of which herbs they might " +
        "currently have in stock.\n", LIGHT_ALL);
    add_item_light(({"shelf", "shelves", "rack", "racks"}),
        "The middle of the hut is filled with racks of shelving, with " +
        "every spare inch filled with a variety of containers which have " +
        "all been filled with herbs.\n", LIGHT_ALL);
    add_item_light(({"box", "boxes"}),
        "There are several small boxes scattered around the shelves inside " +
        "this hut, each of which seems to be filled with herbs.\n", LIGHT_ALL);
    add_item_light(({"jar", "jars"}),
        "These jars are made of glass, and they are being used to store " +
        "various berries on the shelves inside this hut.\n", LIGHT_ALL);
    add_item_light(({"container", "containers", "other container",
                "other containers"}),
        "As you look around this hut, you can see not only boxes and jars, " +
        "but other containers such as pouches and wraps which all serve " +
        "to sort and store a huge variety of herbs.\n", LIGHT_ALL);
    add_item_light(({"wrap", "wraps"}),
        "There are several wraps of herbs, hanging down on strings which " +
        "have been attached to the rafters above.\n", LIGHT_ALL);
    add_item_light(({"pouch", "pouches", "bag", "bags"}),
        "There are dozens of bags and pouches sitting on the shelves of this " +
        "shop, all seemingly filled with herbs. You should probably speak " +
        "with the herbalist if you are looking for any herb in " +
        "particular.\n", LIGHT_ALL);
    add_item_light(({"rafter", "rafters"}),
        "These wooden rafters support the peaked ceiling of the hut, but " +
        "also seem to have provided a convenient place to hang down strings " +
        "of herb-filled wraps to be dried.\n", LIGHT_ALL);
    add_item_light(({"ceiling", "up"}),
        "The wooden ceiling slopes up to a peak, supported by dozens of " +
        "wooden rafters.\n", LIGHT_ALL);
    add_item_light(({"string", "strings"}),
        "All around the hut, you can see strings of herbs which are hanging " +
        "down from the rafters above.\n", LIGHT_ALL);
    add_item_light(({"down", "floor"}),
        "The floor here is quite dirty, but it appears to be made of " +
        "wood.\n", LIGHT_ALL);
    add_item_light(({"west wall", "western wall"}),
        "There are two large windows in the western wall, flanking the thin, " +
        "wooden door which leads back out into the middle of Gairent " +
        "village.\n", LIGHT_ALL);
    add_item_light(({"east wall", "eastern wall"}),
        "You cannot see much of the eastern wall, as it is filled from floor " +
        "to ceiling with shelves of herbs.\n", LIGHT_ALL);
    add_item_light(({"north wall", "northern wall"}),
        "You cannot see much of the northern wall, as it is filled from " +
        "floor to ceiling with shelves of herbs.\n", LIGHT_ALL);
    add_item_light(({"south wall", "southern wall"}),
        "You cannot see much of the southern wall, as it is filled from " +
        "floor to ceiling with shelves of herbs. However, in front of some " +
        "of the shelves, near one of the windows, is a wooden desk with a " +
        "small stool resting behind it.\n", LIGHT_ALL);
    add_item_light(({"window", "windows"}),
        "These windows are a little dirty, but you can make out the village " +
        "of Gairent when you peer through them.\n", LIGHT_ALL);
    add_item_light(({"door", "wooden door"}),
        "This door is made of wood, but it appears rather old and flimsy. It " +
        "seems to be kept open, allowing people to come in and out as they " +
        "please.\n", LIGHT_ALL);
    add_item_light(({"desk", "counter"}),
        "This small desk is apparently being used as a sales counter by " +
        "the local herbalist. You notice a small stool resting behind the " +
        "counter for the herbalist to sit upon.\n", LIGHT_ALL);
    add_item_light(({"stool", "small stool"}),
        "This is a small, wooden stool which the herbalist occasionally " +
        "sits upon. It is neatly tucked in behind the counter on the " +
        "southern wall, and seems to only be used infrequently.\n", LIGHT_ALL);
    add_item_light(({"village", "gairent"}),
        "Outside the hut, you can see the middle of the village of " +
        "Gairent.\n", LIGHT_ALL);

    add_prop(ROOM_I_INSIDE,1);
    
    add_exit(WOODSMEN_DIR + "gairent2", "west", "@@village@@");

    reset_room();
}
int
village()
{
write("\n\nYou make your way back out into the middle of the village.\n\n");
return 0;
}


reset_room() 
{
    if(!wayruth) wayruth = clone_object(WOODSMEN_DIR + "npc/wayruth.c");
    if (!present(wayruth)) wayruth->move_living("somewhere", this_object());
}