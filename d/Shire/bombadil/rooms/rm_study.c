/*
 * Downstairs west hall of Tom's house
 * By Finwe, January 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"
 
inherit HOUSE_BASE;

void
create_house_room()
{
    set_short("A cluttered study");
    set_long("This crowded room is the cluttered study. A large " +
        "desk dominates the room and covered with papers, books " +
        "and other reading material. Bookcases line one wall and " +
        "boxes are stacked in against another wall. This room was " +
        "probably once clean and orderly, but now it looks more " +
        "like a storage room.\n");

    add_item(({"large desk", "desk"}),
        "The desk is large and heavy looking. It sits against the " +
        "west wall under the window. Books and papers are stacked " +
        "and scattered all over the desk.\n");
    add_item(({"papers"}),
        "The papers are stacked on the desk. All kinds of notes " +
        "are scribbled on them and look undecipherable.\n");
    add_item(({"books", "tomes", "reading material"}),
        "They are stacked all over the desk and on the bookcase. " +
        "The books are of all sizes and shape. Some are leather bound " +
        "while others are little more than a group of pages held " +
        "together by some rings.\n");
    add_item(({"bookcases", "bookcase"}),
        "The bookcases are heavy and attached to the south wall. " +
        "They are full of books, papers, and some boxes.\n");
    add_item("boxes",
        "The boxes are of all sizes. They are made of wood and " +
        "are stacked against the north wall beneath the window. They " +
        "are all closed, making the room look more cluttered.\n");
    add_item("chair",
        "It is large and comfortable looking with a high back. It " +
        "is pushed into the desk.\n");

    reset_shire_room();
    add_item(({"north window", "northern window"}), 
        "@@north_up@@\n");
    add_item(({"south window", "southern window"}), 
        "@@south_up@@\n");
    add_item(({"west window", "western window"}), 
        "@@west_up@@\n");

    set_extra_window("@@window_position@@ set into the " +
        "north, south, and west walls.");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
        "@@open_curtains@@");
    num_of_windows=3;

    add_exit(ROOMS_DIR + "rm_bdrm",  "east");
}
void
init()
{
    ::init();

}


void
reset_shire_room()
{
}


