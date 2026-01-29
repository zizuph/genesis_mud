#include "/d/Cirath/common/defs.h"
#include "wbt.h"
inherit "std/room";

void
create_room()
{
   set_short("Second Floor Landing");
   set_long("You stand at the top of a marble staircase "
	+"in the main part of the school.  Before you "
	+"stretches a large hall, which is lit by torches.\n");
   add_item("staircase","It is a large marble staircase, "
	+"intricately etched in damasked designs, as well "
	+"as images of battles.\n");
   add_item("hall","It stretches out in front of you, "
	+"leading further into the Warrior's School of "
	+"Tyr.\n");
   add_item("torches","They are in sconces on the walls "
	+"and let off enough light to see by.\n");

	INSIDE;

	add_exit(WWORK+"hall1.c", "east", 0, 0);
	add_exit(WWORK+"sq4.c", "down", 0, 0);
}
