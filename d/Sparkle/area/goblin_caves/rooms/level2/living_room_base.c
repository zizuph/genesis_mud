/*
 * Living room base room
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

string get_exit_dir();
/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("small living cave");
    set_long("You have entered a small cave filled with all sorts of " +
        "furniture, quite clearly a family of goblins has made this their " +
        "home. Two beds are tucked up against one end of the cave, while " +
        "a table and chairs are standing at the other end. Some wooden " +
        "chests appear to hold everything a domestic household might need, " +
        "from food to clothing to basic tools. An irregular opening in the " + 
        get_exit_dir() + " wall leads back out to the enormous cavern " +
        "you originally came from. Several torches have been mounted on " +
        "the walls here to help make this cave quite well lit.\n\n");
    
    add_item(({"furniture", "belongings"}),
        "There is a lot of furniture here, all made of wood. A round table is" +
        "surrounded by four chairs in one part of the cave, while two beds " +
        "and a couple of wooden chests rest at the opposite end.\n");
    add_item(({"bed", "beds"}),
        "There are two beds here, one larger and one smaller. Both have " +
        "been left in a rather messy state, with their blankets left lying " +
        "is a tumbled heap.\n");
    add_item(({"blanket", "blankets", "smelly blankets", "smelly blanket",
            "heap", "pile"}),
        "There are some rather smelly blankets which have been left on top " +
        "of the beds here. Instead of being neatly drawn over the beds, " +
        "they have simply been left in a crumpled, stinky heap.\n");
    add_item(({"small bed", "smaller bed"}),
        "This is the smaller of the two beds, a couple of cloth dolls " +
        "sitting here suggest that this bed is a bed for the children " +
        "in the family that lives here.\n");
    add_item(({"doll", "cloth doll", "dolls", "cloth dolls", "toy", "toys"}),
        "There are a couple of cloth dolls, obviously toys for the " +
        "children who live here, lying on top of the smaller of the two " +
        "beds.\n");
    add_item(({"large bed", "larger bed"}),
        "This is the larger of the two beds, and from all indications, it " +
        "appears to be used by the parents of the family who lives here.\n");
    add_item(({"table", "wood table", "round table"}),
        "This round table sits at one end of the cave, surrounded by four " +
        "wooden chairs. This appears to be where the family eats their " +
        "meals.\n");
    add_item(({"chair", "chairs", "wooden chair", "wooden chairs"}),
        "You can see four wooden chairs here, all settled around a " +
        "round, wooden table. The chairs are not very fancy, but they " +
        "do appear to be reasonably sturdy.\n");
    add_item(({"chest", "chests", "wooden chest", "wooden chests"}),
        "There are several wooden chests here, obviously used by the " +
        "occupants of this cave to store their daily goods. Some of them " +
        "hold clothing, while others hold food or tools.\n");
    add_item(({"tool", "tools"}),
        "Tucked away in some of the wooden chests here, you can see a " +
        "handful of basic stone tools. They would not be of any real " +
        "interest to anyone save the family that lives here.\n");
    add_item(({"food", "bread", "biscuits"}),
        "Stuffed into some of the wooden chests, you can spot what appears " +
        "to be a variety of food. Mostly, it appears to be a collection " +
        "of bread and biscuits, but it all looks stale and none of it " +
        "really looks appetizing.\n");
    add_item(({"clothes", "clothing"}),
        "Several of the wooden chests here hold clothing for the family. " +
        "Judging by the smell, these clothes have not been washed in quite " +
        "a long time, if ever!\n");
    add_item(({"opening", "irregular opening"}),
        "This opening in the " + get_exit_dir() + " wall leads back out " +
        "into the larger cavern you came from originally.\n");
    add_item(({"lake", "underground lake", "wide lake"}),
        "Barely visible through the opening in the northern wall is " +
        "the wide underground lake which fills the middle of the " +
        "cavern outside.\n");
    add_item(({"cavern", "large cavern", "larger cavern"}),
        "When you look through the opening in the north wall, you can " +
        "see a large cavern with a wide lake in the middle of it.\n");
    add_item(({"caves", "caverns"}),
        "You are in a large series of caves and caverns that tunnel " +
        "deep beneath the mountains.\n");
    add_item(({"floor", "down"}),
        "The grey, stone floor here is uneven, but has been worn " +
        "smooth over what you suspect is many years of use.\n");
    add_item(({"wall", "walls"}),
        "The walls here are made of the same grey stone as everything " +
        "else in these caves. A few torches have been mounted here to " +
        "provide some light.\n");
    add_item(({"ceiling", "up"}),
        "The dull grey stone of the ceiling has been roughly chiseled, " +
        "obviously worked by hand to expand what was probably a " +
        "naturally existing cave at first.\n");
    add_item(({"torch", "torches"}),
        "There are a few torches hanging on the walls here, burning " +
        "brightly and keeping this cave well lit.\n");
    add_item(({"stone", "grey stone", "granite"}),
        "This dull grey stone is the very bones of the mountains you are " +
        "currently beneath. This granite is very hard, but in many places " +
        "it appears that several industrious goblins have chiseled away " +
        "at the walls and ceilings to make these caves more habitable.\n");


    add_npc(NPCS_DIR + "l2_mother", 1, &->arm_me());
    add_npc(NPCS_DIR + "l2_girl", 1, &->arm_me());
    add_npc(NPCS_DIR + "l2_boy", 1, &->arm_me());
} /* create_room */


/*
 * Function name:        get_exit_dir
 * Description  :        blank function to override to return 
 */
string
get_exit_dir()
{
    return "wrong";
} /* get_exit_dir */
