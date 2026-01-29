// std tunnel/hall room
// grace aug 1994

#include "/sys/stdproperties.h"
#include "../local.h"

inherit SPURRM;
/*
* This function defines the room.
*/
varargs void
make_the_room(string extra_long)
{
   if (!extra_long) { extra_long = ""; }
   
   set_name("tunnel");
   SHORT("Tunnel beneath the Spur");
   LONG("This tunnel runs through the base of the Knights' Spur.\n" +
      "The air is chilly and smells of fresh water. The stones " +
      "have been expertly set, giving the walls and floor a " +
      "seamless appearance. Dim light glows from narrow openings " +
      "in both sides of the tunnel walls. " + extra_long + "\n");
   
   AI(({"hall", "tunnel"}), "It is dim in here. You sense, " +
      "rather than see, the tons of stone enclosing you.\n");
   AI(({"wall", "walls"}), 
      "The walls are made of dark stone blocks that absorb light.\n");
   AI(({"floor", "ground"}), "Your footsteps echo eerily on the " +
      "smooth stone floor.\n");
   AI(({"roof", "ceiling"}), "The ceiling arches high above your " +
      "head.\n");
   AI(({"stone", "stones"}), "Smooth, dark and regularly shaped.\n");
   AI("air", 
      "It is cool and damp. Surprisingly, there is no musty smell.\n");
   AI(({"opening", "openings", "narrow openings", "slit", "slits"}),
      "There isn't much to see. They are slits in the stone about " +
      "the width of your hand and the length of your forearm.\n");
   ACI(({"opening", "openings", "narrow openings", "slit", "slits"}),
      ({"open", "enter", "feel", "peer into"}), "The slits are "+
      "too small to do anything but peer into, and you can't see "+
      "anything when you do because the wall is too thick.\n");
   
   LIGHT;
}
