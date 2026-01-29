/*
 * strange.c
 *
 * Used in npc/car_spirit.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "std/object";

#include <macros.h>

string
query_recover()
{
    return MASTER;
}

void
create_object()
{
    set_name("stick");
    add_name("he-he-quest-thingy");
    set_short("wooden stick");
    set_adj("wooden");
    set_long("A mysterious wooden stick.\n");
}
