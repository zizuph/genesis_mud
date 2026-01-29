/*
 * cas_c2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object guard1, guard2, guard3;

void reset_room();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("You have entered this level's guardroom. The floor is " +
             "covered with litter and old, crushed bones that the guards " +
             "have gnawed to pieces. The guards may fancy a lot of things " +
             "but cleaning and dishwashing is not their favourite occupation. " +
             "You see an exit to the west. You might as well use it since this " +
             "place really stinks.\n");

    add_item("litter", "It smells bad.\n");

    INSIDE;
    add_exit("cas_c1", "west");
    reset_room();
}

void
reset_room()
{
    if (guard1 || guard2 || guard3)  /* don't update `til all dead */
        return;

    guard1 = clone_object(ROKEDIR + "npc/guard3.c");
    guard1->equip_me();
    guard2 = clone_object(ROKEDIR + "npc/guard3.c");
    guard2->equip_me();
    guard3 = clone_object(ROKEDIR + "npc/guard3.c");
    guard3->equip_me();
    
    guard1->move(TO);
    guard2->move(TO);
    guard3->move(TO);
}
