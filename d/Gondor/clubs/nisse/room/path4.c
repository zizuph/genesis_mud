/*
 *  /d/Gondor/clubs/nisse/room/path4.c
 *
 *  The path inside the camp of Nisse Ohtar.
 *
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

inherit NISSE_LIB_DIR + "nisse_funcs";

/*
 *  Prototypes
 */
string long_desc();

void
create_gondor()
{
    ::create_gondor();

    set_short("Camp of the Nisse Ohtar");
    set_long(&long_desc());

    sky_add_items();
    add_camp_tells();
    
    add_item(({"hedge", "hawthorn", "hawthorn hedge", "enclosure"}),
        "A broad tall hawthorn hedge extends all around the perimeter " +
        "of the camp, protecting and enclosing the area like a natural " +
        "fort. The prickly thorns help to discourage unwanted intruders.\n");
    add_item(({"clearing", "ground"}),
        "The ground has been cleared of bracken and undergrowth, leaving " +
        "only a carpet of thick green grass.\n");
    add_item(({"brush", "trees"}),
        "Larger trees and brush have been cleared from this area, and only " +
        "a few smaller bushes and trees here and there were kept for " +
        "ornamental purposes.\n");
    add_item(({"appearance", "well-tended appearance"}),
        "Whoever created this camp has taken great care to keep it orderly " +
        "and attractive. You see no garbage or mess. The community here " +
        "apparently abides by its own rule of order.\n");
    add_item("camp",
        "This looks like a more permanent home than a temporary camp, even " +
        "though the residents live in tents.\n");
    add_item(({"bushes", "dark green bushes"}),
        "The dark green bushes arch over the pathway that goes to the " +
        "southwest.\n");
    add_item(({"path", "pathway"}),
        "You lean down and smell the ground briefly. Examining the path, " +
        "you find many footprints. This fact makes you certain that it is " +
        "used quite often.\n");
    add_item(({"footprint", "footprints"}),
        "You notice a variety of footprints, but most of them seem to be " +
        "made by smaller feet.\n");
    add_item(({"tent", "large tent"}),
        "You cannot see any details from here. Maybe you can get closer " +
        "when you follow the path to the west.\n");

    add_exit(NISSE_ROOM_DIR + "o_pool", "southwest", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "path2", "west", 0, 0, 0);
}

/*
 *  Function name: long_desc
 *  Description  : Gives a long description of this room.
 */
string
long_desc()
{
    string long_text =
        "Brush and trees are cleared from this area that is surrounded by " +
        "a tall hawthorn hedge forming a natural enclosure." + sky_desc() +
        " Although situated in the wilderness, the neat and well-tended " +
        "appearance of the tents and clearing suggests the discipline of " +
        "a warrior band. The path turns sharply to the southwest around a " +
        "large tent. Several dark green bushes arch over the path to the " +
        "southwest making the path shady and inviting.\n";

    return long_text;
}

/*
 *  Function name: enter_inv
 *  Description  : It's here just to keep the sky description up to date.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
        sky_add_items();
        start_room_tells();
    }
}
