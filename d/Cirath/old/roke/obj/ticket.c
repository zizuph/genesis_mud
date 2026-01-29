/*
 * ticket.c
 *
 * Used in nyreese/cadu_inn.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <macros.h>

string
query_recover()
{
    return MASTER;
}

void
create_object()
{
    set_short("hotel ticket");
    set_long("This is a ticket to the hotel in Cadu.\n");
    
    set_adj("hotel");
    set_name("ticket");
    add_name("cadu_inn_ticket");
}
