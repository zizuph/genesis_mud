inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

object guard1,guard2;

void
reset_room()
{

  if (!guard1 && !guard2)
  {
    guard1=clone_object(MONSTER+"c_guard");
    guard1->move(this_object());
    guard2=clone_object(MONSTER+"c_guard");
    guard2->move(this_object());
    tell_room(TO,"Two guardians take their posts.\n");
  }
}

void create_room()
{
  set_short("On the southern trade-route");
  
  set_long(break_string(
           "You travel on a road south of a dark green forest surrounded "+
           "fog. South of the road is a stream and the road continues over "+
           "it by a wooden bridge. To your southeast lies a large jungle.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item(({"water","stream"}),"The stream flows fast and the water is "+
           "clear.\n");
  add_item("jungle","This is the west part of the large jungles that grows "+
           "on the southeastern part of Athas.\n");
  add_item("forest","It's a dark green forest. Somewhat threatening with all "+
          "that fog around it.\n");
  add_item(({"fog","mist"}),"It is surrounding the forest.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");
  add_item("bridge","The bridge is made of wood and is well-built. It looks safe "+
           "to pass over.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r20","east");
  add_exit(S_TRADE+"r22","south");

  reset_room();
}
