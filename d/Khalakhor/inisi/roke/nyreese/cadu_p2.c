/*
 * cadu_p2.c
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
   set_short("Small winding road");
   set_long("You are on a small winding road between Cadu and " +
            "the harbour. You are surrounded by large buildings. " +
            "There are lots of people northwest.\n");

   add_item("buildings"," They are rather plain.\n");
            
   add_exit("cadu_p3", "northwest");
   add_exit("cadu_p1", "south");
}
