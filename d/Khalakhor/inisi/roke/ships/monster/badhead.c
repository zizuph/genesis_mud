/*
 * badhead.c
 *
 * Used in ships/monster/hydra.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/leftover";

void
create_leftover()
{
    ::create_leftover();

    simple_names = 0;

    set_short("massacred hydra skull");
    add_name("skull");
    add_name("badhydrahead");
    set_adj("massacred");
    add_adj("hydra");
    set_long("This is a massacred head from a hydra.\n");
}
