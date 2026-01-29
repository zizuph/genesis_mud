// file name: crypt86
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
  acat("85","northwest");
  acat("70","southeast");

  set_short("Tunnel");

  set_long("A tunnel carved from white limestone "
	+ "spans out before you from northwest to southeast. "
	+ "The mist, illuminated in your light, oozes "
	+ "past you and spreads down the tunnel. "
	+ "A heavy oval door grimly fills a brick archway "
	+ "leading southwest, along the southern wall. "
	+ "The air smells mouldy "
	+ "and tastes heavy on your tongue. "
	+ "Of one thing you feel deeply in your bones, "
	+ "Nothing alive lives here for very long.\n");

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
