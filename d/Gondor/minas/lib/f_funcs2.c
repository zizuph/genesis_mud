/*
 *  /d/Gondor/minas/lib/fangorn_funcs.c
 *
 *  Functions that contain base-room repeats for Fangorn forest.
 *
 *  Alto 15 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define INNER_MINAS "/d/Gondor/minas"

public int initiate_torchless();
public int catch_torchless(string str);


public int 
catch_torchless(string str)
{
    string  vb = query_verb();
    object torcher;
    torcher = TP;

    if (torcher->query_npc())
    {
    return 0;
    }
    
    switch (vb)
    {
    case "light":
    case "ignite":
    case "burn":
        WRITE("The brooding menace of the forest seems to prevent that.");
        return 1;
        break;
    default:
        return 0;
    }
}

public int
initiate_torchless()
{
    add_action(catch_torchless, "", 1);
}
