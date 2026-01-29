inherit "/std/room";
#include "square.h"

reset_room()
{
}
 
create_room()
{

	set_short("Northwest end of square");
	set_long(BS("You are in the northwest corner of the town square "+
		"in Tyr, just southwest of a large house. You notice "+
		"a thin layer of desert sand lying all over the marble "+
		"square. To the north the High road is running into the nobles "+
		"quarters, and "+
		"it runs towards the nobles quarters. To the west you can "+
		"follow the Main Gate Roads, towards the commoners quarters, "+
      "and because the Main Gate of Tyr.\n",70));
 
    add_prop(ROOM_I_INSIDE, 0);

	add_exit(SQUA_D+"square2","east",0);
	add_exit(MGR_STR+"road1","west" );
	add_exit(SQUA_D+"square5","southeast",0);
	add_exit(SQUA_D+"square4","south",0);
	add_exit(HGH_STR+"road1","north" );

	add_item(({"square","town square"}),BSS(
				"This square seems to be made of fine "+
				"layed marble rocks. There is a thin layer "+
				"of sand here, but the winds blows away "+
				"all tracks.\n"));
	add_item(({"sand","desert sand"}),BSS(
				"This is usual desert sand that has "+
				"blown in over the city walls. What did "+
				"you expect ?\n"));


}
