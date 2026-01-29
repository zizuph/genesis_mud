inherit "/std/room";
#include "road.h"

create_room() {

	set_short("On Palace Road");
	set_long(BS("You are walking on the Palace Road in Tyr, leading "+
		"north from the town square. To the northeast, you see a "+
		"rather large house, and you guess it belongs to a templar "+
		"or a noble. Outside the house, there is a small garden. On "+
		"the west side of the road you see the east walls of the "+
		"banquet-hall, a hall where the baron and his nobles hold "+
		"their celebrations and banquets.\n",70));

	add_item(({"garden","small garden"}),BSS(
		"You are a bit far from the garden from here, but it seems "+
		"pretty nice. Maybe you should get closer.\n"));

	add_item(({"large house","house"}),BSS(
		"It's a large, well kept house, probably owned by a templar. "+
		"You cannot see much though, but maybe if you got closer.\n"));

	add_item(({"wall","walls"}),BSS(
		"The walls look pretty impressive, and you wonder how the "+
		"inside looks.\n"));


	add_exit(PAL_STR+"street3","north",0);
	add_exit(PAL_STR+"street1","south",0);

}
