/*
 * cadu_a5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged & gresolle */

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
    set_short("Narrow alley");
    set_long("You are in one of Cadu's small alleys.\n"+
             "When you come closer you discover that the group "+
             "of strange people were headed for the small building "+
             "to the south. The alley extends into a road to the "+
             "west.\n");
 
    add_exit("cadu_guild", "south");
    add_exit("cadu_a4"   , "east");
    add_exit("red_r3"    , "west");

    OUTSIDE;
    reset_room();
}
