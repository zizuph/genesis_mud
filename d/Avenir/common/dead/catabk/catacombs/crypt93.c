// file name: crypt93
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
  acat("_entr","north");

  acat("68","west");
  acat("92","northwest");

 

/* Default is the standard random description. */
  //crypt_long(crypt_desc[random(sizeof(crypt_desc))]);
  
  set_long("Hollow white tunnels extend into a stygian " +
          "darkness all about you. The walls seem to be made from "
          +"glistening limestone, and the floor is covered "
          +"with a thick white mist, similiar to the fog "
          +"that lies on the moors, but whiter. Some light "
          +"filters in from the north.\n");

/* Room light values from -11 to 0 */
////   add_prop(ROOM_I_LIGHT, random(12)-12);

  reset_room();
 }

void
reset_room()
 {
  crypt_reset();
 }
