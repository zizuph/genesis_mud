inherit "/std/room";

#include "default.h"

void
create_room()
{
  set_short("A large bedroom");
  set_long(break_string("This long room completely covers a floor of the "+
	"building you are in. There is a bed and covers at the far end "+
	"and a small table made from mismatched pieces of wood just "+
	"nearby.\n", 76));

  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_I_LIGHT, 1);

  add_exit("/d/Emerald/telberin/castle/h5", "down", 0, 1);

  add_item("bed","The bed is slovenly kept, the covers not neatly "+
	"folded or anything. It looks\nlike it has not been slept in "+
	"for some days.\n");
  add_item("covers","The covers are flea ridden, not what you expect from "+
	"an elven residence.\n");
  add_item("table","The table is not a great piece of furniture, more like "+
	"a functional piece.\n");

  call_out("reset_room", 1);
}

void
reset_room()
{
  object elf;

  elf = present("elf");
  if(elf && elf->query_name() != "ghost")
	return;
  else
  elf = clone_object("/d/Emerald/telberin/castle/sit_elf");
  elf->move_living("into a room", TO);
}

