#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "gibber_lair.h"

#pragma save_binary

inherit ELFROOM;

#define NORTHEAST ROOMDIR + "gibber_lair_3"
#define SOUTH     ROOMDIR + "gibber_lair_5"


#define GIBBER_NUM 2

create_room()
{
  set_short(N_KNOW(GIBBER_LAIR_NAT_SHORT, GIBBER_LAIR_FOR_SHORT));
  set_long( N_KNOW(WRAP(GIBBER_LAIR_NAT_LONG),
		   WRAP(GIBBER_LAIR_FOR_LONG)));

  GIBBER_LAIR_STD_ITEMS;
  GIBBER_LAIR_STD_PROPERTIES;

  add_exit(NORTHEAST, "northeast", 0);
  add_exit(SOUTH,     "south",     0);

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
    
  