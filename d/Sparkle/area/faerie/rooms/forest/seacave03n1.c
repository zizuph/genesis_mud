/*
 * The mountain road between Sparkle and Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit SEA_CAVE_BASE;

int gWine_poisoned = 0,
    gPoison_found = 0;

void
create_sea_cave_room()
{

    set_short("A food storage cave");
    set_long(short() + ". The cave is dry and not very large. Some " +
    "shelves line the walls and hold food and drinks. A passage leads " +
    "south out of the cave.\n");
    
    add_item(({"shelf", "shelves"}),
        "The shelves are full of food and wine, and scattered around " +
        "the room. Some of the food looks spoiled and suitable for eating.\n");
    add_item(({"food", "foods"}),
        "They are stacked on the shelves in boxes and bags. Some of " +
        "the food looks spoiled and not to good to eat.\n");
    add_item(({"drinks", "drink"}),
        "There are casks full of wine and other drinks. They are stacked " +
        "against the wall, and some are even open.\n");
    add_item(({"casks", "wine casks"}),
        "The casks are used to store wine and other drinks. They are " +
        "round and look like they have been rolled in here. From the " +
        "marks on the casks, it looks like the casks were stolen from " +
        "villages. Some are open and half full or even empty.\n");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    remove_prop(ROOM_I_LIGHT);
    reset_room();
    set_cave_room();

    add_exit(FOREST_DIR + "seacave03", "south");
}

void
init()
{
    ::init();

//    add_action("poison_food", "poison");

}

void
reset_room()
{
    gWine_poisoned = 0;
    gPoison_found = 0;
}

mixed
do_search(object searcher, string str)
{
    int awareness;
    object poison;
 
    if (gPoison_found)
        return 0;

    if (!strlen(str))
        return 0; 

    if (!parse_command(str, ({}),
//      "'shelf' / 'shelves' / 'casks' / 'food' "))
        "[shelf] [shelves] [casks] [food] [for] [small] [brown] [bottle] [poison]"))
        return 0;
 
    awareness = searcher->query_skill(SS_AWARENESS);
    if ((awareness + random(10)) > 15)
    {
        poison = clone_object(OBJ_DIR + "poison");
        gPoison_found = 1;
        say(QCTNAME(searcher) + " finds a small bottle.\n", searcher);
        if (poison->move(searcher))
        {
            if (poison->move(TO))
                poison->move(TO, 1);
            return "You find a small bottle on the shelves!\n";
        }

        return "You find a small bottle on the shelves, and quickly pick it up!\n";
    }

    return 0;
}
