#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
  set_short("An alcove full of shelves");
  set_long("The alcove is full of shelves that line every wall. " +
	   "The shelves are full of books, most very ancient. " +
	   "Tales of heroic deeds of old and arcane lore are all around. " +
	   "Centuries of knowledge are stored in this room. The smell " +
	   "slowly decaying paper pervades the air.\n");
  
  add_item(({"shelves", "wall", "walls"}),
	   "The shelves line every wall in the alcove.");
  add_item(({"book", "books"}),
	   "You see volumes upon volumes of tomes.");
  add_exit("manor_entrance", "east");
}
