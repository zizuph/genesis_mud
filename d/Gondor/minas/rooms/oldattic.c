inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_room()
{
  set_short("In the attic of an old building");
  set_long("@@long_func");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/minas/rooms/oldhouse","down",0);
  add_item(({"dust","floor"}),"The dusty floor reveals nothing of interest - only dust.\n");
  add_item("stairs","The stone stairs leading down are covered with dust.\n");
}

long_func()
{
  string longstr;
  string time;
  longstr = "You are in the dusty attic of the old house. "+
    "Cobwebs and dust everywhere indicates that this room hasn't been "+
    "used for a very long time. ";
  time = find_object(CLOCK)->query_time_of_day();
  if (time != "evening" && time != "night") longstr= longstr+"A little light comes streaming in through cracks in the ceiling above you. ";
  longstr = longstr+"There is nothing here of interest to you. The only exit is the stairs leading down.\n";
  return (break_string(longstr,75));
}

