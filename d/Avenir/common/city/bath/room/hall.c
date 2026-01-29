#pragma strict_types
/*
 * ~/hall.c
 *
 * Bath House Entrance Hall.
 *
 * Revisions:
 *   Grace,  Feb 1994: Created.
 *   Grace,  Aug 1994: ?
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../bath.h" 
inherit BATH_ROOM;

static void
create_bath_room(void)
{
    set_short("Entrance Hall");
    set_long("A starkly beautiful little hall with a chequered floor. "+
	"Marble columns support a small domed ceiling with painted "+
	"panels depicting bath house scenes. There is the barest "+
	"hint of moisture in the air. A set of double doors lead "+
	"north, into the bath house proper.\n");

    add_item(({"floor", "chequers", "chequer", "squares", "square"}),
	"Composed of black and white veined marble squares that are "+
	"polished to a remarkable sheen, and kept spotlessly clean.\n");
    add_item(({"column", "columns", "supports"}),
	"There are a dozen columns, each of veined white marble,"+
	"and beautifully carved.\n");
    add_item("vein",
	"A dark streak of minerals within the stone.\n");
    add_item(({"carving", "carvings"}),
	"A skilled hand chiselled trailing vines into the marble "+
	"columns.\n");
    add_item(({"panel", "panels", "paintings", "ceiling", "dome"}),
	"The architecturally-sound dome is painted with hedonistic "+
	"scenes of people at their bath.\n");
    add_item(({"door", "doors", "double doors", "pattern"}),
	"These are beautifully made of kesoit wood. "+
	"A repeating pattern of golden trefoils and amphoras "+
	"covers both doors.\n");
    add_item(({"amphora", "amphoras" }),
	"A beautifully proportioned jar with graceful curves, two "+
	"handles, and a narrow neck.\n");  
    add_item(({"trefoil", "trefoils"}),
	"The golden trefoil is the symbol of Sybarus.  It is "+
	"three circles, equidistant, and sharing a common center.\n"); 

    add_exit(BATH + "outside", "up");
    add_exit(BATHRM + "desk", "north");
}
