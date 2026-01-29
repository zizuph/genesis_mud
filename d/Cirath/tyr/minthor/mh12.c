inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("Hallway");
  set_long("You have left the entranceway of the house and made your "
	+"way into a grand hallway. Lining the walls are beautiful "
	+"tapestries made of the finest silks. Small tables well "
	+"stocked with fruits, and decorated with flowers and golden "
	+"candelabras. To the north you can spot a staircase.\n");
  add_item("hallway","You are standing inside one.\n");
  add_item("walls","They lie to your east and west.\n");
  add_item(({"tapestry","tapestries"}),"They line the walls, and depict "
	+"various scenic views of Athas. They are crafted of the finest "
	+"silks.\n");
  add_item(({"table","tables"}),"About as tall as a man's waist, these "
	+"small sturdy tables are laden with fruit for visitors, and "
	+"also contain vases with beautiful flowers and golden candelabras. "
	+"These tables line the walls, and sit under the tapestries.\n");
  add_item(({"fruit","fruits"}),"They look full of moisture, fresh, and "
	+"delicious.\n"); 
  add_item(({"flower","flowers"}),"They are beautiful, and look utterly "
	+"alien here in this desert wasteland.\n");
  add_item(({"candelabra","candelabras"}),"They are large and made of what "
	+"appears to be solid gold.\n");
  add_item("staircase","It is to your north, and barely visible.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
  add_exit(TZ_MINTHOR + "mh13","north", 0);
  add_exit(TZ_MINTHOR + "mh11","south", 0);
}

