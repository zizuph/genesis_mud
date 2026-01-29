/*
 *  /d/Gondor/morgul/city/mm_stables/stable.c
 *
 *  The main stable of Minas Morgul.
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
    
    set_short("In a stable in Minas Morgul");
    set_long("You find yourself in a long broad corridor, divided into " +
             "separate stalls. Each invidivual stall is parted by a wooden " +
             "wall. At the far right end, you notice a  wide, open box. " +
             "All stalls currently housing horses have been furnished with " +
             "doors. Some stalls, however, are open.\n");
    
    add_item(({"wall", "walls"}),
              ("Each stall wall has a high part to prevent the horses from " +
               "seeing and thus annoying each other.\n"));
    
    add_item(({"corridor"}),
              ("You are standing in it.\n"));
    
    add_item(({"box"}),
              ("The large box is in fact more like an open space. " +
               "Currently, it is empty, but judging by that pile of hay, a " +
               "trough and water basin, both of which are empty, it seems " +
               "possible to stall a large steed here.\n"));
    
    add_item(({"door", "doors"}),
              ("You hear a high-strung neigh as you approach one of the " +
               "closed doors. It seems securely locked.\n"));
    
    add_item(({"stall", "stalls"}),
              ("Perhaps you could enter one of the open stalls.\n"));

    add_prop(ROOM_I_INSIDE, 0);
    
    add_exit("stall.c", "enter", 0, 0, 1);
    add_exit("court.c", "south", 0, 0, 0);
}
