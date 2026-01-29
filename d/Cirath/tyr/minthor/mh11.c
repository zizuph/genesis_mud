inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("House");
  set_long("You have entered the home of the noble clan Minthor. The "
	+"entire house exudes wealth. To your left sits a large bowl of "
	+"water, and underfoot is a soft woven mat. Overhead hangs a "
	+"huge crystal chandelier. There are exits to the north, "
	+"northeast, and northwest, all leading to equally lavish rooms "
	+"To the south lies the exit from the house into the courtyard, "
	+"and back under the bloated sun of Athas.\n");
  add_item("building","You are standing inside one.\n");
  add_item("chandelier","It hangs from the ceiling far above you, and "
	+"appears to be made of some sort of crystalline material. "
	+"Whatever it is, you can be assured that is expensive.\n");
  add_item("mat","The mat is made of a very soft cloth which has been "
	+"woven carefully to absorb water.\n");
  add_item("bowl","It is a bowl made of a golden metal, and is filled "
   +"with water that is absolutely pure and clear. It appears as "
	+"if the bowl is made for washing a guests feet before they "
	+"enter the house.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  add_cmd_item("feet","wash","@@wash");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
  add_exit(TZ_MINTHOR + "mh26","northwest",0);
  add_exit(TZ_MINTHOR + "mh14","northeast", 0);
  add_exit(TZ_MINTHOR + "mh12","north", 0);
  add_exit(TZ_MINTHOR + "mh3","south","@@door");
}
door()
{
	write("You step from inside the house, back into the hot "
	+"Athasian sun.\n");
	return 0;
}
wash()
{
	write("You dip your feet into the bowl, washing the dirt off.\n");
	say(QCTNAME(TP) + " dips his feet into the bowl of water, "
	+"washing the dirt from them.\n");
	return 1;
	return 0;
}
