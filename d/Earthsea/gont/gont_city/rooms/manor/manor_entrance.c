#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
  set_short("Entrance to the Lord's manor");
  set_long("You stand just inside the grand entrance of an official " +
	   "looking stone building. The granite tiles of the foyer " +
	   "is polished smooth like a mirror. The large windows let " +
	   "sunlight into room and reflect off the polished stone " +
	   "beneath. Two ancient tapestries adorn the walls of the manor. " +
	   "To the east is an archway that leads further into the manor. " +
	   "To the west is a large alcove full of shelves. To the north " +
	   "is an antechamber that leads into the audience room " +
	   "of the Lord of Gont.\n");
  add_item(({"tapestries", "ancient tapestries"}),
	   "You see two tapestries depicting images of days long ago.\n");
  add_item("tapestry",
	   "Which one do you want to look closer at?\n" +
	   "First or second?");
  add_item("first tapestry",
	   "\n" +
	   "You see an incredibly beautiful willowy dark haired " +
	   "female human. Her dark mesmerizing eyes are somber and " +
	   "melancholy.\n" +
	   "\n" +
	   "              ~*~*~*~*~ Elfarran the Fair ~*~*~*~*~\n");
  add_item("second tapestry",
	   "\n " +
	   "You see a wizened blue-cloaked male human wielding a glowing " +
	   "sword in one hand and a black yew staff in the other engaged in " +
	   "fierce battle with an ancient black dragon.\n" +
	   "\n" +
	   "         +-+-+-+ Erreth-Akbe battling the dragon Orm +-+-+-+\n");
  add_item(({"tile", "tiles", "floor"}),
	   "You see your own image staring back at you.\n");
  add_item(({"window", "windows"}),
	   "Peering through the window, you see the bustling port " +
	   "outside.\n");
  add_item(({"alcove", "west"}),
	   "It appears to be a library of some sort.\n");
  add_exit("antechamber", "north");
  add_exit("../city_street/city_road34", "south");
  add_exit("hallway01", "east");
  add_exit("library", "west");
}
