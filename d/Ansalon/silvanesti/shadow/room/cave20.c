#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <ss_types.h>
#include <macros.h>
inherit SHADOW_IN;

void
init()
{
    ::init();
    ADA("push");
    ADA("pull");
}

void  
reset_shadow_room()
{
    return;
}

create_shadow_room()
{
    set_short("In the shadow caves");
    set_long("@@long_descr");
 
    add_item("walls","The walls down here are made of " +
        "limestone.  They seem capable of absorbing light. "+
        "@@wall_bump");
    add_item("shadows","You take a closer look at the shadowy "+
        "figures moving in the dark, but can't quite be sure "+
        "what they are.\n");
    add_item(({"bump","button"}),"@@find_bump");
 
    add_prop(ROOM_I_LIGHT, 0);
    add_exit(SROOM + "cave19","north",0);
    add_exit(SROOM + "cave21","east",0);
    add_exit(SROOM + "cave17","west",0);
    
    reset_shadow_room();
}

string
long_descr()
{
    return "You are in the shadow caves below the Silvanesti " +
        "forest.  No natural light is able to penetrate this " +  
        "deep.  The tunnels open up here to a large cave where " +
        "there is plenty of room to move about.  You feel " +
        "uncomfortable in the caves as you feel the walls are " +
        "absorbing the light.  Unnatural shadows seem to move " +
        "around.  Wait... those aren't shadows!\n";
}

int push(string str)
{
  if (str == "button" || str == "bump")
  {
    if (TP->query_max_fatigue()/TP->query_fatigue() < 3)
    {
    write("You don't seem to be able to push it in any further.  " +
        "Perhaps you should try something else.\n");
    say(QCTNAME(TP) + " fiddles around with the wall, but nothing " +
        "happens.\n");
    }
    else
    {
     write("You tiredly search the wall for a button to push " +
       "but your weariness prevents you from finding it.\n");
     say(QCTNAME(TP) + " fiddles around with the wall, but nothing " +
       "happens.\n");
   }
  }
  else
  {
    write("Push what?\n");
  }    
  return 1;
}

int pull(string str)
{
  if (str != "button" && str != "bump")
  {
    write("Pull what?\n");
    return 1;
  }
  if (TP->query_max_fatigue()/TP->query_fatigue() < 3)
  {
    write("Suddenly the wall to the south begins to rotate and "+
      "pushes you to the other side.\n");
  say("Suddenly the wall to the south begins to rotate and " +
      "pushes " + QCTNAME(TP) + " to the other side.\n");
  TP->move_living("through the wall",SROOM + "cave22.c");
  }
  else
  {
   write("You tiredly search the wall for a button to pull " +
     "but your weariness prevents you from finding it.\n");
   say(QCTNAME(TP) + " fiddles around with the wall, but nothing " + 
     "happens.\n");
 }
  return 1;
}

string
find_bump()
{
 if (TP->query_max_fatigue()/TP->query_fatigue() < 3)
   return "After examining the bump closer you determine it is " +
       "more of a button than a bump.\n";
 else
   return "You are too tired to find a bump.\n";
}

string
wall_bump()
{
 if (TP->query_max_fatigue()/TP->query_fatigue() < 3)
   return "You also notice that the north wall here has a " +
       "strange looking bump on it.\n";
 else
   return "\n";
}
