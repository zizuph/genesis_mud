/* 

   The dragoncave used in a quest

   Coded 1995-05-04   23.51 by Dumrik

*/


#include "/d/Krynn/dumrik/local.h"

inherit I_ROOM;

create_room() {

  set_short("A Cave");
  set_long("You are standing in a cave that is used by a dragon. You can see "+
	   "a nest in the center of the cave, the walls and ceiling are very "+
	   "moist, just the way dragons like it.\n");
  add_exit("/d/Krynn/dumrik/lake.c","south",0);



}
