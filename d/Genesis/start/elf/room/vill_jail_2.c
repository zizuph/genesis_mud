#include "../stddefs.h"
#include "/sys/stdproperties.h"
#include "vill_jail.h"

#pragma save_binary

inherit ELFROOM;

#define EAST     ROOMDIR + "vill_jail_1"
#define WEST     ROOMDIR + "vill_jail_3"

  
create_room()
{
  set_short(N_KNOW(JAIL_NAT_SHORT, JAIL_FOR_SHORT));
  set_long( N_KNOW(WRAP(JAIL_NAT_LONG),
		   WRAP(JAIL_FOR_LONG)));

  add_exit(EAST,    "east", 0);
  add_exit(WEST,    "west", NYI);

  JAIL_STD_ITEMS;

  add_prop(ROOM_I_INSIDE, 1);

  stock();
}

void stock()
{
  restock_object(OBJDIR     + "labyrinth", 1, "labyrinth");
  restock_object(MONSTERDIR + "sumo",      1, "sumo");
}

reset_room()
{
  stock();
}
