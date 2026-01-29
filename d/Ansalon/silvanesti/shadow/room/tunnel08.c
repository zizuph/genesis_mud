#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <ss_types.h>
#include <macros.h>
inherit SHADOW_IN;

int trap;

void
init()
{
  ::init();
  ADA("find");
  ADA("disarm");
}

void
reset_shadow_room()
{
    trap = 1;
    return;
}

create_shadow_room()
{
    set_short("Inside the tunnel system");
    set_long("@@long_descr");
    
    add_item(({"tunnel","tunnels","tunnel system"}), "The " +   
        "tunnels seem to twist and turn on their own whim. " +
        "Every tunnel looks as good as the next.\n");
    add_item("walls","The walls down here are made of " +
        "limestone.\n");
    
    
    add_prop(ROOM_I_LIGHT, 0);
    add_exit(SROOM + "tunnel13","east","@@trigger_trap");
    add_exit(SROOM + "tunnel05","northwest","@@trigger_trap");
    
    reset_shadow_room();
}
 
string
long_descr()
{
    return "You are in the tunnel system on the lower level " +
        "of the caverns.  No natural light is able to penetrate " +
        "this deep.  The tunnels seem to twist in a variety of " + 
        "directions, and you cannot see well enough to judge " +  
        "one over another.  You feel uncomfortable in the caves "+
        "as you feel the walls are absorbing the light.  It is "+ 
        "very difficult to see and you feel you should tread "+  
        "carefully.\n";
}

int find(string str)
{
  if (str == "trap" || str == "traps")
  {
    if (TP->query_skill(53) > random(50))
    {
      if (trap == 1)
        TP->catch_msg("You find an arrow trap in the wall.\n");
      else
        TP->catch_msg("You find a disarmed arrow trap.\n");
    }
    else
      TP->catch_msg("You fail to find a trap.\n");
  }
  else
    TP->catch_msg("Find what?\n");
  return 1;
}

int disarm(string str)
{
  if (str == "trap" || str == "traps")
  {
    if (TP->query_skill(53) > random(50))
    {
      if (trap == 1)
      {
        TP->catch_msg("You manage to disarm the trap.\n");
        trap = 0;
      }
      else
        TP->catch_msg("The trap is not armed.\n");
    }
    else
    {
      if (trap == 1)
      {
        if (random(2) == 0)
          TP->catch_msg("You fail to disarm the trap.\n");
        else
        {
          TP->catch_msg("In an attempt to disarm the trap, you " +
            "accidentally trigger it.  An arrow shoots out from " +
            "a hole behind you and sticks you right in the butt.\n");
          tell_room(TO,QCTNAME(TP) + " works on something on the " +
            "wall when an arrow shoots out and hits " +
            TP->query_objective() + " in the butt.\n",TP);
          TP->set_hp(TP->query_hp() - 250);
        }
      }
      else
        TP->catch_msg("You fail to disarm the trap.\n");
    }
  }
  else
    TP->catch_msg("Disarm what?\n");
  return 1;
}

int
trigger_trap()
{
  if (trap == 0)
    return 0;
  else
  {
    tell_room(TO,"You turn just in time to see an arrow heading straight at ", 0);
    TP->catch_msg("you!\n");
    tell_room(TO,QCTNAME(TP) + ".\n",TP);
    if (random(2) == 0) //change to check for shield
    {
      string location;
      int locnum = random(5);
      if (locnum == 0)
        location = "left arm";
      else if (locnum == 1)
        location = "right arm";
      else if (locnum == 2)
        location = "chest";
      else if (locnum == 3)
        location = "left leg";
      else
        location = "right leg";

      TP->catch_msg("The arrow strikes you in your " + location + ".\n");
      tell_room(TO,"The arrow hits " + TP->query_objective() + " in " +
        TP->query_possessive() + location + ".\n", TP);
      TP->set_hp(TP->query_hp() - 250);
    }
    else
    {
      TP->catch_msg("You raise your shield in time and block the arrow.\n");
      tell_room(TO,QCTNAME(TP) + " raises " + TP->query_possessive() + 
        " shield in time and blocks the arrow.\n",TP);
    }
    return 0;
  }
}
