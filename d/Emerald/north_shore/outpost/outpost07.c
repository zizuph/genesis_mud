/*
 *  /d/Emerald/north_shore/outpost/outpost07.c
 *
 *  This area was originally created by Mhyrkhaan in November of
 *  1998 and then put on hold. That wizard has since left the
 *  Emerald domain, and so I have decided to put his work to some
 *  use as a small killing area to give some small satisfaction
 *  to players who value that sort of thing. The descriptions
 *  and items have been updated by Gorboth.
 *
 *  Update August 2003 (Gorboth)
 */
#pragma strict_types

#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;


/*
 * Function name:    create_outpost_inside_room
 * Description  :    set up the room with annoying noises
 */
public void
create_outpost_inside_room()
{
    set_short("in a kitchen within an outpost complex");
    set_em_long("Heat fills this room, where the food for the soldiers"
      + " has been prepared on a daily basis. A large fireplace is"
      + " set in the western wall. A long table in the center of"
      + " the room is filled with bowls and utensils used for the"
      + " preparation of food. Barrels and crates line the northern"
      + " wall. A corridor leads out of the chamber to the east.\n");

    add_item( ({ "heat", "fire", "flame", "flames" }),
        "Flames leap high in the fireplace, where a large fire burns,"
      + " sending smoke up the chimney.\n");
    add_item( ({ "smoke", "chimney" }),
        "Smoke is travelling up the chimney due to the fire which"
      + " burns in the fireplace.\n");
    add_item( ({ "fireplace", "fire place", "large fireplace",
                 "western wall", "west wall" }),
        "This fireplace is larger than most, and looks to have been"
      + " intended to serve as a stove for the cooking of meat and"
      + " other foods. A fire burns brighly within it.\n");
    add_item( ({ "table", "long table" }),
        "The table is long, obviously being intended to serve as"
      + " a counter and work station for the cook. It is crowded"
      + " with many bowls and utensils.\n");
    add_item( ({ "bowl", "bowls", "utensils", "untensil",
                 "knife", "knives", "spoon", "spoons" }),
        "Bowls, knives, spoons, and other such things are piled"
      + " on the top of the table. It does not look as if many of"
      + " them have been washed recently.\n");
    add_item( ({ "barrel", "barrels", "crate", "crates",
                 "barrels and crates", "northern wall",
                 "north wall", "supplies", "food", "stuffs",
                 "food stuffs", "foodstuffs" }),
        "The wall to the north contains crates which are most likely"
      + " filled with food stuffs and other supplies needed for"
      + " the cooking which takes place here.\n");

    add_indoor_items();

    add_exit("outpost02" , "east");
} /* create_outpost_inside_room */
