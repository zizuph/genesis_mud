/*
 * egg.c
 *
 * Used in npc/hen.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food";

void
create_food()
{
    set_short("egg");
    set_name("egg");
    set_long("An egg from a hen.\n");
    set_amount(5);
}
