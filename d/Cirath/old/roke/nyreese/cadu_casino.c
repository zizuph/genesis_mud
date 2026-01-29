/*
 * cadu_casino.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Main Casino Hall");
   
    set_long("You are standing in the great hall of the Cadu Casino.\n" +
             "There are lots of people running around here and you get the " +
             "feeling that some of them are quite happy while some of them " +
             "are feeling quite miserable. " +
             "To the south you can see a room with a roulette and to the " +
             "north you see a very nice Black Jack table.\n");
   
    add_item("sign","Welcome to the Cadu Casino!\n"+
             "This is the place where YOU can have a fun and pleasant time.\n"+
             "Please try the different games we offer here.\n");
   
    add_cmd_item("sign","read","Welcome to the Cadu Casino!\n"+
                 "This is the place where YOU can have a fun and pleasant "+
                 "time.\nPlease try the different games we offer here.\n");
   
    INSIDE;

    add_exit("cadu_casino2", "south");
    add_exit("cadu_casino1", "north");
    add_exit("cadu_q6",      "west");
}
