/*
 * cadu_p3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object monster;

void
reset_room()
{
    if (monster) return;
    tell_room(TO, "A human arrives.\n");
    monster = clone_object(ROKEDIR + "npc/people");
    monster->equip_me();
    monster->move(TO);
}

void
create_room() 
{
    set_short("Small winding road");
    set_long("You are on a small winding road leading towards " +
             "the Cadu town square. As you move closer to the " +
             "centre of the city, it becomes more and more crowded. " +
             "You'd better watch out for pickpockets!\n");
            
   add_exit("cadu_p4", "north");
   add_exit("cadu_p2", "southeast");
   
   OUTSIDE;

   reset_room();
}
