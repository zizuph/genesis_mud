/*
 * /d/Gondor/mordor/ungol/tower/east11.c
 *
 * This is the ground level of the tower of Cirith Ungol. It isn't very
 * exciting except for the fact that you will hear it if people are walking
 * in the tower withing hearing distance. This room is a secret room where
 * you might find some interesting things.
 *
 * /Mercade, 11 October 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/tower/stdtower";

#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define PLAYER_I_FOUND_HATCH_EAST11 "_player_i_found_hatch_east11"

#define TOWER_TREASURE_CHEST_ID "_treasure_chest_at_cirith_ungol_"
#define TOWER_TREASURE_CHEST    (MORDOR_DIR + "treasure_chest")

#define MINIMUM_AWARENESS_NEEDED 35

/*
 * Prototype
 */
void reset_room();

/*
 * Global variable
 */

/*
 * This function defines the room.
 */
void
create_room()
{
    no_add_items();  /* prevent the addition of add_items in this room */
    make_the_room(); /* including several add_items (and more) :-)     */

    set_name("Ungol tower, first floor");
    add_name( ({ "room" }) );

    set_short("The tower at Cirith ungol, first floor, secret room");
    set_long(BSN(""));

    add_item_stone();
    add_item_wall();
    add_item( ({ "hatch", "trap-door", "trap door", "door" }),
        "@@hatch_description");

    add_prop(OBJ_I_SEARCH_TIME, 10);
    add_prop(OBJ_S_SEARCH_FUN, "search_in_this_room");
    add_prop(OBJ_S_WIZINFO,
        BSN(""));

    reset_room();
}

/*
 * Reset this room if needed.
 */
void
reset_room()
{
    object box = present(TOWER_TREASURE_CHEST_ID, TO);

    FIX_EUID;

    if (!objectp(box))
    {
        box = clone_object(TOWER_TREASURE_CHEST);
        box->add_prop(OBJ_I_HIDE, 25);
        box->move(TO);
    }

    if (!present("coin", box))
    {
        MAKE_MONEY_GC( 5 + random(10))->move(box, 1);
        MAKE_MONEY_SC(15 + random(30))->move(box, 1);
        MAKE_MONEY_CC(25 + random(50))->move(box, 1);
    }
    if (!present( , box))
    {
        clone_object()->move(box, 1);
    }
}

/*
 *
 */
string
hatch_description()
{

}

/*
 *
 */
string
search_in_this_room(object searcher, string str)
{
    return 0;
}
