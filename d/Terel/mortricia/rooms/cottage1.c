/*
   This is a cottage, suitable for a witch. Mortricia 920720
 */
inherit "/std/room.c";
#define HOME_DIR "/d/Terel/common/forest/cottage/"
#include <stdproperties.h>
#include <macros.h>


reset_room()
{
    object witch;
    if (present("witch"))
        return;
    witch = clone_object(HOME_DIR + "witch");
    witch -> move(this_object());
}

create_room()
{
    object pot, door, key;

    set_short("Cottage");
    set_long(break_string(
        "You are inside a cottage. Most things here are black. Next " +
        "to the stove, there is a big iron pot. There is a door in the " +
        "northern wall, which probably leads to another room.\n", 70));

    add_item(({"wall", "walls"}), "The walls are all black.\n");
    add_item(({"stove"}), "It's a huge iron stove, and it's still warm.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(HOME_DIR + "outs_cott", "south", 0);

    pot = clone_object(HOME_DIR + "pot");
    pot -> move(this_object());

    door = clone_object(HOME_DIR + "black_door");
    door -> move(this_object());

    key = clone_object(HOME_DIR + "black_key");
    key -> set_key(time());
    door -> set_key(key -> query_key());
    key -> move(this_object());

    reset_room();
}
