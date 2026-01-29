#include "../local.h"

inherit CITY_OUT;

string enter_house();

create_kalaman_room()
{
  set_short("Poor district");
  set_long("You stand in a soon to be poor district of Kalaman.\n");

  //add_exit("s06","west",0);
  add_exit("w01", "south",0);
  add_exit("s02", "east",0);

  add_item("house", "This is a common house that is the most common building " +
    "here in the poor district. The house is a three story building made out " +
    "stone and wood. The construction of the houses here might not be of the " +
    "best quality and finish but they do hold together and surve their very "  +
    "purpose.\n");
  add_cmd_item(({"house", "poor house", "common house"}), "enter", enter_house);  
}

string
enter_house()
{
  write ("You step up the porch and into the house.\n");

  tell_room(TO, QCTNAME(TP) + " leaves up the porch and into the house.\n", TP);
  TP->move_living("M", PROOM + "h03a", 1);
  return "";
}
