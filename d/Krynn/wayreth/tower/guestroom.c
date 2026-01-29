/*
   Wayreth. Stairwell in tower.

   guestroom.c
   -----------

   Coded ........: 95/06/02
   By ...........: Jeremiah

    Latest update : 97/01/17
    By........... : Teth

*/

#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;

object mirror;

public void
create_tower_room()
{
   set_short("Guest room");
   set_long("This quaint room is decorated with memorabilia from " +
      "the realm of Krynn. Obviously, this is intended to be a " +
      "guest room. The room has a permanent light to it, emanating " +
      "from a crystal globe floating high in the middle of the " +
      "room. Waiting rooms can be seen to the northwest and " +
      "southwest. The Tower stairs are east.\n");

   AI("floor", "The floor is composed of a highly polished wood, " +
      "to the point of appearing unnatural.\n");
   AI(({"light","crystal","globe","crystal globe"}),
	"This glow-crystal is not very big, yet emanates a soft light " +
	"which fills the entire room.  Obviously magical, the crystal " +
	"is suspended in mid-air, out of the reach of those with minds " +
	"too curious for their own good.\n");
   AI(({"memorabilia","decoration"}),
	"Various adventure maps and portraits of " +
	"popular sites around the land are displayed here.\n");
   AI(({"maps","adventure maps","map"}),
	"These maps show routes of travel through the land.  Some look " +
	"very old, and some look brand new, but in general, they all " +
	"function better as decoration then useful maps.\n");
   AI(({"portrait","portraits","portraits of sites","sites"}),
	"Depicting the beauty of the land, portraits of sunsets, " +
	"waterfronts, lush forests, and others give life to the " +
	"otherwise plain walls,\n");

   add_exit(WTOWER + "waitingroomn", "northwest", 0);
   add_exit(WTOWER + "stairwell04", "east", 0);
   add_exit(WTOWER + "waitingrooms", "southwest", 0);
/*
   add_exit(WTOWER + "public_library", "west", 0);
*/
   add_prop(OBJ_I_LIGHT, 2);

   mirror = clone_object(TOBJ + "mirror");
   mirror->move(TO);
}
