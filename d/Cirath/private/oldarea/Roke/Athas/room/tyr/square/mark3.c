inherit "/d/Roke/Athas/room/tyr/square/MARKEDSTD";

#include "square.h"

create_market()	{
	set_short("Market in Tyr");

	add_exit(SQUA_D+"mark1","north" );
	add_exit(SQUA_D+"mark2","northeast",0);
	add_exit(SQUA_D+"mark4","east",0);
	add_exit("xxx","southwest","@@closed");

}

closed()	{
	write(BSS("Due to building projects, this area is closed.\n"));
	return 1;
}

