/*
 * d5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("end of path");
    set_long("This is the end of the path. North of you is a small plateau " +
             "and north of the plateau you see a huge, steep cliff, with " +
             "a strange building attached to its side. To the east the path " +
             "leads back to the more civilized areas of Nyreese, and south and " +
             "west are thick bushes.\n");

    add_item("cliff",
             "The cliff has a strange building attached to its front.\n");
    add_item("building", "The building looks like some kind of temple.\n");
    add_item(({"bush", "bushes"}), "The bushes are very thick.\n");
    add_item("plateau", "The plateau is, well, just a plateau.\n");

    add_exit("d6", "north");
    add_exit("d3", "east");
}
