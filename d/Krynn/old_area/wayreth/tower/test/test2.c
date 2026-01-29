/*

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;

void
create_tower_room()
{
   set_short("A misty room");
   set_long("This place is also covered in mists ... you see no way of "+
	"escape ... you feel an air of opression about you. You get the "+
	"feeling that there is a purpose here ... and it is not to try to "+
	"find a way out.\n");

   set_wall_type(3);
}
