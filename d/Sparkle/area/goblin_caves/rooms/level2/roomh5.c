/*
 * Empty cave room
 * Boreaulam, August 2012
 */

#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
    ::create_room();

    set_short("Empty cave");
    set_long("You are standing in the middle of a small, damp cave. The " +
        "cave is filled with several stalagmites and stalactites, and " +
        "slow drips of water are constantly falling down from the ceiling " +
        "and along the jagged stone walls. It feels rather cramped in here, " +
        "as there is not much space to move around, while dark shadows " +
        "surround you and seem to creep into every dark corner. A low " +
        "opening in the wall to the northwest leads back out into the " +
        "main cavern and the lake beyond.\n");

    add_item(({"corner", "corners", "dark corner", "dark corners", "shadow",
                "shadows","dark shadow","dark shadows"}),
        "Lurking behind every outcropping of stone and into every " +
        "dark corner, are gloomy shadows that could be hiding almost " +
        "anything.\n");
    add_item(({"opening", "irregular opening"}),
        "This opening in the northwestern wall leads back out into the " +
        "larger cavern you came from originally.\n");
    add_item(({"floor", "down"}),
             "The grey, stone floor here is uneven, but has been worn " +
        "smooth over what you suspect is many years of use.\n");
    add_item(({"wall", "walls"}),
        "Which wall did you want to examine? The north wall? The " +
        "south wall?\n");
    add_item(({"ceiling", "up"}),
        "The dull grey stone of the ceiling is covered with wet, " +
        "dripping stalactites that cast shadows into the dark corners " +
        "of the cave.\n");
    add_item(({"south wall", "southern wall", "southeastern wall",
            "southeast wall","southwest wall","northeast wall",
            "northeastern wall","east wall","eastern wall","west wall",
            "western wall","north wall","northern wall","southwestern wall"}),
        "This wall is made from the same dull, grey stone as " +
        "the rest of the cave. Several stalactites and stalagmites " +
        "obscure your view however.\n");
    add_item(({"northwest wall", "northwestern wall"}),
        "There is an opening in the wall of the cave here, leading " +
        "back towards the larger cavern and the lake which wait " +
        "outside.\n");
    add_item(({"lake", "underground lake", "wide lake"}),
        "Barely visible through the opening in the northwestern wall " +
        "is the wide underground lake which fills the middle of the " +
        "cavern outside.\n");
    add_item(({"cave", "room", "here"}),
        "You are standing in the middle of a small, damp cave. The " +
        "cave is filled with several stalagmites and stalactites, and " +
        "slow drips of water are constantly falling down from the ceiling " +
        "and along the jagged stone walls. It feels rather cramped in here, " +
        "as there is not much space to move around, while dark shadows " +
        "surround you and seem to creep into every dark corner. A low " +
        "opening in the wall to the northwest leads back out into the " +
        "main cavern and the lake beyond.\n");
    add_item(({"cavern", "large cavern", "larger cavern"}),
        "When you look through the opening in the northwest wall, you can " +
        "see a large cavern with a wide lake in the middle of it.\n");
    add_item(({"caves", "caverns"}),
        "You are in a large series of caves and caverns that tunnel " +
        "deep beneath the mountains.\n");
    add_item(({"stone", "grey stone", "granite"}),
        "This dull grey stone is the very bones of the mountains you are " +
        "currently beneath. The stone in this cave is constantly wet and " +
        "damp.\n");
    add_item(({"stalagmite", "stalactite", "stalagmites","stalactites",
            "stone outcropping","outcropping"}),
        "This cave is filled with dozens of stalagmites and stalactites, " +
        "probably a result of the water that is constantly dripping down " +
        "here. Sharp and pointed, they almost give the impression that " +
        "this small cave is full of jagged teeth just waiting to chew " +
        "up the unwary traveller.\n");
    add_item(({"water", "drops", "water drop"}),
        "There is quite a bit of water seeping into this cave through " +
        "the ceiling. It seems to have created the dozens of stalagmites " +
        "and stalactites you see everywhere.\n");
    add_item(({"moss", "mould"}),
        "You cannot see any moss here, but who knows what might be " +
        "hiding in the dark corners of a wet cave like this?\n");
    add_exit("roomg2", "northwest");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

} /* create_room */

/*
 * Function name:        do_search
 * Description  :        allow the player to search things in the room
 * Arguments    :        object pl  - the player object,
 *                       string arg - what the player tried to search
 * Returns      :        int 1 - success, 0 - failure
 */
public string
do_search(object pl, string arg)
{
    if (member_array(arg,
        ({ "corner", "corners", "dark corner", "dark corners"}) ) == -1)
    {
        return "Your search reveals nothing special.\n";
    }

    object moss = clone_object(OBJS_DIR + "l2_moss");
    moss->move(this_player());

    return "You find some damp green moss in a dark corner.";

} /* do_search */
