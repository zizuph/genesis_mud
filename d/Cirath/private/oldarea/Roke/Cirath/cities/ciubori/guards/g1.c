inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

object guard1,guard2,guard3;

void
reset_room()
{

  if (!guard1 && !guard2 && !guard3)
  {
    guard1=clone_object(MONSTER+"c_guard");
    guard1->move(this_object());
    guard2=clone_object(MONSTER+"c_guard");
    guard2->move(this_object());
    guard3=clone_object(MONSTER+"c_guard");
    guard3->move(this_object());
    tell_room(TO,"Three guardians take their posts.\n");
  }
}

void create_room()
{
  set_short("guard tower base");
  
  set_long(break_string(
           "This is the ground floor inside one of the four towers that are used "+
           "by the guards of Ciubori to scan the surroundings in order to discover "+
           "enemies early. The tower itself is made by stone blocks, neatly put "+
           "together. Here is the place where the guards, which aren't at duty, rest "+
           "and eat.\n"
           ,60));  

  add_item(({"stone","stones","block","blocks"}),"They are perfectly put together.\n");
  add_item("tower","You are standing at the bottom level of the tower.\n");
  add_item("ciubori","The second largest city in Cirath.\n");

  INSIDE;

  add_exit(CIUBORI+"topaz/street1","southeast");
  add_exit(CIUBORI+"guards/t1","up");

  reset_room();
}
