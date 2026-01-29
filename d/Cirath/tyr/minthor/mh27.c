inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"


create_room()
 {
  set_short("North Hall");
  set_long("You are in a short corridor leading north and south.  From "
	+"the north you can see what appears to be a soft light, while "
	+"to the south you can see the large staircase leading to the "
	+"second floor.  There are a few paintings along the walls here "
	+"depicting people of some sort.  Other than that it is very "
	+"bare.\n");
  add_item("corridor","It leads north and south.\n");
  add_item(({"staircase","stairs"}),"You cansee the large metal and "
	+"stone staircase to your south, you can't see any details from "
	+"here though.\n");
  add_item(({"painting","paintings"}),"They are all portaits of various "
	+"men.  Each one has a name at the bottom.  They look to be the "
	+"patriarchs of the Minthor family.\n");
  add_item("ceiling","It is above you.\n");
  add_item("plants","There are a large variety of plants, none which you "
        +"are familiar with.  In a land with virtually no water, this is "
        +"an exercise in wealth and waste.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  add_item(({"windows","window","crystalline windows"}),"They appear to "
	+"be made of some form of strange translucent crystal that only "
	+"allows a fraction of the overpowering sun into the room.\n");
  add_item(({"chair","chairs","padded chairs","padded chair"}),"These "
	+"chairs are very soft and comfortable, they seem to almost mold "
	+"to your body.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
  add_exit(TZ_MINTHOR + "mh20","north",0);
  add_exit(TZ_MINTHOR + "mh13","south",0);

}

