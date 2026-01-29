#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "gibber_lair.h"

#pragma save_binary

inherit ELFROOM;

#define WEST      ROOMDIR + "cairn"
#define EAST      ROOMDIR + "gibber_lair_2"
#define SOUTHEAST ROOMDIR + "gibber_lair_3"

#define LONG \
  "From west a little light filters in.\n"
#define LIGHT_ITEM ({"light", "sunlight"})
#define LIGHT_DESC \
  "It is weak, it is pale, but it definitively is light.\n"

create_room()
{
  set_short(N_KNOW(GIBBER_LAIR_NAT_SHORT, GIBBER_LAIR_FOR_SHORT));
  set_long( N_KNOW(WRAP(GIBBER_LAIR_NAT_LONG + LONG),
		   WRAP(GIBBER_LAIR_FOR_LONG + LONG)));

  GIBBER_LAIR_STD_ITEMS;
  add_item(LIGHT_ITEM, WRAP(LIGHT_DESC));

  add_prop(ROOM_I_INSIDE, 1);      

  add_exit(WEST,      "west", 0);
  add_exit(EAST,      "east", 0);
  add_exit(SOUTHEAST, "southeast", 0);

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
    
  