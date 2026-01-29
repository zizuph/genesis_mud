/* Created by Lucas on June 1, 1996 */
/* Amended - Wisk 6/5/97 */
#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <macros.h>

void
create_room()
{
    set_short("Playerarch private meeting chambers");
    set_long("This is where the Arch of Players and his cabinet meet " +
      "to discuss important issues. The room is an elegant ellipse " +
      "enclosed by an enormous glass dome. Only the sky above is visible " +
      "outside. A rather large table rests in the middle of the room, " +
      "with a number of comfortable looking chairs surrounding it. "+
      "A small portal in the south wall leads to the Sparkle office.\n");

    add_item(({"dome","glass dome","glass"}),
      "The glass dome is nearly invisible, leaving the " +
      "impression that you are not really inside.\n");
    add_item("sky","The bright, neverending daylight of the toroid's sun " +
      "shines down through the dome.\n");
    add_item("table", "The beautiful table is made entirely of " +
      "polished jade. Members of the Playerarch sit at " +
      "this table in meeting.\n");
    add_item(({"chair","chairs"}),
      "The chairs are made of jade like the table, and the smooth " +
      "contours look as though they would fit your body nicely.\n");
    add_item(({"portal"}),
      "This portal leads to the office in Sparkle.\n");

    add_exit("/d/Genesis/start/human/town/aop_office", "portal");

    setuid();
    seteuid(getuid());

    /* Removed board after merging with player board.
    clone_object("/w/postmaster/private/arch_boards/aop_board")->move(this_object(), 1);
     */
}

int
sit()
{
    write("You take a seat at the table.\n");
    say(QCTNAME(this_player()) + " takes a seat.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(sit, "sit");
}
