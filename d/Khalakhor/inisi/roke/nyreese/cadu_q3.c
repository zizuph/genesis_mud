/*
 * cadu_q3.c
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
    set_short("Town square");
    set_long("You are at the town square in Cadu.\n" +
             "High above you can see the ever-shining sun. " +
             "To the east you can see a forge and " +
             "to the south of you is a very big building: " +
             "The famous Cadu library.\n");

    add_exit("cadu_smith", "east");
    add_exit("cadu_q6", "north");
    add_exit("cadu_q5", "northwest");
    add_exit("cadu_q2", "west");
    add_exit("cadu_l" , "south");
}

int
block()
{
    write("The library is net there yet.\n");
    return 1;
}
