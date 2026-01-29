#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

string long_descr();

create_kalaman_room()
{
  set_short("Poor district east street");
  set_long(long_descr);

  //add_exit("s07","north",0);
  add_exit("s08", "west" ,0);
}

string
long_descr()
{
  return "You stand in the middle of a street in the poor district of Kalaman. " +
    "These streets are not as well kept as the once in the richer parts of the city " +
    "and the people here are not as cheery. All around the street you see three story " +
    "stone and wooden buildings, homes of the people that live and work in Kalaman.\n";
}
