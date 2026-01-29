/*
 * cadu_q7.c
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
    set_short("Town square");
    set_long("You are at the town square in Cadu.\n" +
             "To the north you spot the post office. " +
             "Surrounding you is a small group of locals, " +
             "shopping in the small sheds on the square.\n");
   
   
    add_item("locals", "They hardly notice you, much too preoccupied " +
             "with their own business as they are.\n");
    add_item("sheds", "They are quite small and spartanic.\n");
    add_item("post office", "The post office is to the north!\n");

    add_exit("cadu_q5", "southeast");
    add_exit("cadu_q4", "south");
    add_exit("cadu_a3", "north");
    add_exit("cadu_q8", "east");
}
