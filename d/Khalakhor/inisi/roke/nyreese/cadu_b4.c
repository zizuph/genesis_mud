/*
 * cadu_b4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Pier junction");
    set_long("You are standing in the middle of the pier south of Cadu.\n" +
             "To the west a new building has been constructed.\n"+
             "To the north you can see a nice beach and a few people and " +
             "to the south the pier continues until it makes a turn " +
             "to the west. A brand new pier opens to the east.\n");
   
    add_item(({"building", "extension", "pier"}),
             "The building and the rails of the new pier have the "+
             "letters 'G S L' all around them.\n");

    add_exit("cadu_b1", "north");
    add_exit("cadu_b2", "south");
    add_exit("cadu_pier1", "east");
    add_exit("gs_office/entrance", "west");

    BEACH;
}
