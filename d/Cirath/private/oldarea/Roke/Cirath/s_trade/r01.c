inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

object monster,guard;

void
reset_room()
{

  if (!monster)
  {
    tell_room(TO,"A traveller arrives.\n");
    monster=clone_object(MONSTER+"traveller");
    monster->move(this_object());
  }

  if (!guard)
  {
    guard=clone_object(MONSTER+"c_guard");
    guard->move(this_object());
    tell_room(TO,"A guard takes his post.\n");
  }
}

void create_room()
{
  set_short("On the southern trade-route");
  
  set_long(break_string(
           "You're standing on a road just north of the city Ci'u'bori. "+
           "The city is placed in the mouth of the large river Durni. "+
           "This makes it very easy to defend, since it is water all "+
           "around it. There is a drawbridge leading south into the "+
           "town and north, the road leads over one of the many streams "+
           "in the marches that dominates the river mouth.\n"
           ,60));  

  add_item("road","This is the beginning of the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni"}),"This is the "+
           "mouth of the large river Durni.\n");
  add_item(({"bridge","drawbridge"}),"This bridge leads into the "+
           "the city, it's currently down.\n");
  add_item(({"march","marches","swamp"}),"The area is full of water "+
           "and the ground is not very reliable.\n");
  add_item(({"city","ciubori","town","Ciubori"}),"This is the third "+
           "city of Cirath. It's magnifique.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r02","north");
  add_exit(CIUBORI+"gate","south","@@query_gate");

  reset_room();
}

void
init()
{
  ::init();
  add_action("guardpass","lower");
}

int
query_gate()
{
  if (!guard)
    write("The draw-bridge is up and you don't know how to lower it.\n");
  else
    write("The draw-bridge is up. Type 'lower bridge' to make the guards lower it.\n");

  return 1;
}

int
guardpass(string str)
{
  string race = TP->query_race_name();

  if (str=="bridge")
  {
    if (MAL("guard"))
    {
      if (race == "goblin" || race == "dwarf")
      {
        write("You ask the guard if he can lower the draw-bridge.\n"+
          "The guard says: Sorry, I don't like your looks and will not let you pass.\n");
        say(QCTNAME(TP)+" asks the guard to lower the draw-bridge.\n"+
          "The guard answers: Sorry, I don't like your looks and will not let you pass.\n");
        return 1;
      }
      write("You ask the guard to lower the bridge.\n"+
            "The guard eyes you suspiciously and draws the conclusion that it's safe.\n"+
            "The guard shouts: Ok lads! Lower the bridge, a traveller wants to pass!\n"+
            "The bridge starts to lower down...\n");
      say(QCTNAME(TP)+" asks the guard to lower the bridge.\n"+
            "The guard eyes "+QTNAME(TP)+" suspiciously and draws the conclusion that it's safe.\n"+
            "The guard shouts: Ok lads! Lower the bridge, a traveller wants to pass!\n"+
            "The bridge starts to lower down...\n");
      call_out("bridge_down1",5);
      return 1;
    }
  }
  write("I don't understand what you mean.\n");
  return 1;
}

int bridge_down1()
{
  tell_room(TO,"The bridge lowers down...\n");
  call_out("bridge_down",5);
  return 1;
}

int bridge_down()
{
  write("The draw-bridge is lowered and the guard waves you through.\n");
  say("The draw-bridge is lowered and the guard waves "+QTNAME(TP)+" through.\n");
  TP->move_living("over the bridge",CIUBORI+"gate");
  tell_room(TO,"As soon "+QTNAME(TP)+" has walked over the bridge. The bridge is pulled up again.\n");
  tell_room(TO,"The guard smiles gleefully.\n");
  return 1;
}
