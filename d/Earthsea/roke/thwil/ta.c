#include "defs.h"
inherit THWIL_BASE_ROOM;

void create_thwil_room()
{
  set_short("Street");
  set_long("The street makes a soft turn here, leading into the"+
	   " city south and west from here. "+
	   "To the north the street becomes more like an alley, "+
	   "leading away from"+
	   " the city, and towards the harbour. "+
           "The air is cold and damp. There's a feeling of "+ 
           "magic surrounding you. \n");
  
  add_exit(THWIL + "t9" , "west" , 0);
  add_exit(THWIL + "t7" , "south" , 0);
  add_exit(THWIL + "a2" , "north" , 0);
  
  STREET;
}







