/*
   This is a room outside the cottage. Mortricia 920721
 */
inherit "/std/room.c";
#define HOME_DIR "/d/Terel/common/forest/cottage/"
#define FOR_DIR "/d/Terel/common/forest/"
#include <stdproperties.h>
#include <macros.h>

create_room()
{
    set_short("In front of cottage");
    set_long(break_string(
        "You are standing outside a black cottage. The roof is hidden " +
        "under a deep layer of snow. The cottage must be occupied by " +
        "someone since smoke is coming from the chimney. You can visit " +
        "the cottage by going north.\n", 70));

    add_item(({"cottage"}), "The cottage has been painted black.\n");
    add_item(({"roof"}), "You cannot see it because of all the snow.\n");
    add_item(({"chimney"}), break_string("It's an ordinary chimney. But " +
        "the smoke coming from it forms a strange pattern.\n", 70));
    add_item(({"smoke"}), break_string("The cloud of smoke forms something " +
        "that resembles a toad. Very strange, indeed!\n", 70));

    add_prop(ROOM_I_INSIDE, 0);

    add_exit(FOR_DIR + "forest6", "east", 0);
    add_exit(HOME_DIR + "cottage1", "north", 0);
}
