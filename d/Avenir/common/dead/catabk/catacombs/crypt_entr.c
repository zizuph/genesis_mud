// file name: crypt_entr
// creator: Ilyian (Oct 15, 1995)
// last update:
// purpose: Entrance to the underground crypts
// note: Most of the code for these rooms is in
//         dead.c - see that file for info on these rooms.
// bug(s):
// to_do:

inherit "/d/Avenir/common/dead/dead";
#include "../dead.h"

void
create_room()
 {
  acat("93","south");

  crypt_long("There is some light coming in from the north, "
            +"but south there is nothing but darkness.");

  set_long("This is the entrance to a long and winding "
          +"tunnel that leads south into a frightful "
          +"blackness. The walls seem to be made from "
          +"glistening limestone, and the floor is covered "
          +"with a thick white mist, similar to the fog "
          +"that lies on the moors, but whiter. Some light "
          +"filters in from the north. ");

//   add_prop(ROOM_I_LIGHT, 1);

  clone_object(OBJ+"crypt_gate_s")->move(TO);
  reset_room();
 }

void
reset_room()
 {
  crypt_reset();
 }
