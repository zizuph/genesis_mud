/*
 * cadu_stable.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

inherit ROKEDIR + "lib/roomcode";

#include <macros.h>

void
create_room()
{
    init_sp_quest();

    set_short("The stable of the castle\n");
	   
    set_long("You find yourself standing just outside a huge stable.\n" +
             "On the other side of a small forest is a city, and above " +
             "you the castle of Cadu towers high up in the sky. As " +
             "you look into the stable you notice a hole in the ceiling " +
             "with a slippery pole leading upwards in the castle.\n");

    add_cmd_item("pole", "climb", "@@climbpole");
    add_cmd_item("pole", "clean", "@@cleanpole");
    add_item("pole", "The pole is smeared with grease.\n");
    add_item("ceiling", "It's a huge hole in the ceiling.\n");
  
    add_exit("cadu_a7", "southeast");
}

int
cleanpole()
{
    TP->catch_msg("You try to remove the grease, but by doing this you " +
                  "have only polished the pole and made it more slippery.\n");
    return 1;
}

int
climbpole()
{
    say(QCTNAME(TP) + " tries to climb up the pole but fails" +
	" and falls down again.\n");

    TP->catch_msg("You try to climb up the pole but fall down and" +
                  " hit the ground! Ouch! That hurt!\n");

    TP->heal_hp(-20);

    return 1;
}

void
init()
{
    ::init();
    initrc();
}
