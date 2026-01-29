#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Spiral staircase");
    set_long("You are walking a steep spiral staircase.\n");
    add_item("staircase",
	     "It winds up and down around a dark shaft in the mountain. "+
	     "You can feel the air gets fresher further up, while the "+
	     "clammy air below is damp and unfresh. The staircase has no "+
	     "railing, so better be careful and do not jump.");
    add_item("shaft",
	     "This is obviously a dwarven cut shaft, since the cuts are made "+
	     "clear and straight. In circles the staircase winds up and "+
	     "down, having no railing at all, so better be alert and do not "+
	     "loose your balance.");
    add_item("railing", "Noone ever built one!");
    add_item(({"air","scent"}),"It is fresher up than down.");
    add_item("cuts",
	     "They are clear and straight, obviously dwarven-made.");
    DOWN("mjunc");
    UP("swindow");
}
