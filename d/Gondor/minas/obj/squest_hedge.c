/*
 * The hedge for the Fen Hollen Porter quest.
 *    This hedge is cloned to one of an array of rooms
 *    and will move a brush into TP if searched.
 *
 * /d/Gondor/minas/obj/squest_hedge.c
 *
 * Alto, 27 April 2001
 *
 * Updated 2023-06 - reset the hedge brush status, or
 * else the quest may become blocked.
 *
 */


inherit "/std/object";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/lib/porter_defs.h"
#include "/d/Gondor/bits.h"



#define INNER_MINAS "/d/Gondor/minas"

object brush;
int brush_is_taken = 0;

public string do_search(object actor, string str);
public int get_brush(object actor, int i);

void
create_object()
{
    set_short("hedge");
    set_name("hedge");
    add_name("hedges");
    add_name("_stable_quest_hedge_");
    set_long("This part of the hedge looks slightly trampled. In "
        + "fact, it almost appears as if someone tripped and fell "
        + "into it, crushing the stems near the bottom.\n");

    add_item(({"stems"}), "They appear to be rather crushed near "
        + "the bottom of the hedge.\n");
    add_item(({"bottom"}), "The bottom of the hedge is a obscured by the "
        + "numerous stems that have been crushed recently.\n");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The hedge is rooted firmly in the ground.\n");
    add_prop(OBJ_I_VOLUME,      1000);
    add_prop(OBJ_I_WEIGHT,      1000);

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    enable_reset();
}

public void reset_object()
{
    brush_is_taken = 0;
}

public int
get_brush(object actor, int i)
{

    if ((actor->test_bit("Gondor",
        MTIRITH_PORTER_GROUP,
        MTIRITH_PORTER_BIT)) || brush_is_taken)
    {
        WRITE("Your search reveals nothing special.");
        return 0;
    }

    if (actor->query_prop(QUESTING_FOR_BRUSH))
    {
        WRITE("You find a brush under the stems!");
        brush_is_taken = 1;
        brush = clone_object(INNER_MINAS + "/obj/horse_brush.c");
        brush->move(actor, 1);
        return 1;
    }

    WRITE("There is nothing special about the hedge.");
    return 0;
    
}

public string
do_search(object actor, string str)
{
    if(!str)
        NFN("Search what?");

    switch(str)
    {
        case "hedge" :
            WRITE("You move aside the crushed stems.\n");
            get_brush(TP, 1);
            return "When you release them, the stems return to their "
                + "original position.\n";
     }
     NFN("You don't find any " + str + " to search.");
}


