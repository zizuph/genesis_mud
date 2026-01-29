#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "gibber_lair.h"

#pragma save_binary

inherit ELFROOM;

#define WEST      ROOMDIR + "gibber_lair_1"
#define SOUTHWEST ROOMDIR + "gibber_lair_3"


create_room()
{
  set_short(N_KNOW(GIBBER_LAIR_NAT_SHORT, GIBBER_LAIR_FOR_SHORT));
  set_long( N_KNOW(WRAP(GIBBER_LAIR_NAT_LONG),
		   WRAP(GIBBER_LAIR_FOR_LONG)));

  GIBBER_LAIR_STD_ITEMS;
  GIBBER_LAIR_STD_PROPERTIES;

  add_exit(WEST,      "west", 0);
  add_exit(SOUTHWEST, "southwest", 0);

  stock();
}


reset_room()
{
  stock();
}


stock()
{
  object obj;

  if (!present("gibberer")) {
    obj = clone_object(MONSTERDIR + "gibberer");
    obj->move(this_object());
  }
}
    
  