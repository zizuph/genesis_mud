/*
 * /d/Gondor/mordor/ungol/tower/west14.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance.
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/tower/stdtower";

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define BEER_FILE MORDOR_DIR + "obj/orc_beer"
#define WINE_FILE MORDOR_DIR + "obj/orc_wine"

#define MINIMUM_AWARENESS_NEEDED 10

/*
 * Prototypes
 */
void reset_room();

/*
 * Global variables
 */
object orc; /* mean orcs guard the tower */
object sack; /* the sack of flour. */

/*
 * This function defines the room.
 */
void
create_room()
{
    make_the_room(); /* including several add_items :-) */

    set_name("Ungol tower, first floor");
    add_name( ({ "room", "kitchen", "storage" }) );

    set_short("The tower at Cirith ungol, first floor, kitchen");
    set_long(BSN("You are at the first floor in the tower at Cirtih Ungol. " +
        "It is dimly lit with torches flaring in brackets on the walls. " +
        "This room in the tower is used for cooking and storage. Here you " +
        "see sacks with all kinds of things used to prepare meals and " +
        "shelves and cupboards with more stuff that the orcs in use for " +
        "their everyday life. You also see some ashes from fires."));

    add_item( ({ "shelf", "shelves" }),
        BSN("The shelves are made of wood and they are very messy. On them " +
        "you see several items that orc use to prepare food."));
    add_item( ({ "cupboard", "cupboards" }),
        BSN("In the cupboards you find several things that orcs use in " +
        "their everyday life. You don't find them particularly interesting."));
    add_item( ({ "sack", "sacks" }),
        BSN("There are several sacks here, willed with all kinds of " +
        "food-stuff and other nutritious or less nutritious things."));
    add_item( ({ "ashes", "pile", "piles", "fire", "fires" }),
        BSN("You see some piles of ashes on places where orcs have " +
        "prepared meals. Glancing at them will not yield much information " +
        "though."));
    add_item( ({ "bone", "bones" }),
         BSN("It are some small bones. You cannot tell what kind of " +
         "creature they belonged to."));

    add_prop(OBJ_I_SEARCH_TIME, 10);
    add_prop(OBJ_S_SEARCH_FUN, "search_in_this_room");
    add_prop(OBJ_S_WIZINFO,
        BSN("This tower has to nice features. If you walk here, other " +
        "people that are within hearing distance will hear you walking. " +
        "The stairs are developed like a so-called winding staircase. If " +
        "you go northeast, you descend the stairs, if you go northwest you " +
        "up. In this particular room you might find some flour in one of " +
        "sacks in this kitchen."));

    add_exit(CIRITH_DIR + "west13", "north");

    reset_room();
}

/*
 * A new orc will be created if the other one dies.
 */
void
reset_room()
{
    if (!objectp(orc))
    {
        orc = make_orc(100, 1); /* give this orc a whip */
    }
}

/*
 * If you try to search in this room.
 */
string
search_in_this_room(object searcher, string str)
{
    object alive_orc = query_living_orc();

    if (!strlen(str))
    {
        NFN("What do you want to search?");
        return 0;
    }

    if ((str == "fire") || (str == "fires"))
    {
        return BSN("How can you search a burning fire, not that there is " +
            "one in this room.");
    }

    if (objectp(alive_orc))
    {
        /*
         * I am not completely fond of this implementation, but what the
         * heck. No mortal will probably complain about it and besides
         * myself no-one will probably ever read this text ;-)
         */
        return BSN("The " + orc->query_nonmet_name() + " does not like you " +
            "to mess with the inventory of this kitchen and prevents you " +
            "from searching that.");
    }

    FIX_EUID;

    if ((str == "ashes") || (str == "pile") || (str == "pile of ashes"))
    {
        return BSN("Searching the ashes does not yield much information. " +
            "You discover that the orcs must have eaten flesh, for you " +
            "see some bones. The rest is just ashes, all ashes and " +
            "nothing but ashes.");
    }

    if ((str == "shelf") || (str == "shelves"))
    {
        if (!present("wine", TO))
        {
            clone_object(WINE_FILE)->move(TO);
            clone_object(WINE_FILE)->move(TO);
        }
        if (!present("beer", TO))
        {
            clone_object(BEER_FILE)->move(TO);
            clone_object(BEER_FILE)->move(TO);
            clone_object(BEER_FILE)->move(TO);
        }

        return BSN("One the shelves in this kitchen you find some a few " +
            "orkish beers and a couple of bottles of wine.");
    }

    if ((str == "sack") || (str == "sacks"))
    {
        if (searcher->query_skill(SS_AWARENESS) <= MINIMUM_AWARENESS_NEEDED)
        {
            return BSN("Searching the sacks reveals that they are heavy and " +
                "big. As to the contents of the sack you cannot determine " +
                "much.");
        }

        if (!objectp(sack))
        {
            sack = clone_object(SACK_FILE);
            sack->move(this_object());
        }

        return BSN("One of the sacks you search contains flour. Since you " +
            "are in a room that looks like an orc kitchen, it might not be " +
            "very nutritious, but then, what can you expect in an orc " +
            "kitchen.");
    }

    return 0;
}
