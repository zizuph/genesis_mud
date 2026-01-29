
#include "../local.h";
#include <macros.h>
#include <ss_types.h>

inherit SOLACE_ROOM_BASE;

void
create_solace_room() 
{
    set_short("An old rotten dock");
    set_long("You have proven to be quite brave, walking out on this " +
	     "termite ridden piece of driftwood! It is overwhelmingly " +
	     "obvious that this dock is no longer in service. There " +
	     "are several boards missing, and many rusty nails sticking " +
	     "up.\n");
    /* "You notice that the water level has lowered somewhat\n" +
       "since the dock was built, leaving some dry ground underneath.\n");  */
    add_item(({"wood","dock","boards"}),
	     "It's an old, rotten dock out on Crystalmir lake.\n");
    add_item(({"nails"}),"They're old and rusty, but they still seem to " +
	     "hold things together.\n");
    add_exit(ROOM + "lake6","northeast",0);
    /* add_cmd_item("under dock","climb","@@check_climb");*/
}

string
check_climb()
{
    if (TP->query_skill(SS_CLIMB) < 20)
      write("You try to find footing to get underneath the dock, " +
	    "but you just aren't skilled enough.\n");
    else
      write("You plant your foot on a cement casting by the dock, " +
	    "and skillfully swing yourself under.\n");
    TP->move_living("climbing under the dock", ROOM + "tunnel1.c",1,0);
    return "";
}



