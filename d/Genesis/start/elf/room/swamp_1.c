#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "swamp.h"

#pragma save_binary

inherit ELFROOM;

#define WEST  ROOMDIR + "swamp_path_3"

#define LONG \
  "The swamp fills the land to the east of you, and "+\
  "a small, muddy path disappears into the forest in the west.\n"

#define PATH_ITEM ({"path", "swamp path", "muddy rut", "ruts", "rut"})
#define PATH_DESC \
  "The path is only a deep rut of wet mud, winding an ambling "+\
  "way through the forest.\n"


create_room()
{
  set_short(N_KNOW(SWAMP_NAT_SHORT, SWAMP_FOR_SHORT));
  set_long( N_KNOW(WRAP(SWAMP_BRINK_NAT_LONG + LONG),
		   WRAP(SWAMP_BRINK_FOR_LONG + LONG)));

  SWAMP_STD_ITEMS;
  add_item(  PATH_ITEM, WRAP(  PATH_DESC));

  add_exit(WEST,      "west",  0);

  stock();
}


reset_room()
{
  stock();
}


stock()
{
  restock_object(MONSTERDIR + "dragonfly", 3, "dragonfly");
}