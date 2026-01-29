inherit "std/room";
#include "defs.h"
#include <stdproperties.h>

object mon=0;

void
create_room()
{
	set_short("Nice cell");
	set_long("This is a very regal cell compared to the "+
	   "rest of this dreary place. The floor is well swept "+
	   "and covered by a small rug. There is a very large chair "+
	   "with a table sitting beside it. There is actually a "+
	   "mattress in the corner instead of a pile of straw. The "+
	   "room is lit by a lantern on the table.\n");


	add_item(({ "floor"})"The floor is clean and contains no "+
	   "trap doors.\n");
	add_item(({ "rug" })"It is a pretty commonplace rug. It is "+
	   "also clean on the surface and the floor beneath it.\n");
	add_item(({ "chair", "throne" })"This is a huge chair, "+
	   "crafted for someone the size of two men. It is made of "+
	   "finely polished wood reinforced by iron, a rarity here "+
	   "in the desert of Athas.\n");
	add_item(({ "table" })"This is an ordinary table made of a "+
	   "cheap wood.\n");
	add_item(({ "lantern", "lamp"})"The lantern is a modern "+
	   "wonder; able to make light for hours just by burning "+
	   "a little flask of oil.\n");
	add_item(({ "mattress", "bed" })"The mattress is lumpy and "+
	   "stained. Still, it looks better than the other bedding "+
	   "in this hellhole.\n");


	LIGHT

	add_exit(TYR_PITS+"pen8.c", "west");
}
reset_room()
{
	seteuid(getuid(TO));
	if(mon)
	  return;
	tell_room(TO, "A jet-black half-giant slowly rises from his "+
	   "throne to confront you.\n");
	mon = clone_object(TYR_NPC+"blackslave");
	mon->move(TO);
}

