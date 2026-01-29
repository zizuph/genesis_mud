/*
 * cadu_a2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("Alley");
    set_long("You are in one of Cadu's small alleys.\n" +
             "To your south is the big town square, and in " +
             "the north the alley continues to the outermost " +
             "parts of the city. There is a yellow sign here.\n");
    add_exit("cadu_a6", "north");
    add_exit("cadu_q8", "south");
    add_exit("cadu_a3", "west");
   
    add_item("sign", "It's yellow. The blue letters on it form the " +
             "words 'Post Office. 100 m'. It points to the west.\n");
   
    add_cmd_item("sign", "read", "Post Office. 100 m\n");
}
