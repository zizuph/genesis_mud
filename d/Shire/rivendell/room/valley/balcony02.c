/*
 * Elrond's private balcony
 * By Finwe, December 1997
 */
 
#include "local.h"
#include "/d/Shire/sys/defs.h"
 
inherit VALLEY_BASE;
 
void
create_valley_room()
{
    set_extraline("The private balcony overlooks the garden below. " +
        "A wooden rail surrounds the perimeter of " +
        "the balcony. The balcony is small, allowing only a few " +
        "people on it. Beyond the garden, you can see the river " +
        "Bruinen flowing west out of the valley.");

    add_item(({"down", "balcony"}),
        "The balcony is made of planks of oak. They are solid " +
        "and planed smooth.\n");
    add_item("garden",
        "The garden is obscured by the tree tops, which are " +
        "green and healthy.\n");
    add_item(({"tree", "trees", "tree tops", "fruit trees",
            "fruit tree", "tall trees"}),
        "The fruit trees below you are healthy and full of  " +
        "fruit. The branches wave in the breeze.\n");
    add_item(({"river", "river bruinen", "river Bruinen"}),
        "The river, a small ribbon of blue water, bubbles and " +
        "runs west past the house.\n");
    add_item("house",
        "The walls of the house are stone. Set into them are " +
        "ornately carved beams. The beams form a criss-cross " +
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
    add_room_tell("In the distance you hear a group of elves " +
        "laughing gaily and singing songs.");
    add_room_tell("You hear a quiet snap and a tree shakes below.");
    add_room_tell("The fruit trees move gently in the breeze.");
    add_room_tell("Fragrances from the garden drift up.");    
    add_room_tell("Delicious odors drift up from the kitchen below.");
    add_room_tell("A bird chirps in a nearby fruit tree.");   
    add_room_tell("A bird flies out of a tree.");
    add_room_tell("A bird flies into a fruit tree. The air " +
        "erupts with the sound of babies peeping.");
 
    add_exit(VALLEY_DIR + "elrond_bdrm", "north");
}

 
string short_desc()
{
    return ("Elrond's private balcony");
}
