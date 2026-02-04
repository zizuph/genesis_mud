/*
   This is a small room in the witch cottage. Mortricia 920721
 */
inherit "/std/room.c";
#define HOME_DIR "/d/Terel/common/forest/cottage/"
#include <stdproperties.h>
#include <macros.h>

reset_room()
{
    object toad;
    if (present("toad"))
        return;
    toad = clone_object(HOME_DIR + "toad");
    toad -> move(this_object());
}

create_room()
{
    set_short("Cottage room");
    set_long(break_string(
        "You are inside a small storage room in the northern part of " +
        "the cottage. The floor is slimy. South from here is a door.\n", 70));

    add_item(({"wall", "walls"}), "The walls are all black.\n");
    add_item(({"slime"}), "Something must be real slimy in here!\n");

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}
