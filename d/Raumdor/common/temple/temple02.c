/* Lair of the Khiraa */
#pragma strict_types

#include "defs.h"
inherit TEMPLE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Top of a dark stairwell");
    set_long(
      "You stand in a stairwell with stairs leading down further into this " +
      "dark and sinister temple. The stairs are made of strange dark stone. " +
      "Burning torches line the wall, illuminating the way.\n");
    add_item(({"stairs"}), "They lead down into darkness.\n");
    add_item(({"torches"}), "They give light to the area.\n");
    add_exit(TEMPLE_DIR + "lair3", "down", 0);
    add_exit(TEMPLE_DIR + "temple05", "north", 0);
    clone_object(TEMPLE_OBJ_DIR + "western_door_inner")->move(TO, 1);
}

int
block()
{
    write(
      "A dreadful whisper echoes in your head, saying: Only the servants of " +
      "the Nameless One may descend into the Darkness.\n");
    return 1;
}
