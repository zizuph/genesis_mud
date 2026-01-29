// file name: crypt49
// creator: Ilyian (September 1, 1995)
// last update:
// purpose: Room in the underground crypts
// note: Most of the code for these rooms is in
//         dead.c - see that file for info on these rooms.
//
// Updates:  
//    Lilith, Jun 2021 Updated exit to room 48. It was pointing south 
//                     instead of north.


inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

void
create_room()
{
  acat("48","north");
  acat("50","east");

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
