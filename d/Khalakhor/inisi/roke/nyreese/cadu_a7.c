/*
 * cadu_a7.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Small alley");
    set_long("You are in one of Cadu's small alleys.\n" +
             "To your south is the big town square and to the northwest, " +
             "over the treetops, you see a huge castle, made of grey stone, " +
             "with polished copper roofs that shine in the bright sun.\n");
   
    add_exit("cadu_stable", "northwest");
    add_exit("cadu_a6", "south");
    add_exit(WILDDIR + "f1", "northeast");
}
