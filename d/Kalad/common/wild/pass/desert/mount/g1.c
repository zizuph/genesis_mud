inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(OBJ_I_HAS_FIRE,1);
   set_short("The entrance to a large cavern");
   set_long("This is the entrance to a large cavern.\n"+
      "Presently its interior is barely visible due to the roaring fire "+
      "in the center of the cavern that is belching forth a large, "+
      "acrid-smelling cloud of black smoke. Barely visible in the dim light "+
      "is an opening in the wall of the cavern to the east. In the west "+
      "lies the sole exit from here.\n");
   add_item(({"entrance","exit"}),
      "An opening in the side of the cavern, the sole entry and exit point "+
      "to this place.\n");
   add_item(({"large cavern","cavern"}),
      "A place of dark stone and no water. It is presently filled with a "+
      "large amount of smoke.\n");
   add_item(({"roaring fire","fire"}),
      "Despite its blazing intensity, the sheer volume of smoke it is "+
      "producing only seems to dull its brightness.\n");
   add_item(({"center"}),
      "A roaring fire lies there.\n");
   add_item(({"large cloud of black smoke","acrid-smelling cloud of black smoke","large cloud","acrid-smelling cloud","black smoke","smoke","cloud"}),
      "A thick, almost oily cloud of noxious vapors that fills this cavern "+
      "with its choking presence. Some of it is escaping out through the "+
      "exit in the west.\n");
   add_item(({"opening"}),
      "It appears to lead deeper into this cavern.\n");
   add_exit(CPASS(desert/mount/m24),"west");
   add_exit(CPASS(desert/mount/g2),"east");
}
