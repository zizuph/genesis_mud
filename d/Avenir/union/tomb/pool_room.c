#pragma strict_types
#include "defs.h"

inherit "/std/room";
#include <macros.h>


public void
create_room(void)
{
    set_short("circular edge");
    set_long("Opening up before you is a large, circular aqua pool. "+
	"Surrounding the pool is the narrow ledge upon which you "+
	"stand, which borders the pool all the way around.\nStrange, "+
       	"sinuous shapes seems to dance within the pool, reflecting a "+
	"gleaming silver light.\n");

    add_item(({"shape","shapes"}), "You cannot make them out, whenever "+
	"you look at one to closely, they dart out of sight.\n");
    add_item(({"pool","water"}), "The pool is a startlingly deep shade "+
	"of aqua, the eye of a forgotten soul staring into you. Looking "+
	"past shapes that flicker in the pool, the pool appears to open "+
	"up into somewhere wider.\n");
    add_item("ceiling", "It is flat and uninteresting, of an unreflective "+
	"off-white plaster.\n");
    add_item(({"floor","ledge","ground"}),
	"The ledge surrounding the pool is made from slippery, "+
	"blue stone tiles.\n");
    add_item(({"tile","tiles"}),"They are tiny tiles that "+
	"make up the ledge.\n");

    add_cmd_item(({"water","pool","from pool","the water"}),
	({"drink","taste"}), "The liquid has a strange and unfamiliar "+
	"taste, completely unlike water, but not unpleasant.\n");
    add_cmd_item(({"pool","water","in pool","into pool","into the pool",
	    "in the pool","in water","into the water","in the water"}),
	({ "dive","jump", "enter" }), "@@do_dive@@");

    add_exit(PASSAGE, "southwest");
}

public string
do_dive(void)
{
    write("You take a deep breath and dive down into the pool.\n"+
	"A sudden current graps you like a dark hand and yanks you "+
	"down, and suddenly the water below you opens up impossibly.\n"+
	"You find yourself in a different place.\n");
    say(QCTNAME(TP) +" dive down into the pool and is "+
	"quickly lost from sight.\n");

    TP->move_living("M", MAZE + "maze1", 1, 1);
    return "";
}
