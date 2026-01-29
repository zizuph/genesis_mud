/*
 * waterhandler.c
 *
 * This file handles the water area between Cadu and Carisca
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
#include "defs.h"

object *rooms;

void
trans(string s, int i, int j)
{
    int f;

    if ((i<0) | (i>4) | (j<0) | (j>4))
    {
        TP->catch_msg("The waves flush you back to your previous location.\n" +
                      "You realize that it is impossible to swim further " + 
                      "in that direction.\n");
        return;
    }

    f = i + j * 5;

    if (f == 0)
    {
        TP->move_living(s, NYREESEDIR + "cadu_water");
        return;
    }
    if (f == 23)
    {
        TP->move_living(s, CARISCADIR + "d2");
        return;
    }
    TP->move_living(s, rooms[f]);
}

void
set_em_up()
{
    int i,j;
    object ob;

    for(j = 0; j < 5; j++)
        for(i = 0; i < 5; i++)
        {
            ob = clone_object(CARISCADIR + "waterroom");
            ob->set_which(i, j);

            if (!sizeof(rooms))
                rooms = ({ob});
            else
                rooms = rooms + ({ob});
        }
}      

void
create_room()
{
    set_em_up();
    add_prop(ROOM_I_NO_CLEANUP, 1);
}

void
init()
{
    ::init();
    TP->move_living("with a bird.", rooms[0]);
}
  
