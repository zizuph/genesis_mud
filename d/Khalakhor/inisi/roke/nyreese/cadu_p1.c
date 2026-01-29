/*
 * cadu_p1.c
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
  set_long("You are on a small winding road leading towards " +
           "the harbour. Surrounding you are large buildings. " +
           "On one of the buildings are a few small balconies.\n");
  
  add_item("building", "It's an ordinary wooden house.\n");
  add_item("balcony", "It looks like it will fall down soon.\n");
  add_item(({"balconys", "balconies", "small balconies"}),
           "They look like they will fall down soon.\n");
  add_item("house","It's built of wood, that has become grey in the sun.\n");
  add_item("houses", "They are the homes of many Cadu families.\n");
  
  add_exit("cadu_p2", "north");
  add_exit("cadu_s1", "south");
}
