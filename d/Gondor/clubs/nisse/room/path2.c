/*
 *  /d/Gondor/clubs/nisse/room/path2.c
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
    add_tent_tells();
    
    add_item(({"hedge", "hawthorn", "hawthorn hedge", "enclosure"}),
        "A broad tall hawthorn hedge extends all around the perimeter " +
        "of the camp, protecting and enclosing the area like a natural " +
        "fort. The prickly thorns help to discourage unwanted intruders.\n");
    add_item(({"clearing", "ground"}),
        "The ground has been cleared of bracken and undergrowth, leaving " +
        "only a carpet of thick green grass.\n");
    add_item(({"brush", "underbrush", "trees"}),
        "The brush has been neatly clipped back along the pathway, where " +
        "there are some low bushes planted for ornamental purposes. Deep " +
        "green grass flourishes where the trees have been cleared.\n");
    add_item(({"path", "broad path"}),
        "The path that is the main throughfare in the camp branches here " +
        "to the east and west. There is a large tent just to the south.\n");
    add_item(({"appearance", "well-tended appearance"}),
        "Whoever created this camp has taken great care to keep it orderly " +
        "and attractive. You see no garbage or mess. The community here " +
        "apparently abides by its own rule of order.\n");
    add_item("tents",
        "There is a large tent just to the south, and two smaller tents " +
        "are farther to the north standing on either side of the path.\n");
    add_item(({"tent", "large tent"}),
        "You look closer at the large tent. The tent before you, though " +
        "obviously worn, is in perfect condition, and the surface has been " +
        "adorned with stone runes. This looks like the tent of a warrior. " +
        "A round hide flap is draped over the entrance to the tent.\n");
    add_item(({"stone", "stones", "rune stones"}),
        "The stones are all very similar in shape and size but each one " +
        "has a different rune symbol carved into it.\n");
    add_item(({"rune", "runes"}),
        "The runes do not form any particular words or phrases but rather " +
        "seem to be a collection of all the various rune letters.\n");
    add_item("camp",
        "This looks like a more permanent home than a temporary camp, " +
        "even though the residents live in tents.\n");

    add_exit(NISSE_ROOM_DIR + "path1", "north", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "path3", "west", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "path4", "east", 0, 0, 0);
    add_exit(NISSE_ROOM_DIR + "estiu_tent", "south", 0, 0, 0);
}

/*
 *  Function name: read_runes
 *  Description  : There are runes on the tent south of here, let the players
 *                 read them.
 *  Arguments    : string str - as entered by the player
 *  Returns      : 0/1
 */
int
read_runes(string str)
{
    if (str != "runes" && str != "runes on tent")
    {
        notify_fail("Read what?", 0);
        return 0;
    }

    write("The runes do not form any particular words or phrases but " +
        "rather seem to be a collection of all the various rune letters.\n");
    return 1;
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
        "a tall hawthorn hedge forming a natural enclosure." +
        sky_desc() + " Although situated in the wilderness, the neat and " +
        "well-tended appearance of the tents and clearing suggests the " +
        "discipline of a warrior band. The path branches to the east and " +
        "west here before meeting an entrance to a large tent standing " +
        "just to the south.\n";

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

void
init()
{
    ::init();

    add_action(read_runes, "read");
}
