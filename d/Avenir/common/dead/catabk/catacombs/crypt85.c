// file name: crypt85
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
  acat("84","north");
  acat("86","southeast");

  set_short("Tunnel");

  set_long("The tunnel snakes from the southeast to the north, "
	+ "making it impossible to see around the bend. To the "
	+ "southeast, blackness stretches out ahead of you. Cool "
	+ "mist clings it's moist fingers to your clothes, and "
	+ "silence lies like a heavy blanket over everything. "
	+ "Mounted on the wall is a rusty candleabra.\n");

  add_item("candleabra", "Holding eight candles, it "
	+ "looks like a wicked hand "
	+ "reaching out of the wall for you!");


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
