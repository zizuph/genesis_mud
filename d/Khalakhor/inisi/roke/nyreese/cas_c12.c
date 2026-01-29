/*
 * cas_c12.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

object coward;
int iscoward;

void reset_room();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("This room is in the southeast corner of the castle. This room " +
             "is really kind of nice, except for the black walls. The strange, " +
             "magical light from the ceiling feels soothing and relaxing. Why " +
             "don't you rest yourself for a moment? You see exits to the " +
             "north and to the west. You can also enter a tower to the " +
             "southeast.\n");

    reset_room();

    add_exit("cas_c11", "west");
    add_exit("cas_t34", "southeast");
    add_exit("cas_c8", "north");
}

void
reset_room()
{
    iscoward = 1;
    if (coward)
    {
        coward->remove_object();
        tell_room(TO, "The coward was desintegrated by some divine force.\n");
    }
}

int
assault()
{
    write("You lie down for a short while. You feel very relaxed.\n");
    say(QCTNAME(TP) + " rests for a while.\n");
    if (iscoward)
    {
        TP->catch_msg("You feel your health rising...\n");
        TP->heal_hp(TP->query_max_hp() / 20);
        iscoward = 0;
        coward = clone_object(ROKEDIR + "npc/coward");
        coward->equip_me();
        tell_room(TO, "A coward leaps from the shadows and attacks you!!\n");
        coward->move(TO);
        coward->attack_object(TP);
    }
    return 1;
}

void
init()
{
    ::init();
    add_action(assault, "rest");
}
