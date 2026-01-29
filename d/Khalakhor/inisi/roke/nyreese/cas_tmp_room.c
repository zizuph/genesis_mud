/*
 * cas_tmp_room.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 * Added ::enter_inv(a, b) call, Cotillion 2005
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
    int remove = 1, t;
    object *objs;

    // Security check, cadu_q5 should have move the player earlier
    if (objectp(a) && present(a, this_object()))
        a->move(NYREESEDIR + "cadu_q5");


    objs = all_inventory(this_object());
    
    for (t = 0; t < sizeof(objs); t++)
    {
        if (interactive(objs[t]))
        {
           objs[t]->move(NYREESEDIR + "cadu_q5");
           remove = 0;
        }
    }

    if (remove)
        remove_object();
    else
        set_alarm(5.0, 0.0, &check(a));
}

void
enter_inv(object a, object b)
{
    ::enter_inv(a, b);
    set_alarm(10.0, 0.0, &check(a));
}
