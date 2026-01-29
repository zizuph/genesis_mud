#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "gibber_lair.h"

#pragma save_binary

inherit ELFROOM;

#define SOUTHWEST ROOMDIR + "gibber_lair_5"
#define NORTHEAST ROOMDIR + "gibber_lair_8"
#define UP        ROOMDIR + "gibber_lair_6"


#define GIBBER_NUM 3

create_room()
{
  set_short(N_KNOW(GIBBER_LAIR_NAT_SHORT, GIBBER_LAIR_FOR_SHORT));
  set_long( N_KNOW(WRAP(GIBBER_LAIR_NAT_LONG),
		   WRAP(GIBBER_LAIR_FOR_LONG)));

  GIBBER_LAIR_STD_ITEMS;
  GIBBER_LAIR_STD_PROPERTIES;

  add_exit(SOUTHWEST, "southwest", 0);
  add_exit(NORTHEAST, "northeast", 0);
  add_exit(UP,        "up",        0);

  stock();
}


reset_room()
{
  stock();
}


stock()
{
  restock_object(MONSTERDIR + "gibberer", GIBBER_NUM, "gibberer");
}
    
  