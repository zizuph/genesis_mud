/*
 * cas_a5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged & Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object c1,c2,c3;

void reset_room();

void
create_room()
{
    INSIDE;
   
    set_short("The Cadu Castle");
    set_long("You are standing in a narrow corridor, with an open " +
             "door leading to the east. As you look into the room " +
             "you see the faint light of candles reflected on the " +
             "stone walls.\n");
   
    add_item("door", "It's open, and it looks like it's stuck.\n");
    add_cmd_item("door", "close",
                 "You try to close the door, but with no success!\n" +
                 "You realise that not even the Balrog of Ib would make it.\n");
    
    add_exit("cas_a1", "north");
    add_exit("cas_a6", "east");
    add_exit("cas_a9", "south");
   
    reset_room();
}

void
reset_room()
{
    if (c1 || c2 || c3) return;
   
    tell_room(TO, "Some evil children arrives.\n");
   
    c1 = clone_object(ROKEDIR + "npc/child");
    c1->equip_me();
    c1->move(TO);
    c2 = clone_object(ROKEDIR + "npc/child");
    c2->equip_me();
    c2->move(TO);
    c3 = clone_object(ROKEDIR + "npc/child");
    c3->equip_me();
    c3->move(TO);

    c1->team_join(c2);
    c1->team_join(c3);
}
