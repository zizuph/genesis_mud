/*
 * Aragorn and Arwen's  private balcony
 * By Finwe, December 1997
 */
 
#include "local.h"
#include "/d/Shire/sys/defs.h"
 
inherit VALLEY_BASE;
 
void
create_valley_room()
{
    add_my_desc("This private balcony connects both bedrooms. " +
        "It overlooks the garden below and is hidden by some " +
        "tall trees. A wooden rail surrounds the perimeter of the " +
        "balcony. The balcony is small, allowing only a few " +
        "people on it. Below is a garden with a path leading " +
        "east.\n");

    add_item(({"down", "balcony"}),
        "The balcony is made of planks of oak. They are solid " +
        "and planed smooth.\n");
    add_item("garden",
        "The garden is obscured by the tree tops, which are " +
        "green and healthy. A path can be seen leading east " +
        "and northeast into the forest.\n");
    add_item(({"tree", "trees", "tree tops", "fruit trees",
            "fruit tree"}),
        "The fruit trees below you are healthy and full of " +
        "fruit. The branches wave in the breeze.\n");
    add_item(({"tall trees", "great trees"}),
        "The tall trees are oak. They are taller than the balcony " +
        "and offer protection and privacy to the balcony.\n");
    add_item("branches",
        "The oak branches are thick and ancient looking. " +
        "Nonetheless, they are smooth to the touch and covered " +
        "with many green leaves.\n");
    add_item(({"leaves", "leaf"}),
        "The oak leaves are as large as a man's hand. They " +
        "are a healthy, green and rustle in the breeze.\n");
    add_item(({"river", "river bruinen", "river Bruinen"}),
        "The river, a small ribbon of blue water, bubbles and " +
        "runs west past the house.\n");
    add_item(({"house", "walls", "wall"}),
        "The walls of the house are stone. Set into them are " +
        "ornately carved beams. The beams form criss-cross " +
        "and diamond patterns across the walls.\n");
    add_item("roof",
        "The roof isn't really visible, but you see the ends of " +
        "cedar shingles extending over the eaves.\n");
    add_item("eaves",
        "The eaves hang over the walls of the house. Cedar " +
        "shingles can bee seen.\n");
    add_item(({"shingles", "cedar shingles"}),
        "The cedar shingles are made from split cedar. They are " +
        "weather worn but still in good condition.\n");
    add_item("rail",
        "The rail is made of solid wood. It is waist high and " +
        "runs around the edge of the balcony.\n");

    set_room_tell_time(ROOM_TELL_TIME);
    add_room_tell("A nightingale sings in the distance.");
    add_room_tell("You hear some laughing in nearby.");
    add_room_tell("Some elves can be heard singing nearby.");
    add_room_tell("Somewhere nearby you hear a fair voice " + 
        "reciting a Lay.");
    add_room_tell("A bird warbles a tune in the distance.");
    add_room_tell("An elf patrols the area below.");
    add_room_tell("In the distance you hear a group of elves " +
        "laughing gaily and singing songs.");
    add_room_tell("You hear a quiet snap and a tree shakes below.");
    add_room_tell("The fruit trees move gently in the breeze.");
    add_room_tell("Fragrances from the garden drift up.");    
 
    add_exit(VALLEY_DIR + "arwen_rm", "north");
    add_exit(VALLEY_DIR + "aragorn_rm", "south");

}

 
string short_desc()
{
    return ("A private balcony");
}
