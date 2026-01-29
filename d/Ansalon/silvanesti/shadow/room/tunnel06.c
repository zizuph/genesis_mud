#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <ss_types.h>
#include <macros.h>
inherit SHADOW_IN;

int trap;

void init()
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
    add_exit(SROOM + "tunnel05","north","@@trigger_trap");
    add_exit(SROOM + "tunnel04","south","@@trigger_trap");
    
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
        TP->catch_msg("You notice a pit trap covered by an " +
          "illusionary floor.\n");
      else
        TP->catch_msg("You notice the big pit in the middle of the room.\n");
    }
    else
    {
      if (trap == 0)
        TP->catch_msg("You notice the big pit in the middle of the room.\n");
      else
        TP->catch_msg("You fail to find a trap.\n");
    }
  }
  else
    TP->catch_msg("Find what?");
  return 1;
}

int disarm (string str)
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
          TP->catch_msg("Having misjudged the width of the pit, you " +
            "accidentally fall in.\n");
          TP->move_living("falling into the pit and hits the ground hard.\n",
            SROOM + "pit");
          TP->set_hp(TP->query_hp()-500);
          TP->catch_msg("You hit the ground below hard.\n");
          trap = 0;
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
  if (trap == 1)
  {
    if (TP->query_encumberance_weight() < 14)
    {
      return 0;
    }
    else
    {
      TP->catch_msg("The floor gives way beneath you and you fall " +
        "into the pit below.\n");
      TP->move_living("falling into the pit and hits the ground hard.\n",
        SROOM + "pit");
      TP->catch_msg("You hit the ground below hard.\n");
      TP->set_hp(TP->query_hp() - 500);
      trap = 0;
      return 1;
    }
  }
  else
  {
    TP->catch_msg("You hop over the pit.\n");
    return 0;
  }
}
