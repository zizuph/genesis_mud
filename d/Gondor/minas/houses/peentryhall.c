inherit "/d/Gondor/common/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define TP this_player()
#define TO this_object()
#define BS(xxx) break_string(xxx,70)

create_room()
{
  set_short("The entrance hall in the first floor of a house in Minas Tirith");
  set_long("@@describe");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,"@@test_time");
  add_exit("/d/Gondor/minas/houses/pehall2","up",0,0);
  add_exit("/d/Gondor/minas/houses/pekitchen","north",0,0);
  add_exit("/d/Gondor/minas/houses/pelivroom","west",0,0);
  add_item(({"staircase","stairs","stair"}),
    "The spiral staircase of stone leads up to the second floor.\n");
  clone_object("/d/Gondor/minas/houses/pedoorin")->move(TO);
}

describe()
{
  string longstr;
  longstr = "You are in the entrance hall in the first floor of the house. "+
    "There's a doorway leading north into the kitchen, and another leading "+
    "west into the livingroom. A spiral staircase leads up to the second floor. ";
  if (tod()=="night" || tod()=="early morning")
    longstr= longstr+"Now as it is "+tod()+", the house is quiet and dark. ";
  if (tod()=="morning" || tod()=="evening")
    longstr =longstr+"Now in the "+tod()+" you hear people in the house. ";
  if (tod()=="noon")
    longstr = longstr+"It is noon, and the house is quiet. ";
  longstr = longstr+"To the south is the main door out of the house.\n";
  return BS(longstr);
}

test_time()
{
  if (tod()=="night" || tod()=="early morning") return 0;
  return 1;
}
