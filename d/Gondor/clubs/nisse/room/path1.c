/*
 *  /d/Gondor/clubs/nisse/room/path1.c
 *
 *  The path inside the camp of Nisse Ohtar.
 *
 *  Deagol, March 2003
 *  Tigerlily, added a few descriptions April, 2003
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
string  long_desc();

void
create_gondor()
{
    ::create_gondor();

    set_short("Camp of the Nisse Ohtar");
    set_long(&long_desc());

    sky_add_items();
    add_camp_tells();
    add_tent_tells();

    add_item(({"hedge", "hawthorn", "hawthorn hedge", "enclosure"}),
        "A broad tall hawthorn hedge extends all around the perimeter " +
        "of the camp, protecting and enclosing the area like a natural " +
        "fort. The prickly thorns help to discourage unwanted intruders.\n");
    add_item(({"clearing", "ground"}),
        "The ground has been cleared of bracken and undergrowth, leaving " +
        "only a carpet of thick green grass.\n");
    add_item(({"brush", "underbrush", "trees",  "bushes"}),
        "The brush has been neatly clipped back along the pathway, " +
        "where there are some low bushes planted for ornamental " +
        "purposes. Deep green grass flourishes where the trees " +
        "have been cleared.\n");
    add_item(({"path", "broad path"}),
        "The path that is the main throughfare in the camp runs straight " +
        "north and south.  Bright-coloured stones have been placed at the " +
        "edge as decoration.\n");
    add_item(({"appearance", "well-tended appearance"}),
        "Whoever created this camp has taken great care to keep it orderly " +
        "and attractive. You see no garbage or mess. The community here " +
        "apparently abides by its own rule of order.\n");
    add_item(({"tents", "two tents"}),
        "There are two tents standing on either side of the path. You can " +
        "examine the east tent or the west tent. There is also a larger " +
        "tent farther to the south.\n");
    add_item("east tent",
        "Aromas are coming from the east tent that make your mouth water, " +
        "and judging from the sounds emanating from that direction, this " +
        "is a busy tavern.\n");
    add_item("west tent",
        "There are many empty crates stacked neatly by the entrance, " +
        "suggesting that this is where supplies are stored. There is a " +
        "flap made from hide tied open as an entrance.\n");
    add_item(({"crates", "empty crates"}),
        "The wooden crates have been opened and stacked neatly along the " +
        "wall. They look as though they may have contained various " +
        "supplies.\n");
    add_item(({"larger tent", "south tent", "tent to the south"}),
        "A larger tent stands further south, but you can't make out the " +
        "details on it from here.\n");
    add_item("tent",
        "There are three tents. You can look at the east tent, the west " +
        "tent, or the larger tent to the south.\n");
    add_item("camp",
        "This looks like a more permanent home than a temporary camp, " +
        "even though the residents live in tents.\n");

    add_exit(NISSE_ROOM_DIR + "entrance", "north", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "path2", "south", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "tavern", "east", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "shop", "west", 0, 0, 0);
}

/*
 *  Function name: long_desc
 *  Description  : Gives a long description of this room. It depends on
 *                 fact if a player is the Nisse member or not.
 */
string
long_desc()
{
    string text =
        "Brush and trees are cleared from this area that is surrounded " +
        "by a tall hawthorn hedge forming a natural enclosure." +
        sky_desc() + " Although situated in the wilderness, the neat and " +
        "well-tended appearance of the tents and clearing suggests the " +
        "discipline of a warrior band. There are two tents standing to the " +
        "east and west that have open entrances on this side. The path " +
        "leads out of the camp to the north and continues south where " +
        "there stands another larger tent.\n";

    return text;
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
