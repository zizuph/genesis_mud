inherit "/std/room";

#include "specials.h"

create_room()	{

	set_short("Stadium Gate in Tyr");
	set_long(BSS("You are standing outside the Stadium gate of Tyr, just south of the "+
		"city. You can see the gates to the north and south you can only "+
		"see desert dunes and hot sand.\n"));

	add_exit(DES_D+"d1","southeast","@@closed");
	add_exit(SPEC_D+"stadgate","north","@@pass_gate" );

}

pass_gate()	{
	write(BSS("You hail the guards, glad to have escaped the desert once more.\n"));
}

closed()	{
	write("You see no future in that direction and turn back.\n");
	return 1;
}

