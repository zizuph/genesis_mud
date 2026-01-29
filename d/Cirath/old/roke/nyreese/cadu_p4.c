/*
 * cadu_p4.c
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
    set_short("Small winding road");
    set_long("You are on a small winding road close to the centre of " +
             "Cadu. The crowd is getting thicker and thicker and you " +
             "can hardly move between all the people walking up and " +
             "down the street.\n");
   
    add_item("people", "As you carefully eye the people of Cadu, one " +
             "of them mutters something about strangers destructing the " +
             "moral of the youth.\n");

   add_exit("cadu_q2", "north");
   add_exit("cadu_p3", "south");
}
