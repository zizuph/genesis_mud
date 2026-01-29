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
  set_short("On a pier at southern trade-route");
  
  set_long(break_string(
           "This is a wooden pier on the west side of the river Durni. "+
           "The river is quite wide here since the river Sophri joins "+
           "Durni here. A small boat uses to take travellers over to "+
           "the other side. To the southwest lies a little village that "+
           "looks rather poor.\n"
           ,60));  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni","sophri","Sophri"}),"The river "+
           "Durni flows west of you and Sophri to the north.\n");
  add_item("village","It's one of the poor villages that are inhabited by "+
           "the 'inlanders' as the cirathian people prefer to call them./n");
  add_item("pier","It's a wooden pier.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r14","southwest");
  BEACH;

  reset_room();
}
