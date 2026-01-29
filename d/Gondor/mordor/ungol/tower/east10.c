/*
 * /d/Gondor/mordor/ungol/tower/east10.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance.
 *
 * This particular room is a dead end in a 'closet' next to the hidden room.
 * It is designed to make the mortals wonder and search this room thoroughly.
 * However, they will not find anything in this room. *cackle*
 *
 * /Mercade, 23 October 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/tower/stdtower";

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define MINIMUM_AWARENESS_NEEDED 25

/*
 * This function defines the room.
 */
void
create_room()
{
    make_torch();    /* get a torch, skip the add_item one    */
    no_add_items();  /* to prevent all add_items in this room */
    make_the_room(); /* including several add_items :-)       */

    set_name("Ungol tower, first floor");
    add_name( ({ "room", "passage", "closet", "large closet" }) );

    set_short("The tower at Cirith ungol, first floor, passage");
    set_long(BSN("You are at the first floor in the tower at Cirith Ungol. " +
        "At first glance there is nothing special in this room. This is a " +
        "dead end. Frankly, this room looks like a large closet."));

    add_item( ({ "south wall", "wall", "walls" }),
        BSN("The walls of this tower are make of stone and they are quite " +
        "thick. They are quite smooth, making the the rooms sound hollow."));
    add_item( ({ "ground", "floor" }),
        BSN("The floor is made of dark stones and is rather dusty."));
    add_item("south wall",
        BSN("The south wall is definitely located at the south end of this " +
        "room. At first sight it is no different from the other walls."));
    add_item( ({ "stone", "stones" }),
        BSN("Looking closely at the stones you see that even though they " +
        "are all shaped capriciously they are carved in such a way that " +
        "they fit exactly without cement between them."));

    add_prop(OBJ_I_SEARCH_TIME, 10);
    add_prop(OBJ_S_SEARCH_FUN, "search_in_this_room");

    make_door(CIRITH_DIR + "centre10", "west", 1);
}

/*
 * Add some dummy commands.
 */
void
init()
{
    ::init();

    add_action("do_try_to_move", "move");
    add_action("do_try_to_move", "push");
    add_action("do_try_to_move", "pull");
    add_action("do_try_to_move", "press");
}

/*
 * These commands don't do a thing... *grin*
 */
int
do_try_to_move(string str)
{
    if ((str != "stone") && (str != "stones") &&
        (str != "wall") && (str != "walls") &&
        (str != "dark stone") && (str != "darker stone"))
    {
        NFN0(CAP(query_verb()) + " what?");
    }

    switch(random(3))
    {
    case 0:
        NFN0("You " + query_verb() + " the " + str + ", without effect.");
    case 1:
        NFN0("You " + query_verb() + " the " + str + ", but nothing happens.");
    case 2:
    default:
        NFN0("In vain you try to " + query_verb() + " the " + str + ".");
    }

    /* should never happen */
    return 0;
}

/*
 * Called if someone searches here. Nothing can be found in this room, but
 * the texts are composed so that he will remain curious and maybe try to
 * find something here after all.. *cackle*
 */
string
search_in_this_room(object searcher, string str)
{
    if (searcher->query_skill(SS_AWARENESS) < MINIMUM_AWARENESS_NEEDED)
    {
        return BSN("You are not skilled enough in the art of searching to " +
            "find anything in this room.");
    }

    if (str == "here")
    {
        return BSN("You search the room but do not find anything that is " +
            "peculiar. Searching specific objects might yield more " +
            "information.");
    }

    if ((str == "floor") || (str == "ground"))
    {
        return BSN("Searching the floor does not tell you anything but the " +
            "fact that it is very dusty. While searching you destroyed all " +
            "footprints on the floor that might have helped you. Next time " +
            "you should be more careful.");
    }

    if ((str == "wall") || (str == "walls"))
    {
        return BSN("Just at the moment you want to give up searching the " +
            "walls in this room, something catches your eye. One of the " +
            "stones in the south wall is slightly darker than the others " +
            "and you don't believe that is caused by the flickering of the " +
            "light in this room.");
    }

    if (str == "south wall")
    {
        return BSN("The south wall is made of the same stones as the rest " +
            "of this dreadful tower. One of the stones in the south wall " +
            "is definitely other than the other stones that you see here " +
            "It has a different pattern and is also darker.");
    }

    if ((str == "stone") || (str == "stones"))
    {
        return BSN("The stones in the walls, the ceiling and the floor are " +
            "all alike, dark and smooth. One of the stones in the south " +
            "attracts your attention for it is hue is a little darker than " +
            "the other stones.");
    }

    if ((str == "dark stone") || (str == "darker stone"))
    {
        return BSN("All that fuss about one single stone that is slightly " +
            "darker than the other stones in this wall. However, it true " +
            "that this stone was probably added to the wall later. Also " +
            "is doesn't fit in the wall that well. It might hide a button " +
            "or a lever behind it.");
    }

    return 0;
}
