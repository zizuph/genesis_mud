/*
 * d6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("plateau");
    set_long("You are on a small plateau high up in the mountains. South " +
             "of you is a path leading down, out of the mountains, and " +
             "north of you is a huge, high cliff with a stair leading up " +
             "to a hole in the mountainside. Around the hole are some " +
             "sculptures that obviously have been crafted directly from " +
             "the mountain itself.\n");

    add_item("stairs", "The stairs leads up to a hole in the mountain.\n");
    add_item("hole", "It is a dark hole, leading into the mountain.\n");
    add_item("sculptures", "They look a little nasty.\n");

    add_exit("c1", "up");
    add_exit("d5", "south");
}
