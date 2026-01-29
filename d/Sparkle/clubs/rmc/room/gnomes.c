/* by Conan 950410 */

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

void
create_room()
{
  set_short("In a small house");
  set_long(break_string(
    "You're standing in a small house. This house is quite spartan. The walls are "+
    "painted white and the only furniture is a small desk placed in the north end of "+
    "the room. A golden sign hangs on the wall behind the desk.\n",70));

  add_item("desk","A golden desk with a small gnome sitting behind it.\n");
  add_item("gnome","This gnome can help you with your bank account.\n");
  add_item(({"wall","walls"}),"Just white, plain walls.\n");
  add_item("sign","There's some readable text on it.\n");

  INSIDE;
  LIGHT;
  
  add_exit(RMCROOMS+"pier","east");

  clone_object("/d/Genesis/obj/deposit")->move(this_object());
}












