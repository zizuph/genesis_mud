inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/mobber.h"

create_room()
{
  set_short("Barbarian camp");
   set_long("The frequency of yurts, as well as people has decreased "+
	"as this path wanders further away from the encampment.  Dark "+
	"scars from old gullies make jagged scars across the ground "+
	"here.  Small clumps of bright blue and pink, blooms of early "+
	"crocus and dwarf lily struggle against the sharp cold.\n");

  add_exit(PATH + "encampment/camp11","west");  
  add_exit(PATH + "encampment/camp18","east");

}

