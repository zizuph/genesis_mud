/*
 * cas_tmp_room.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Glindor  */

/* this is the room in which the players stay a few sec when pressing the
   magic button of the statues */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room() 
{
    INSIDE;

    set_short("");
    set_long("\n");
}

void
check(object a)
{
    if (present(a, this_object()))
        a->move(NYREESEDIR + "cadu_q5");
}

void
enter_inv(object a, object b)
{
    set_alarm(10.0, 0.0, &check(a));
}
