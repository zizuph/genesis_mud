#pragma strict_types

inherit "/d/Gondor/rohan/plains/plain";

#include <language.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

#define RHARD   30

static object *Npcs = allocate(3);

public void
create_plain() 
{
    set_geo("open");
    set_wet("damp");
    set_grass("long, dark green and spicy");
    set_land("the Eastfold");
    set_where("northeastern");
    set_special(2);
    set_rname("Entwash");
    set_rhard(RHARD);
    set_rwhere("north");
    add_exit("NotOpen/f14", "north", drown, RHARD);
/*
    add_exit("NotOpen/f14","north",crossing);
*/
    add_exit("d14", "south", 0, 5);
    add_exit("e13", "west",  0, 5);
    set_extraline("To the east you can see the mighty mouths of the "
      + "Entwash, where the mighty river splits up into dozens "
      + "of smaller streams, all running towards the great Anduin "
      + "in the east. The fens lying between the many rivers that "
      + "make up the mouths of the Entwash seem to be hardly passable.");

    set_drink_from( ({"entwash","river","stream"}) );
    
    set_npc_file(ROH_DIR + "npc/eastfoldorc");
    set_npc_number(3);

    reset_room();
}
