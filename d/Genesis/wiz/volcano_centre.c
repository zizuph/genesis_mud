#pragma save_binary

#include "default.h"

/*
  This room is linked to the worldmap at x0.4 y0.4
*/

create_room() 
{
	set_short("Volcano centre");
	set_long("This is the centre of the volcano. " +
		 "You are swimming in lava.\n" +
		 "Right above the lava is a golden " +
		 "staircase leading up into the air.\n" +
		 "You can walk in any direction.\n");

	add_exit(THIS_DIR + "stairlow", "up", "@@up_msg@@");
	add_exit("@@map_file|x0.5y0.3","south",0);
	add_exit("@@map_file|x0.5y0.4","east",0);
	add_exit("@@map_file|x0.3y0.4","west",0);
	add_exit("@@map_file|x0.4y0.5","north",0);
	set_noshow_obvious(1);
}

up_msg()
{
	write("You climb up onto the golden staircase.\n");
	write("You follow the stairs into the air.\n");
	return 0;
}

