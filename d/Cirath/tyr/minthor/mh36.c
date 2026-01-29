inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "defs.h"

 
create_room()
 {
  set_short("Landing");
  set_long("You are on a small landing above the staircase in the Minthor "
	+"House.  Around you, you can see dust and what appears to be "
	+"old, out of style dishes and accessories for the house.  "
	+"Most of the things are either piled up on the floor or in "
	+"one of the various chests lying around.  The room extends "
	+"southward into a dark area of the attic.\n");
  add_item(({"stairs","staircase"}),"The staircase seems to have gotten "
	+"little use lately as there is dust all over the steps.\n");
  add_item("dust","There is a lot of dust on the floor here.  It all "
	+"looks relatively undisturbed at first.  Upon careful "
	+"examination, though, you notice faint footprints in the "
	+"dust.\n");
  add_item(({"wall","walls"}),"The walls stretch out around you.\n");
  add_item(({"footprint","footprints"}),"They are footprints the size "
	+"of a young man or possibly a woman.  You can't be absolutely "
	+"sure because they are so faint.\n");
  add_item(({"dishes","accessories","things"}),"There is a large variety "
	+"of miscellaneous dishes and things on the floor or in chests.\n");
  add_item(({"chest","chests"}),"There are a number of chests lying on "
	+"the floor and are apparently used to store things.\n");
  INSIDE
  add_exit(TZ_MINTHOR + "mh37","south");
  add_exit(TZ_MINTHOR + "stairs","down");
}


