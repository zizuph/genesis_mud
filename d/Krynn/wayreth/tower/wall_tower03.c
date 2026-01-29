/*
   Wayreth. Tower in the wall enclosing the towers of High Sorcery

   wall_tower03.c
   --------------

   Coded ........: 95/05/31
   By ...........: Jeremiah

   Latest update : 18/12/11
   By ...........: Arman

*/

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include <composite.h>

inherit WAYINROOM;

#define SCROLL "/d/Krynn/common/scrolls/vul_magic_scroll"

public mixed prevent_teleport();
object memorial, scroll;

void
reset_wayreth_room()
{
   if (!objectp(memorial))
    { 
        memorial = clone_object(TOBJ + "wizard_memorial");
        memorial->move(TO);
    }

    if (!P(scroll, memorial))
    {
        scroll = clone_object(SCROLL);
        scroll->move(memorial, 1);

        memorial->reset_gem_slots();
        memorial->add_prop(CONT_I_CLOSED, 1);
        memorial->add_prop(CONT_I_LOCK, 1);
    }

}

void
create_wayreth_room()
{
   set_short("Inside the west tower");
   set_long("This is the west tower of the complex surrounding " +
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

   add_exit(WTOWER + "yard04", "east", 0);

   add_prop(ROOM_M_NO_TELEPORT, prevent_teleport);
   add_prop(ROOM_M_NO_ATTACK, "Magical runes of tranquility have been incorporated " +
       "into the walls surrounding the Tower of High Magic. There will be no violence " +
       "allowed on these grounds.\n");

   reset_wayreth_room();
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
   

