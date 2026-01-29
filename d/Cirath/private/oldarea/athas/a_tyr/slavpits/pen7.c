inherit "std/room";
#include "/d/Roke/common/defs.h"
#include <stdproperties.h>

void
create_room()
{
	set_short("The center of the slave pits.");
	set_long("This is the center of the corridor of "+
	   "the slave pits under the streets of Tyr. The way "+
	   "out is to the west while to the east the hallway "+
	   "continues deeper into the bowels of the slave pens "+
	   "and eventually lead to the fighting pits. Slave "+
	   "pens are to the north and south.\n");

	add_item(({ "pens", "cells", "pen", "cell"})"The slave "+
	   "pens contain unwanted slaves or criminals condemned "+
	   "to 'Death by Gladiator'.\n");

	LIGHT

	add_exit(PEN_DIR+"pen6.c", "west");
	add_exit(PEN_DIR+"pen2.c", "north");
	add_exit(PEN_DIR+"pen11.c", "south");
	add_exit(PEN_DIR+"pen8.c", "east");
}

