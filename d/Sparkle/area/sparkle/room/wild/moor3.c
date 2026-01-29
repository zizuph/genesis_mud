/* 	moor3.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Misty moor");
    set_long("\n"+
             "You are standing on a misty moor, sloping down towards the sea.\n"+
             "A trail leads north along the coast and south towards the shore.\n"+
             "");

    add_exit ("c_trail","north");
    add_exit ("moor2","west");
    add_exit ("n_shore","south");
    add_exit ("peninsula","east");

    add_item(({"moor" }),
             "It's misty.\n"+
             "");
    add_item(({"sea","coast","shore" }),
             "");
}
