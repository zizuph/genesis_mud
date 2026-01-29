#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <ss_types.h>
#include <macros.h>
inherit SHADOW_IN;

void
init()
{
    ::init();
    ADA("climb");
}

void  
reset_shadow_room()
{
    return;
}

create_shadow_room()
{
    set_short("Down a pit trap");
    set_long("@@long_descr");
 
    add_item("walls","The walls down here are made of " +
        "limestone.  They seem capable of absorbing light. "+
        "You think they are rough enough to use to climb " +
        "out of the pit with.\n");
 
    add_prop(ROOM_I_LIGHT, 0);
    
    reset_shadow_room();
}

string
long_descr()
{
    return "You have fallen down a pit trap that seems to " +
      "be about fifteen feet deep.  The walls here are very " +
      "rough and you figure it would be an easy climb up and " +
      "out of the pit.  You'll have to be sure to avoid this " +
      "trap in the future.\n";
}

int climb(string str)
{
  if (str == "wall" || str == "out" || str == "up")
  {
    TP->catch_msg("You work your way out of the pit.\n");
    TP->move_living("climbing out of the pit",SROOM + "tunnel06.c");
  }
  else
  {
    TP->catch_msg("Climb what?\n");
  }
  return 1;
}

