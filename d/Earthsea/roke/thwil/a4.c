#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
  set_short("Alley");
  set_long("To the south you see a great building whose few small "+
	   "windows are higher then the chimney tops of the houses "+
	   "to the north. It looks like a fort or castle, built on "+
	   "mighty grey blocks of stone. \n");
  
  add_exit(THWIL + "t3" , "north" , 0);
  add_exit(THWIL + "gate" , "south" , 0); /* maybe not like this ..*/
  
  add_item("building", "You have to go closer to get a better look!\n"); 
  STREET;
}







