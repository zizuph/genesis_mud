inherit "/d/Roke/Athas/room/tyr/square/MARKEDSTD";

#include "square.h"

create_market()	{
	set_short("Market in Tyr");

	add_exit(SQUA_D+"mark1","west",0);
	add_exit(SUL_STR+"road6","east",0);
	add_exit(MAR_STR+"street2","north",0);
	add_exit(SQUA_D+"mark3","southwest",0);
	add_exit(SQUA_D+"mark4","south",0);

}

