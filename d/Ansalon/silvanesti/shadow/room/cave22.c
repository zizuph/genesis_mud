#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <ss_types.h>
#include <macros.h>
inherit SHADOW_IN;

object obj1,obj2,obj3;

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
    if(!objectp(obj1))
    {
      obj1 = clone_object(SLIVE + "titanic");
      obj1->move_living("xxx",TO);
    }
    if(!objectp(obj2))
    {
      obj2= clone_object(SLIVE + "warrior");
      obj2->move_living("xxx",TO);
    }
    if(!objectp(obj3))
    {
      obj3 = clone_object(SLIVE + "warrior");
      obj3->move_living("xxx",TO);
    }
    return;
}

create_shadow_room()
{
    set_short("Hidden room in the shadow caves");
    set_long("@@long_descr");
 
    add_item("walls","The walls down here are made of " +
        "limestone.  They seem capable of absorbing light. "+
        "@@wall_bump");
    add_item("shadows","You take a closer look at the shadowy "+
        "figures moving in the dark, but can't quite be sure "+
        "what they are.\n");
    add_item(({"bump","button"}), "@@find_bump");
 
    add_prop(ROOM_I_LIGHT, 0);
    
    reset_shadow_room();
}

string
long_descr()
{
    return "You have found the hidden lair where the head " +
        "warrior of the community resides.  There is a nest " +
        "made of cloth and fur in the corner of the room, as " +
        "well as some stone furniture and woven mats to " +
        "decorate the room.  You feel a small breeze coming " +
        "from above and you assume this room is connected " +
        "to the outside, though you cannot find the opening.\n";
}

int pull(string str)
{
 if (str == "button" || str == "bump")
 {
   if (TP->query_max_fatigue()/TP->query_fatigue() < 3)
   {
     write("You don't seem to be able to pull it in any further.  " +
         "Perhaps you should try something else.\n");
     say(QCTNAME(TP) + " fiddles around with the wall, but nothing " +
         "happens.\n");
   }
   else
   {
     write("You tiredly search the wall for a button to pull " +
       "but your weariness prevents you from finding it.\n");
     say(QCTNAME(TP) + " fiddles around with the wall, but nothing " +
        "happens.\n");
   }
 }
 else
 {
   write("Pull what?\n");
 }
 return 1;
}


int push(string str)
{
  if (str != "button" && str != "bump")
  {
   write("Push what?\n");
   return 1;
 }
  if (TP->query_max_fatigue()/TP->query_fatigue() < 3)
 {
   write("Suddenly the wall to the north begins to rotate and "+
       "pushes you to the other side.\n");
   say("Suddenly the wall to the north begins to rotate and " +
       "pushes " + QCTNAME(TP) + " to the other side.\n");
   TP->move_living("through the wall",SROOM + "cave20.c");
 }
 else
 {
   write("You tiredly search the wall for a button to push " +
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

