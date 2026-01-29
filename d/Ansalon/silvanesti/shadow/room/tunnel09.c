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
    add_exit(SROOM + "tunnel10","north","@@trigger_trap");
    add_exit(SROOM + "tunnel04","northwest","@@trigger_trap");
    add_exit(SROOM + "tunnel15","southeast","@@trigger_trap");
    
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


int
trigger_trap()
{
  if (trap == 1)
  {
    tell_room(TO,"Suddenly a gust of wind fills the tunnel.\n",0);
    if (TP->query_encumberance_weight() < 86)
    {
      TP->catch_msg("The wind lifts you off your feet and slams you " +
        "into the wall in the next room.\n");
      TP->set_hp(TP->query_hp()-500);
      TP->move_living("southeast carried violently by the wind.",SROOM + "tunnel15");
      tell_room(TO,QCTNAME(TP) + " is lifted by the wind an thrown " +
        "out of the room to the southeast.\n");
      if (TP->query_hp() <= 0)
        TP->do_die();
      trap = 0;
      return 1;
    }
    else
    {
      TP->catch_msg("The wind tries to pick you up, but " +
        "luckily you weigh more than it can carry.\n");
      tell_room(TO,"The wind seems to focus around " + QCTNAME(TP) +
        ", but nothing happens.\n",TP);
      trap = 0;
      return 0;
    }
  }
  return 0;
}

int find (string str)
{
 if (str == "trap" || str == "traps")
 {
  if(TP->query_skill(53) > random(50))
  {
    if (trap == 1)
      TP->catch_msg("You find a loose stone that triggers a wind trap.\n");
    else
      TP->catch_msg("You find a stone pushed in the floor, the trap looks tripped.\n");
  }
  else
    TP->catch_msg("You fail to find a trap.\n");
 }
 else
 {
  TP->catch_msg("Find what?\n");
 }
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
        {
          TP->catch_msg("You fail to disarm the trap.\n");
        }
        else
        {
          TP->catch_msg("In an attempt to disarm the trap, you accidentally trigger it.\n");
          tell_room(TO,"Suddenly a gust of wind fills the tunnel.\n",0);
          if (TP->query_encumberance_weight() < 86)
          {
            TP->catch_msg("The wind lifts you off your feet and slams you " +
              "into the wall in the next room.\n");
            TP->set_hp(TP->query_hp()-500);
            TP->move_living("southeast carried violently by the wind.",SROOM +
              "tunnel15");
            tell_room(TO,QCTNAME(TP) + " is lifted by the wind an thrown " +
              "out of the room to the southeast.\n");
            if (TP->query_hp() <= 0)
              TP->do_die();
            trap = 0;
            return 1;
          }
          else
          {
            TP->catch_msg("The wind tries to pick you up, but " +
              "luckily you weigh more than it can carry.\n");
            tell_room(TO,"The wind seems to focus around " + QCTNAME(TP) +
              ", but nothing happens.\n",TP);
            trap = 0;
            return 1;
          }
          trap = 0;
        }
      }
      else
      {
        TP->catch_msg("You fail to disarm the trap.\n");
      }
    }
  }
  else
  {
    TP->catch_msg("Disarm what?\n");
  }
  return 1;
}


