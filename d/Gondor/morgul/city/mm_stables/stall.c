/*
 *  /d/Gondor/morgul/city/mm_stables/stall.c
 *
 *  The stall of the stable of Minas Morgul.
 *
 *  Deagol, August 2002
 */

inherit "/std/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "mm_stables.h"

void
create_room()
{
    ::create_room();
    
    set_short("In a stall of the stable in Minas Morgul");
    set_long("Once inside one of the open stalls, the first thing you set " +
             "eyes on is an empty trough, used for corn perhaps, and a " +
             "hayrack. The floor in this stall is paved and sloped to a " +
             "channel, which would run behind any horse stalled here. A " +
             "large iron hook has been fixed in the middle of the stall. " +
             "You can go out and back to the corridor from here.\n");

    add_item(({"channel", "floor"}),
              ("A dried, sour-smelling yellowish substance still remains " +
               "in some parts of the sloped channel.\n"));

    add_item(({"hook"}),
              ("The hook most likely serves as a hanger for harnesses, " +
               "bridles, and stirrups.\n"));

    add_item(({"trough", "hayrack"}),
              ("It is currently empty.\n"));

    add_prop(ROOM_I_INSIDE, 0);
    
    add_exit("stable.c", "out", 0, 0, 0);
}
