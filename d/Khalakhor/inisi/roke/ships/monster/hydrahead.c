/*
 * hydrahead.c
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

    set_short("hydra head");
    set_name("head");
    add_name("hydrahuvve");

    set_adj("hydra");
    set_long("This is a head from a green hydra.\n");
}
