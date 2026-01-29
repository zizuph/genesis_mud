inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("guard", TYR_NPC+"hgiant", 2, 1);
}

 
create_room()
 {
  set_short("Path to Slave Pits");
  set_long("You are on a dusty path north of Templar Road.  Sounds "
	+"of agony and wails of pain echo through the walled plaza "
	+"around you.  You think you are near a place where most "
	+"people don't choose to be.\n");
  add_item(({"wall","walls"}),"The walls stretch "
	+"around the entire complex which contains Kalak's ziggurat. "
	+"It is said he likes the way the screams of pain of his slaves "
	+"echos throughout the complex.\n");
  add_item("path","It leads north and south and you are standing in the "
	+"middle of it.\n");
  add_item("plaza","You are inside of Kalak's main plaza.  Here are all "
	+"of his slaves, torture rooms, his personal chambers and members "
	+"of his elite guard.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  OUTSIDE

  add_exit(TYR_PITS + "pen4","north",0);
   add_exit(TYR_SLAVE + "rd_tr_03","south",0);
  set_alarm(1.1,0.0,"reset_room");
}

