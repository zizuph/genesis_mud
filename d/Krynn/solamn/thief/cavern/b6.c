/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE


void
create_thief_room()
{
    set_short("In a staircase");
    set_long("This is a narrow staircase winding up and down. The staircase is " +
	     "made entirely from stone@@dwarf_sees@@.\n");
    
    add_exit(CAVERN + "a6","down");
    add_exit(CAVERN + "c6","up");
    
    DARK;

    add_item(({"staircase","walls","wall"}),
	     "It's carved from the rock@@dwarf_sees@@.\n");
    add_item("stonemasonry",
	     "You notice that a caring dwarf must have put a lot of effort " +
	     "into this staircase. The wall is perfectly circular and it is " +
	     "a pleasure to look at it and be honored to be able to descend " +
	     "and ascend in it.\n");
}


string
dwarf_sees()
{
  /* any dwarf-kin should recognize it */
    if (TP->query_race() == "dwarf")
      return ", and you notice that this is some excellent dwarven stonemasonry here";
    else
      return ", probably of dwarven origin";
}
