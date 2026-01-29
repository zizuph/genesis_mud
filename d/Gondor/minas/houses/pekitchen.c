inherit "/d/Gondor/common/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define TP this_player()
#define TO this_object()
#define BS(xxx) break_string(xxx,70)

create_room()
{
  set_short("The kitchen in the first floor of a house in Minas Tirith");
  set_long("@@describe");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,"@@test_time");
  add_exit("/d/Gondor/minas/houses/peentryhall","south",0,0);
  add_exit("/d/Gondor/minas/houses/peservant","west",0,0);
  add_item(({"equipment","bowls"}),"They are used for cooking food.\n");
  add_item(({"shelves","racks"}),"The only thing you see on the shelves and racks is cooking equipment.\n");
  add_item("hooks","Bowls and cooking equipment are hanging from the hooks.\n");
}

describe()
{
  string longstr;
  longstr = "You are in a nice kitchen, a little, but convenient one. "+
    "There are bowls and cooking equipment everywhere; hanging from hooks "+
    "in the ceiling, stacked on racks and stuffed in shelves. "+
    "There's a doorway leading south into the entry hall, and another leading "+
    "west into the servant's bedroom. ";
  if (tod()=="night" || tod()=="early morning")
    longstr= longstr+"Now as it is "+tod()+", the house is quiet and dark. ";
  if (tod()=="morning" || tod()=="evening")
    longstr =longstr+"It is "+tod()+". You hear people somewhere in the house. ";
  if (tod()=="noon")
    longstr = longstr+"It is noon, and the house is quiet. ";
  longstr = longstr+"To the south is the main door out of the house.\n";
  return BS(longstr);
}

init()
{
  ::init();
  add_action("try_get","get");
  add_action("try_get","take");
  add_action("pull_hook","pull");
}

try_get(string str)
{
  if (!str) {
    write("Get what?\n");
    return 1;
    }
  if (str== "bowls" || str == "cooking equipment" || str == "equipment" || str == "bowl") {
    write("You grab one of the bowls on the shelf, and accidentally tear down\n"+
      "several other bowls, pans and pots, making terribly lot of noise!!\n");
    say(QCTNAME(TP)+" accidentally tears down several bowls, pans and pots\n"+
      "trying to get a bowl from the shelves!!\n",TP);
    return 1;
    }
  return 0;
}

pull_hook(string str)
{
  if (!str) {
    write("Pull what?\n");
    return 1;
    }
  if (str == "hook" || str == "hooks") {
    write("You try to pull one of the hooks, but nothing happens.\n");
    say(QCTNAME(TP)+" tries to pull one of the hooks in the ceiling, but nothing happens.\n",TP);
    return 1;
    }
  if (str == "bowls" || str == "equipment" || str=="bowl") {
    try_get("bowl");
    return 1;
    }
  return 0;
}
 
test_time()
{
  if (tod()=="night" || tod()=="early morning") return 0;
  return 1;
}
