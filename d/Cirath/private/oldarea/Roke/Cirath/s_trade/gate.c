inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

object guard;

void
reset_room()
{
  if (!guard)
  {
    guard=clone_object(MONSTER+"c_guard");
    guard->move(this_object());
    tell_room(TO,"A guard take his post.\n");
  }
}

void create_room()
{
  set_short("Cirath gate");
  
  set_long(break_string(
    "You are standing inside the gigantic wall that splits the island "+
    "of Athas into two parts. The wall was built long ago to protect "+
    "the citizens of the kingdom Cirath from the wild tribes of nomads "+
    "that lives in the desert west of it. Parts of the walls are still "+
    "fuctioning, but the nomads have breached it further north, it is said "+
    "anyway. North and south lies the guard houses and the gate, which leads "+
    "into the mountain on which base the wall is built on, and further into "+
    "kingdom, lies to the east. West lies the sun-dried desert.\n",60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"mountain","mountains","ridge"}),"The tunnel leads through it.\n");
  add_item(({"cave","tunnel","opening"}),"The tunnel doesn't seem natural. "+
    "Someone ore something have made it. It leads through the mountain.\n");
  add_item("wall","This is the mighty wall that in the old days protected "+
    "the cirathians from the wild savages of the west.\n");
  add_item("gate","It's large and made of steel. Looks robust.\n");
  add_item(({"guardhouse","house","guardhouses","houses"}),"It's where the guards "+
    "rest.\n");

  INSIDE;

  add_exit(S_TRADE+"c4","east","@@query_gate");
  add_exit(S_TRADE+"r37","west");
  add_exit(S_TRADE+"gh1","north");
  add_exit(S_TRADE+"gh2","south");

  reset_room();
}

void
init()
{
  ::init();
  add_action("guardpass","pass");
}

int
query_gate()
{
  if (!guard)
    write("The gate is closed and you don't know how to open it.\n");
  else
    write("The gate is closed. Type 'pass gate' to make the guard open it.\n");

  return 1;
}

int
guardpass(string str)
{
  string race = TP->query_race_name();

  if (str=="gate")
  {
    if (MAL("guard"))
    {
      if (race == "goblin" || race == "dwarf")
      {
        write("You ask the guard if he can open the gate.\n"+
          "The guard says: Sorry, I don't like your looks and will not let you pass.\n");
        say(QCTNAME(TP)+" asks the guard to open the gate.\n"+
          "The guard answers: Sorry, I don't like your looks and will not let you pass.\n");
        return 1;
      }
      else if (race == "gnome" || race == "hobbit")
      {
        write("You ask the guard if he can open the gate.\n"+
          "The guard says: HA! you little puny creature, go to mom instead. You won't pass these gates!\n");
        say(QCTNAME(TP)+" asks the guard to open the gate.\n"+
            "The guard answers: HA! you little puny creature, go to mom instead. You won't pass these gates!\n");
        return 1;
      }

      write("You ask the guard to open the gate.\n"+
            "The guard opens it and waves you through.\n");
      say(QCTNAME(TP)+" asks the guard to open the gate.\n"+
        "The guard opens the gate and waves "+TP->query_objective()+" through.\n");
      TP->move_living("through the gate",S_TRADE+"c4");

      return 1;
    }
  }
  write("I don't understand what you mean.\n");
  return 1;
}
