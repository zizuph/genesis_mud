inherit "/std/room";

#include "road.h"

#define DRA_STR "/d/Roke/Athas"

create_room()	{
	set_short("High Road");
	set_long(BSS("You are walking along the High Road, and to the east you "+
		"see the Dragon Street. Northeast of here you "+
		"see a noble's house standing alone, just beside a "+
		"large castle, while to the west you can see "+
		"many large houses of nice quality.\n"));

	add_exit(HGH_STR+"road3","southeast",0);
	add_exit(DRA_STR+"xxx","west","@@closed");
	add_exit(HGH_STR+"road5","northwest",0);

}

closed()	{
	write(BSS("Due to immense bulding, this road is closed. We hope "+
		"to have it opened in a few days.\n"));
	return 1;
}

