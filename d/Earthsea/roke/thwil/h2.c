#include "defs.h"
inherit THWIL_BASE_ROOM;

object fisher;

void
reset_room()
{
  if(!objectp(fisher))
    {
      fisher = clone_object(THWIL + "monster/fisher");
      fisher->move(TO);
    }
}   

void
create_thwil_room()
{
  set_short("Pier");
  set_long("You are on a strange pier. "+
	   "It is unnaturally quiet here and you feel that "+
	   "although there is no one around, it would be "+
	   "very unwise to disturb the calm of this place. "+
	   "The pier continues east and west.\n");
  
  add_item("pier","The pier is solid. Built by the best craftsmen "+
	   "in Earthsea, and maybe something more... \n");
  
  add_exit(THWIL + "h1" , "west" , 0);
  add_exit(THWIL + "h3" , "east" , 0);
  reset_room();
  BEACH;
}



