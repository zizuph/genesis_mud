
inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/farlong.h"

create_room()
{
	set_short("At the citadel gate");
	set_long(
	"This is the steel gate of a great, black, foreboding citadel.  "+
	"You stand beneath a raised portullis of black-painted iron.  "+
	"All around you is the huge and menacing wall which surrounds "+
	"the citadel.  You may head into the courtyard of this "+
	"dark fortress to the west, or leave back to the "+
	"east."+
	"\n");

	AE(RHUN+"citadel/by_the_wall","east");
	AE(RHUN+"citadel/1a","west");

	add_item("portcullis","The portcullis here is "+
	"raised, giving anyone free access to the citadel.  "+
	"Apparently whatever noble lived here is gone, and it has fallen "+
	"to housing a few of the nomadic Easterlings.\n");

}

