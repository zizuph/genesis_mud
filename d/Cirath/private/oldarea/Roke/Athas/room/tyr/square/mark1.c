inherit "/d/Roke/Athas/room/tyr/square/MARKEDSTD";

#include "square.h"

create_market()	{
	set_short("Market in Tyr");

	add_exit(SUL_STR+"road5","west",0);
	add_exit(MER_STR+"road2","north",0);
	add_exit(SQUA_D+"mark2","east",0);
	add_exit(SQUA_D+"mark3","south",0);
	add_exit(SQUA_D+"mark4","southeast",0);

}

