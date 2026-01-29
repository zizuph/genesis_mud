// file name: crypt102
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
  acat("_s6","north");
  acat("103","south");
  acat("101","southwest");

/* Default is the standard random description. */
  crypt_long(crypt_desc[random(sizeof(crypt_desc))]);

/* Room light values from -11 to 0 */
//   add_prop(ROOM_I_LIGHT, random(12)-12);

  reset_room();
 }

void
reset_room()
 {
  crypt_reset();
 }
