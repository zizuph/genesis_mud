inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

object guard1;

void
reset_room()
{

  if (!guard1)
  {
    guard1=clone_object(MONSTER+"c_guard");
    guard1->move(this_object());
  }
}

void create_room()
{
  set_short("guard tower");
  
  set_long(break_string(
           "You stand at the top of the southwestern tower in Ciubori. You have "+
           "an excellent view from here. North, you can see the city and to your "+
           "south lies the pier and the ocean.\n"
           ,60));  

  add_item("pier","It's where the boats load and unload cargo and passagers.\n");
  add_item("ocean","It seems never ending.\n");
  add_item("tower","You are standing at the top level of the tower.\n");
  add_item("ciubori","The third largest city in Cirath.\n");

  OUTSIDE;

  add_exit(CIUBORI+"guards/g4","down");

  reset_room();
}
