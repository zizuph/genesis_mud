
/*
 *   coder(s):  Amelia  coded 22/4/95
 *
 *   Modifications by Maniac 15/9/96
 *
 *   This room is part of the mermaid quest. If players get past
 *   the giant clam, they may search here for oysters.
 *   Assuming one hasn't been found recently, they may, after
 *   a number of searches find one with a black pearl in it,
 *   which is the main quest item.
 *   Adden oyster to searches / Hyde 27NOV15
 *
 * Cotillion - 2020-10-04
 * - Type confusion
 */

inherit "/d/Calia/std/water_room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

#include SEA_QUESTS

int searches, oysters, lucky;


void
reset_room()
{
    oysters = 15 + random(10);
    lucky = (oysters/2)+random(oysters/3);
    searches = 0;
}

void
create_water_room()
{
    set_short("Sea alcove containing an oyster bed");
    set_long("You are in a small alcove set into a sharp rise " +
       "in the sea bed, fairly deep down. This small dark place " +
       "would be uninteresting but for the plethora of oysters that you " +
       "see. The grey shellfish are clustered together in a large " +
       "mass and are within easy reach. The blue-green sea is all " +
       "around you, and feels warm and refreshing.\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item("alcove", "You're inside it!\n");

    add_item(({"sea", "sea bed"}), "You see nothing special.\n");

    add_item((({"oyster", "oysters", "oyster bed", "shellfish"})),
       "The grey shellfish are clustered together in a large mass. " +
       "You could maybe find an oyster that you were able to fairly " +
       "easy get from the mass. \n");

    add_prop(OBJ_S_SEARCH_FUN, "find_oyster");
    add_prop(OBJ_I_SEARCH_TIME, 5);

    add_swim_exit(SECTOR_PATH(3,7,2)+"wr_3_7_2", "west", 0, 1);

    reset_room();
}


string
find_oyster(object searcher, string str)
{
    object oyster;

    if (str == "here for oyster" || str == "here for oysters" ||
        str == "oysterbed" || str == "oyster bed" || str == "oysters" ||
        str == "oysterbed for oysters" || str == "oyster bed for oysters" ||
        str == "oysterbed for oyster" || str == "oyster bed for oyster" ||
        str == "oyster")  {

        if (searcher->test_bit(MERMQ_DOMAIN, MERMQ_GROUP, MERMQ_BIT))
        {
            oyster = clone_object(SEA_OBJECTS+"oyster_shell");
            oyster->move(searcher);
            return ("You don't find any more oysters. Just an empty shell.\n");
        }

        if (searches < oysters) {
            searches++;
            oyster = clone_object(SEA_OBJECTS+"oyster");
            if (searches == lucky) {
                oyster->add_black_pearl();
                searcher->add_prop(PLAYER_I_MERMQ_FOUND_PEARL, 1);
            }
            oyster->move(searcher);
            return "You found an oyster.\n";
        }

        return "You don't find any more oysters. Perhaps you "+
            "should come back later.\n";
    }

    return "Your search reveals nothing special.\n";
}

string query_lucky() { return "Lucky = "+lucky; }
string query_searches() { return "Searches = "+searches; }
string query_oysters() { return "Oysters = "+oysters; }

