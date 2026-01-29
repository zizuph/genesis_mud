/*
 * orc_road3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Updated and added new exit to pth to new Golbar camp, Treacher 08/2021
 */

/* Gresolle 1992       */
/*Knife added by Ged 93*/

#pragma strict_types

inherit "/std/room";

#include "defs.h"

object knife;
object well;

void reset_room ();

void
create_room ()
{
    set_short("in the forest");
    set_long("You are standing inside a dark forest, where the path ends at "+
             "a wishing well. To your south you think that perhaps there is " +
             "some water, the sea or a lake. The shrubberies are rather thick " +
             "here, seemingly blocking going any further to the east. The " +
             "only way out of here is the path to the west.\n");

    add_item(({"forest", "dark forest", "vegetation"}),
             "The vegetation in the forest is dark and thick, making it difficult "+
             "to see far outside the path. At the end of the path there is a " +
             "thick shrubbery that strikes you as a little odd.\n");
    add_item("path",
             "The path windles in from the west and ends here at the " +
             "wishing well.\n");
    add_item(({"shrubberies", "thick shrubberies", "shrubbery", "thick shrubbery"}),
             "These are really thick shrubberies! But as you scour through the " +
             "branches you notice that someone has cleared a small opening " +
             "and you can see a small trampled path on the other side.\n");
    add_item(({"opening", "small opening", "trampled path", "small path"}),
             "Someone has cleared an opening in the thick shrubberies and trampled up a small "+
             "path leading east.\n");
        
    add_exit("orc_road2", "west");
    add_exit(CAMP + "room/path-sw-0", "east", 0, 0, 1);

    reset_room();
}

void
reset_room ()
{
  if (!objectp(well)) {
    well = clone_object(ROKEDIR + "obj/wishingwell");
    well->move(TO);
  }
  else
    well->reset_well();
  
  if ((knife && !present(knife, TO)) || !knife) {
    knife = clone_object(ROKEDIR + "wep/orc_knife");
    knife->move(TO);
  }
}
