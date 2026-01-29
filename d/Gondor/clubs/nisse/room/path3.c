/*
 *  /d/Gondor/clubs/nisse/room/path3.c
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
string	long_desc();
int	read_sign(string str);

void
create_gondor()
{
    ::create_gondor();

    set_short("Camp of the Nisse Ohtar");

    set_long(&long_desc());

    sky_add_items();
    add_camp_tells();
    add_tent_tells();

    add_item(({"path", "pathway"}),
        "You lean down and smell the ground briefly. Examining the path, " +
        "you find many footprints. This fact makes you certain that it " +
        "is used quite often.\n");
    add_item(({"footprint", "footprints"}),
        "You notice a variety of footprints, but most of them seem to be " +
        "made by smaller feet.\n");
    add_item(({"willow", "willow tree", "old willow tree",
        "large willow tree", "great willow tree"}), "The great old willow " +
        "tree sways gracefully with every passing breeze.\n");
    add_item(({"large tent", "east tent"}),
        "You cannot see more than the brown wall and painted white top of " +
        "the tent from here. Maybe you can get closer when you follow " +
        "the path to the east.\n");
    add_item(({"small tent", "smaller tent", "west tent"}),
        "You look closer at the small tent west from here. It seems to be " +
        "a frequented place. A wooden sign has been hammered down at the " +
        "entrance.\n");
    add_item(({"tent", "tents"}),
        "There are two tents nearby. You can look at the small tent to the " +
        "west or the large tent to the east.\n");
    add_item(({"sign"}),
        "Post office of the Nisse Ohtar.\n");
    add_item(({"hedge", "hawthorn", "hawthorn hedge", "enclosure"}),
        "A broad tall hawthorn hedge extends all around the perimeter of " +
        "the camp, protecting and enclosing the area like a natural fort. " +
        "The prickly thorns help to discourage unwanted intruders.\n");
    add_item(({"clearing", "ground"}),
        "The ground has been cleared of bracken and tree roots, leaving " +
        "only a carpet of thick green grass.\n");
    add_item(({"brush", "underbrush", "trees",  "bushes"}),
        "The brush has been neatly clipped back along the pathway, where " +
        "there are some low bushes planted for ornamental purposes. Deep " +
        "green grass flourishes where the trees have been cleared.\n");
    add_item(({"appearance", "well-tended appearance"}),
        "Whoever created this camp has taken great care to keep it orderly " +
        "and attractive. You see no garbage or mess. The community here " +
        "apparently abides by its own rule of order.\n");
    add_item("camp",
        "This looks like a more permanent home than a temporary camp, even " +
        "though the residents live in tents.\n");
    add_item(({"tree", "trees"}),
        "Some trees have been planted for ornamentation purposes. Through " +
        "an arch created by two young cypress trees to the southeast, you " +
        "can glimpse a great old willow tree gracefully swaying in the " +
        "breeze.\n");
    add_item(({"cypress trees", "young cypress trees", "cypress tree",
        "bower"}), "There are a pair of tall young cypress trees on either " +
        "side of the path to the southeast. Their top limbs arch over the " +
        "path to join each other and entwine like two dancers.\n");

    add_exit(NISSE_ROOM_DIR + "o_pool", "southeast", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "path2", "east", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "post", "west", 0, 0, 0);
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
        "a warrior band. The path turns sharply to the southeast around " +
        "a large tent. Just to the west stands a smaller tent. Through a " +
        "bower of young cypress trees that bend over the path, you can " +
        "glimpse a great willow tree whose branches sway gently in the " +
        "breeze.\n";

    return long_text;
}

/*
 *  Function name: read_sign
 *  Description  : Reads a text on the sign.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
read_sign(string str)
{
    if (str != "sign")
    {
        notify_fail("Read what?\n", 0);
        return 0;
    }

    write("The sign reads:  Post office of the Nisse Ohtar.\n");
    return 1;
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

void
init()
{
    ::init();

    add_action(&read_sign(), "read");
}
