/*
 * Rope Shop
 * Boreaulam, Nov 2012
 */
#include "defs.h"
#pragma save_binary
#pragma strict_types

inherit L2_BASE_ROOM;
inherit "/lib/shop";

#include <stdproperties.h>

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();
    set_short("Shop");
    set_long("You find yourself in a tidy little cave, filled with several " +
        "useful items. This appears to be a store which serves the needs " +
        "of the local goblins. Several torches have been mounted on the " +
        "walls here, each burning brightly to provide quite a bit of light. " +
        "It appears as if the owner of the store, a shopkeeper who sits " +
        "behind the long, stone counter against the northern wall, keeps " +
        "all of his inventory in the middle of the cave. A white sign " +
        "is displayed prominently above his head, helping people to " +
        "understand the rules of his store. An opening in the western wall " +
        "will take you back out towards the lake and the larger cavern you " +
        "originally came from. \n\n");

    config_default_trade();

    add_exit ("roome3", "west");

    add_item(({"opening", "irregular opening"}),
        "There is an irregular shaped opening in the wall which leads back " +
        "out into the larger cavern you came from originally.\n");
    add_item(({"lake", "underground lake", "wide lake"}),
        "Barely visible through the opening in the western wall is " +
        "the wide underground lake which fills the middle of the " +
        "cavern outside.\n");
    add_item(({"cavern", "large cavern", "larger cavern"}),
        "When you look through the opening in the west wall, you can " +
        "see a large cavern with a wide lake in the middle of it.\n");
    add_item(({"caves", "caverns"}),
        "You are in a large series of caves and caverns that tunnel " +
        "deep beneath the mountains.\n");
    add_item(({"floor", "ground", "down"}),
        "The ground beneath your feet is the same grey stone as the " +
        "walls and ceiling around you, only it has been worn smooth " +
        "from centuries of traffic.\n");
    add_item(({"wall", "walls"}),
        "The walls here are made of the same grey stone as everything " +
        "else in these caves. Several torches have been strategically " +
        "placed on all of the walls to provide a maximum amount of light " +
        "here.\n");
    add_item(({"south wall", "southern wall"}),
        "The dull grey stone of the southern wall has been cleanly chiseled, " +
        "allowing the shopkeeper to set up some shelves against it to " +
        "display his wares that much better. You can also see that " +
        "several torches have been mounted " +
        "upon this wall.\n");
    add_item(({"north wall", "northern wall"}),
        "The northern wall of the store has a long, stone counter which runs " +
        "almost the entire length of the cave. A white sign has been mounted " +
        "on the wall behind the counter. You can also see that several " +
        "torches have been mounted " +
        "upon this wall.\n");
    add_item(({"east wall", "eastern wall"}),
        "The dull grey stone of the eastern wall has been cleanly chiseled, " +
        "allowing the shopkeeper to set up some shelves against it to " +
        "display his wares that much better. You can also see that several " +
        "torches have been mounted " +
        "upon this wall.\n");
    add_item(({"west wall", "western wall"}),
        "The dull grey stone of the western wall has been cleanly chiseled, " +
        "in fact, the wall looks so clean that the irregular shape of the " +
        "opening seems oddly out of place here. Through the opening, you " +
        "can see the underground lake and the rest of the cavern " +
        "beyond. You can also see that several torches have been mounted " +
        "upon this wall.\n");
    add_item(({"ceiling", "up"}),
        "The dull grey stone of the ceiling has been cleanly chiseled here, " +
        "obviously worked by hand to expand what was probably a " +
        "naturally existing cave at first.\n");
    add_item(({"torch", "torches"}),
        "Plenty of torches have been mounted on the walls here, each of them " +
        "strategically placed to provide a maximum amount of light.\n");
    add_item(({"stone", "grey stone", "granite"}),
        "This dull grey stone is the very bones of the mountains you are " +
        "currently beneath. This granite is very hard, but in many places " +
        "it appears that several industrious goblins have chiseled away " +
        "at the walls and ceilings to make these caves more habitable.\n");
    add_item("shop", long());
    add_item(({"counter", "table", "desk", "countertop"}),
        "This long, stone counter provides a place for the shopkeeper to " +
        "conduct his business.\n");
    add_item(({"shopkeeper", "merchant"}),
        "This goblin sits behind the long counter, waiting for the next " +
        "customer.\n");
    add_item(({"cave", "store", "here"}),
        "You find yourself in a tidy little cave, filled with several " +
        "useful items. This appears to be a store which serves the needs " +
        "of the local goblins. Several torches have been mounted on the " +
        "walls here, each burning brightly to provide quite a bit of light. " +
        "It appears as if the owner of the store, a shopkeeper who sits " +
        "behind the long, stone counter against the northern wall, keeps " +
        "all of his inventory in the middle of the cave. A white sign " +
        "is displayed prominently above his head, helping people to " +
        "understand the rules of his stone. An opening in the western wall " +
        "will take you back out towards the lake and the larger cavern you " +
        "originally came from. \n");
    add_item(({"shelves", "shelf"}),
        "There are several shelves mounted on the eastern and southern " +
        "walls, each filled with plenty of interesting items that the " +
        "shopkeeper has available for sale.\n");
    add_item("items", "Use <list> to check staff for sale.\n");
    add_item(({"sign", "small sign"}),
             "You should <read sign>.\n");

    set_store_room(ROOMS_DIR+"level2/store");
} /* create_room */

/*
 * Function name:        init
 * Description  :        init room
 */
void
init()
{
  ::init();

  init_shop();
} /* init */

