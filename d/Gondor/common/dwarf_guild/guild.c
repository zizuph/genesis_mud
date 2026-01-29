/*
 * /d/Gondor/common/dwarf_guild/guild.c
 *
 * This is the central guild cave. You will find the board here.
 *
 * /Mercade, 9 January 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/d/Gondor/common/room";

#include <macros.h>
#include <stdproperties.h>
#include "dwarf.h"

#define BOARD        (DWARVEN_RACE_GUILD_OBJECTS + "board")
#define TEDDYBEAR    (DWARVEN_RACE_GUILD_BEARS + "bear")
#define TEDDYBEAR_ID (DWARVEN_RACE_GUILD_PREFIX  + "bear")
#define WATER        100 /* in ml */

/*
 * Prototype
 */
void reset_room();

void
create_room()
{
    set_short("the central cave of the " + DWARVEN_RACE_GUILD_NAME);
    set_long("This cave is more a momentous hall. You are in the " +
        "central cave of the " + DWARVEN_RACE_GUILD_NAME + ". It is " +
        "ornamented with sculptures and wood-carvings. In the middle of " +
        "the cave is a fountain and next to the pool surrounding the " +
        "fountain is a bulletin board, the board on which members and " +
        "visitors can post notes to discuss matters or stay in touch with " +
        "one another. Several exits lead from and to this cave. To the " +
        "north is the exit of the guild. East you may train. To the west " +
        "you find another bulletin board. The shop is to the southwest and " +
        "it is connected to the pub of the guild to the southeast. Stairs " +
        "lead up and down to adjacent caverns.\n");

#include "cavedesc.h" /* for some nice descriptions. */

    add_item( ({ "pool", "fountain" }),
        "In the middle of the cave is a pool. In that pool there is " +
        "a fountain. The fountain squirts crystal clear water.\n");
    add_item( ({ "sculpture", "sculptures" }),
        "There are severel sculptures of dwarves in this cave. They " +
        "are all hewn out of rock that is imported from other places. At " +
        "least. The stone looks different from the walls and floor of this " +
        "cave.\n");
    add_item( ({ "carving", "wood-carving", "carvings", "wood-carvings" }),
        "The carvings are just ornamental. They depict deeds of heros, " +
        "obviously all dwarves from the past.\n");

    add_item( ({ "stair", "stairs" }),
        "There are stairs that lead down to the sleeping cave of the " +
        "members of the " + DWARVEN_RACE_GUILD_NAME + ". Other stairs " +
        "lead up to a cavern with an altar in it.\n");
    add_item( ({ "altar" }),
        "Looking up the stairs you think you see an altar, but to be " +
        "sure you should go up the stairs and check it out.\n");

    set_noshow_obvious(1);
    add_exit(DWARF_DIR + "common",   "west");
    add_exit(DWARF_DIR + "entrance", "north");
    add_exit(DWARF_DIR + "train",    "east");
    add_exit(DWARF_DIR + "shop",     "southwest");
    add_exit(DWARF_DIR + "pub",      "southeast");
    add_exit(DWARF_DIR + "join",     "up");
    add_exit(DWARF_DIR + "start",    "down", "@@is_member@@");

    add_prop(OBJ_I_CONTAIN_WATER,   -1);
    add_prop(ROOM_I_INSIDE,          1);
    add_prop(ROOM_I_NO_ATTACK,       1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    FIX_EUID;

    clone_object(BOARD)->move(this_object(), 1);

    reset_room();
}

int
is_member()
{
    if (IS_MEMBER(this_player()) || (this_player()->query_wiz_level()))
    {
        return 0;
    }

    write("The members of the " + DWARVEN_RACE_GUILD_NAME + " value their " +
        "privacy. You are not allowed to enter their private chambers.\n");
    return 1;
}

void
reset_room()
{
    if (!present(TEDDYBEAR_ID))
    {
        FIX_EUID;

        clone_object(TEDDYBEAR)->move(TO);
    }
}

int
drink(string str)
{
    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    /* This may look a bit odd, but it allows people to drink both water and
     * from the fountain/pool.
     */
    if (!parse_command(str, ({ }),
        "[crystal] [clear] 'water' [from] [the] [fountain] [pool]") &&
        !parse_command(str, ({ }),
        "[crystal] [clear] [water] [from] [the] 'fountain' / 'pool'"))
    {
        notify_fail("Drink what from where?\n");
        return 0;
    }

    if (!(this_player()->drink_soft(WATER)))
    {
        notify_fail("You are too soaked to enjoy the crystal clear water " +
            "from fountain.\n");
        return 0;
    }

    write("You bend over to the fountain and refresh yourself with a few " +
        "draughts of crystal clear water.\n");
    say(QCTNAME(this_player()) + " bends over to the fountain and " +
        "refreshes " + this_player()->query_objective() + "self with a few " +
        "draughts of crystal clear water.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(drink, "drink");
}
