/*
 * orc_road3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
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
    set_long("You are standing inside a dark forest. To your south you " +
             "think that perhaps there is some water, the sea or a lake. " +
             "The shrubberies are rather thick here, and the only way " +
             "out of here is the way you came, to the west.\n");

    add_exit("orc_road2", "west");

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
