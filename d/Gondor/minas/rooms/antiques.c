inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h";

create_room()
{
  set_short("An antiques-shop in Minas Tirith");
  set_long("@@long_func");
  add_exit("/d/Gondor/minas/s1crc2","south");
  add_prop(ROOM_I_INSIDE,1);
}

long_func()
{
  return "The antiques-shop is not opened yet.\n";
}
