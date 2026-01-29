// file name: crypt70
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
  acat("86","northwest");
  acat("69","south");
  acat("91","southeast");

  set_short("Tunnel");
  set_long("A dark tunnel wraps suffocatingly around you. "
	+ "Mist hangs over the ground, obscuring your feet. "
	+ "To your south, a large oval door seals a "
	+ "moldy brick archway. Nothing seems to breathe here, "
	+ "not even a breeze.\n");  

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
