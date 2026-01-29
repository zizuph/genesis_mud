/*
   Wayreth. Tower in the wall enclosing the towers of High Sorcery

   wall_tower01.c
   --------------

   Coded ........: 95/05/31
   By ...........: Jeremiah

   Latest update : 96/11/27
   By ...........: Teth

*/

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include <composite.h>

inherit WAYINROOM;

public mixed prevent_teleport();

void
create_wayreth_room()
{
   set_short("Inside the northeast tower");
   set_long("This is the northeast tower of the complex surrounding " +
      "the Tower of High Sorcery. There is no evidence present to " +
      "suggest that this tower is ever guarded by anything living. " +
      "Rather, it seems that the tower is for show, to provide " +
      "a sense of symmetry to the area. The magical barriers " +
      "protecting the Tower of High Sorcery appear to make this " +
      "small tower useless.\n");
   add_item(({"wall","walls"}),"The walls of the tower are a " +
      "dusky black colour, a muted shade of the polished obsidian " +
      "that composes the Tower of High Sorcery.\n");
   add_item("floor","The floor is special in that it seems to " +
      "emanate a feeling of permanence and depth. Very odd...\n");
   add_item("ceiling","The ceiling can not be seen in the blackness "+
      "that camouflages distance.\n");

   add_exit(WTOWER + "yard01", "southwest", 0);

   add_prop(ROOM_M_NO_TELEPORT, prevent_teleport);
   add_prop(ROOM_M_NO_ATTACK, "Magical runes of tranquility have been incorporated " +
       "into the walls surrounding the Tower of High Magic. There will be no violence " +
       "allowed on these grounds.\n");
}

public mixed
prevent_teleport()
{
    if(!this_player())
	return 0;

    if(this_player()->query_is_wohs())
	return 0;

    return "Something prevents you from teleporting there.";
}
   

