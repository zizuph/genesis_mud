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
	"as this path wanders further away from the encampment.  "+
	"To the south herds of cattle, horses and sheep can be seen "+
	"grazing on the sparse grass that has broken through the "+
	"crust of old snow.  To the northwest lies a small clump of "+
	"pure white yurts, while further to the west lies the open "+
	"steppe.\n");

   add_exit(PATH + "encampment/camp22","west");
  add_exit(PATH + "encampment/camp14","east");
  add_exit(PATH + "encampment/camp20","northwest");

}

