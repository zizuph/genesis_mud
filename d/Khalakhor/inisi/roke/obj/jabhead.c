/*
 * jabhead.c
 *
 * Used in wep/jabsword.c
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
    set_short("jabberwock head");
    set_name("head");
    set_adj("jabberwock");
    add_name("jab_head");
    set_long("This head once belonged to a Jabberwock.\n");
}
