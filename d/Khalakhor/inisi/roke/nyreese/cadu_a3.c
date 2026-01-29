/*
 * cadu_a3.c
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
             "To your south is the big town square.\n" +
             "In the north is a huge stone building, with a " +
             "yellow sign attached to its front.\n");
   
    add_item("sign", "It says: Cadu Post Office.\n");
    add_cmd_item("sign", "read", "It says: Cadu Post Office.\n");
   
    add_exit("cadu_pos", "north");
    add_exit("cadu_q7" , "south");
    add_exit("cadu_a4" , "west");
    add_exit("cadu_a2" , "east");
}
