inherit "/std/room";
#include "square.h"

reset_room()
{
}
 
create_room()
{

	set_short("Southeast end of square");
	set_long(BS("You are in the southeast corner of the town square "+
		"in Tyr, just southwest of a large temple. You notice "+
		"a thin layer of desert sand lying all over the marble "+
         "square. To the south is Market Street, and "+
		"it runs towards a small market. To the east you can "+
		"follow the Stadium Road, towards the Gladiator Arena "+
		"and the Golden tower.\n",70));
 
    add_prop(ROOM_I_INSIDE, 0);

	add_exit(SQUA_D+"square8","west",0);
	add_exit(STA_STR+"road1","east" );
	add_exit(SQUA_D+"square5","northwest",0);
	add_exit(SQUA_D+"square6","north",0);
	add_exit(MAR_STR+"street1","south" );

	add_item(({"temple","temple"}),BSS(
			"You see a large and impressive temple, and you "+
			"recognize it as the well known 'Temple of Tyr'. "+
			"Maybe you should go closer ?\n"));
	add_item(({"arena","arena"}),BSS(
			"You can vaguely see the arena walls in the "+
			"distance, and it looks mighty impressive!\n"));
	add_item(({"square","town square"}),BSS(
				"This square seems to be made of fine "+
				"layed marble rocks. There is a thin layer "+
				"of sand here, but the wind blows away "+
				"all tracks.\n"));
	add_item(({"sand","desert sand"}),BSS(
				"This is usual desert sand that has "+
				"blown in over the city walls. What did "+
				"you expect ?\n"));


}
