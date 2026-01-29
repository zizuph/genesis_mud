// file name: crypt91
// creator: Ilyian (September 1, 1995)
// last update:
// purpose: Room in the underground crypts
// note: Most of the code for these rooms is in
//         dead.c - see that file for info on these rooms.
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

void
create_room()
{
  set_long("A tunnel twisting through the white limestone "
	+ "stretches out before you to the northwest. "
	+ "The ceiling above is a void of blackness. "
	+ "A cold mist wraps around your ankles and "
	+ "and chills your bones. Somewhere nearby, "
	+ "water drips into a puddle. A candlabra has "
	+ "has been mounted onto the wall, but long "
	+ "since neglected. Somehow... you feel watched.\n");

  acat("70","northwest");
  acat("92","south");

/* Default is the standard random description. */
//  crypt_long(crypt_desc[random(sizeof(crypt_desc))]);

/* Room light values from -11 to 0 */
////   add_prop(ROOM_I_LIGHT, random(12)-12);

  reset_room();
 }

void
reset_room()
 {
  crypt_reset();
 }
