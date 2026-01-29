/*
	*Base file holding the observables and rtells for Maggot's barn
	*Altrus, March 2005
*/

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";	

//adds observable items for Maggot's barn in general
void set_add_barn()
{
	add_item(({"barn"}), "This is a barn, something commonly found on a farmstead.\n");
	add_item(({"rafters", "beams", "boards", "roof"}), "The sloped beams " +
	"and cross boards support the roof of the barn.\n");
	add_item(({"walls", "wall"}), "The walls of the barn are " +
	"only a single board-width thick and have small gaps " +
	"between the slats.\n");
	add_item(({"slats"}), "The slats of wood that form the " +
	"the walls of the barn are thin and have slight gaps " +
	"between them.\n");
	add_item(({"gaps"}), "The gaps in the walls are rather small, " +
	"almost negligible, barely allowing any light to enter.\n");
}

//adds observeables for Maggot's barn, main rooms
void set_add_barn_main()
{
	add_item(({"floor"}), "The floor is covered with bits of " +
	"hay and dirt.\n");
	add_item(({"dirt"}), "The dirt looks mostly like soil from the fields, probably tracked in by the farm hands and animals.\n");
	add_item(({"hay", "bits", "scraps"}), "The scant scraps " +
	"of hay look like spills from the many feedings the animals " +
	"in the barn must receive.\n");
	add_item(({"shelves"}), "They are holding a few assorted " +
	"farming implements.\n");
	add_item(({"animals"}), "You don't see any animals in the " +
	"immediate area, however, from the smell and sounds, there " +
	"are probably animals in some of the stalls.\n");
	add_item(({"tools", "implements"}), "The tools are hanging " +
	"from the walls and rafters. There are also a few sitting on the " +
	"shelves. They are the kinds of inexplicably odd implements " +
	"one would expect to find on a farm.\n");
	add_item(({"stalls", "stall", "space", "spaces"}), "The animal stalls are all " +
	"on the western side of the barn. They smell strongly of " +
	"manure and old hay.\n");
}

//adds rtells for Maggot's barn
void set_add_rtells_barn()
{
	set_room_tell_time(120+random(15));
	add_room_tell("Barking can be heard in the distance.");
	add_room_tell("Scuffling can be heard from one of the stalls.");
	add_room_tell("'Bzzzzzzzzzzzz... Bzzzzz...'");
	add_room_tell("Something grunts loudly.\n");
}

