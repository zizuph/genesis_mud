/*
   Wayreth. Tower in the wall enclosing the towers of High Sorcery

   wall_tower02.c
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

void
create_wayreth_room()
{
   set_short("Inside the southeast tower");
   set_long("This is the southeast tower of the complex surrounding " +
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

   add_exit(WTOWER + "yard03", "northwest", 0);
}
   

