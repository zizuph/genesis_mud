inherit "/d/Roke/Athas/room/tyr/square/MARKEDSTD";

#include "square.h"

create_market()	{
	set_short("Market in Tyr");

	add_exit(SQUA_D+"mark2","north",0);
	add_exit(SQUA_D+"mark1","northwest" );
	add_exit(SQUA_D+"mark3","west",0);
	add_exit("xxx","southeast","@@closed");

}

closed()	{
	write(BSS("Due to building projects, this area is closed.\n"));
	return 1;
}

