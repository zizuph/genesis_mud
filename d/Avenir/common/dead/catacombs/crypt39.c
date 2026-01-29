// file name: crypt39
// creator: Ilyian (September 1, 1995)
// last update:   Lilith & Zizuph, May-July 2021: finishing area for launch
// purpose: Room in the underground crypts
// note: Most of the code for these rooms is in
//         dead.c - see that file for info on these rooms.
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/crypt_base";
#include "../dead.h"

void
create_crypt_room()
{
  acat("41","northwest");
//  acat("40","south");
  acat("42","east");

/* Default is the standard random description. */
    crypt_long(crypt_desc[random(sizeof(crypt_desc))] +" "+ crypt_desc2[random(sizeof(crypt_desc2))]);

/* Room light values from -11 to 0 */
//   add_prop(ROOM_I_LIGHT, random(12)-12);

  reset_domain_room();
 }

void
reset_domain_room()
 {
  set_searched(0);    ::reset_domain_room();
 }
