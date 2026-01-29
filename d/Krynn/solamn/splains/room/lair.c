/* created by Aridor 01/12/94 */

#include "../local.h"

inherit INSIDE_BASE;

void
create_splains_room()
{
  set_short("Skie's lair");
  set_long("You are in a cavern. This is a dragon lair. " +
	   "It is completely unaccessible from the outside " +
	   "currently, but who knows? Maybe it'll change " +
	   "some day.\n");

  clone_object(LIV + "skie_dummy")->move_living("x",TO);
}
