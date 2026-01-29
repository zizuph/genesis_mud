/*

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;

void
create_tower_room()
{
   set_short("A misty room");
   set_long("The area is surrounded in mists. You do not think that this "+
	"is the way it should be. You see nowhere to go ... no way to "+
	"leave this oppressive place.\n");

   set_wall_type(3);
}
