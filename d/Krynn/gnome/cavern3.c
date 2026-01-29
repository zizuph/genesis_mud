#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

create_room()
{
    set_short("In a tunnel");

    set_long(BS("You are passing through a tunnel cut into the stone.  " +
      	"The tunnel continues west, and curves northward to the east.  " +
     	"The tunnel ends shortly beyond, opening into a noisy cavern " +
      	"full of small scurrying figures, cables, and partly assembled " +
     	"gizmos.", 70));
    INSIDE;
    LIGHT;
    
    add_item("tunnel", "Hewn out of the rock, the tunnel walls curve " +
	"and meet above your head.\n");
    add_item("gizmos", "Just plain ordinary gizmos.\n");

    add_exit(TDIR + "cavern2", "west", 0);
    add_exit(TDIR + "cavern4", "northeast", 0);
}

wayout() { return "northeast west"; }
tohelp() { return "northeast"; }
fromhelp() { return "west"; }
area() { return "Inthemaincaverns"; }
