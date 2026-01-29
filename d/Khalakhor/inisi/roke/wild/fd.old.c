/*
 * fd.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

object guard;
object warrior1;
object warrior2;
object warrior3;

void reset_room();

void
create_room()
{
    set_short("Camp");
    set_long("You have entered a warrior camp. There are several small tents" +
             " here. They form a nice pattern to protect the camp from " +
             "intruders. There is a large fire in the middle of the camp and" +
             " just beside the fire there is a larger tent. It is probably " +
             "the leader's tent.\n");

    add_item("tent", "It is made of dirty canvas.\n");
    add_item("fire", "The fire pleasantly heats your skin.\n");

    add_exit("fc", "north");
    add_exit("fb", "northwest");
    add_exit("ff", "west");
    add_exit("tent", "tent", "@@block");
    add_prop(OBJ_I_HAS_FIRE, 1);

    reset_room();
}

int
block()
{
  if (guard && present(guard) && CAN_SEE(guard, TP))
    {
        write("The guard stops you from entering the tent.\n");
        return 1;
    }

    return 0;
}

void
reset_room()
{
    if (!guard)
    {
        guard = clone_object(ROKEDIR + "npc/campguard");
        guard->equip_me();
        guard->move(TO);
    }

    if (!warrior1)
    {
        warrior1 = clone_object(ROKEDIR + "npc/campwarrior");
        warrior1->equip_me();
        warrior1->move(TO);
    }

    if (!warrior2)
    {
        warrior2 = clone_object(ROKEDIR + "npc/campwarrior");
        warrior2->equip_me();
        warrior2->move(TO);
    }

    if (!warrior3)
    {
        warrior3 = clone_object(ROKEDIR + "npc/campwarrior");
        warrior3->equip_me();
        warrior3->move(TO);
    }
}
