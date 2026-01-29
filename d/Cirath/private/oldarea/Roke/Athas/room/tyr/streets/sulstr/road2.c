inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "road.h"

#define COM_STR "/d/Roke/Athas"


create_room()	{
	set_short("Sul street");
	set_long(BSS("You are walking along Sul street, the street which "+
		"leads from the Main Gate to the Stadium Gate of Tyr, "+
		"and passes straight through the market place. "+
		"You can see an inn to the northwest, and east of here "+
		"you see many buildings, built around Commoners "+
		"road.\n"));

	add_exit(SUL_STR+"road1","northwest",0);
   add_exit(COM_STR+"blah","east","@@closed@@",0);
	add_exit(SUL_STR+"road3","southeast",0);

}

closed()	{
	write(BSS("Commoners road is currently closed due to intense "+
		"building activities.\n"));
	return 1;
}
