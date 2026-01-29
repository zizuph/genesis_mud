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

object riverboat;

start_ship()
{
  if (!riverboat) 
    {
      riverboat=clone_object("/d/Roke/Cirath/ships/riverboat/riverboat");
      riverboat->move(TO);
    }
  
  riverboat->start_ship(0);
}

void create_room()
{
  set_short("On a pier at southern trade-route");
  
  set_long(break_string(
           "You're standing on a wooden pier. Here you can, if you "+
           "want to pay the price, be shipped over to the other side "+
           "of the large river Durni. The river Sophri joins Durni at this location "+
           "and the result is a huge amount of streaming water. East lies "+
           "a small village and the trade-route continues southeast.\n"
           ,60));  

  add_item("road","This is the southern trade-route "+
           "that leads to Tyr.\n");
  add_item(({"river","water","stream","durni","Durni","sophri","Sophri"}),"The river "+
           "Durni flows west of you and Sophri to the north.\n");
  add_item("jungle","This is the jungle that covers the southern "+
           "part of Cirath.\n");
  add_item("village","It's a small village at the bank of the river Sophri../n");
  add_item(({"city","ciubori"}),"A cirathian city that lies south of here.\n");
  add_item("pier","It's a wooden pier.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r11","southeast");

  call_out("start_ship",1);
  add_prop(OBJ_S_WIZINFO,
           "type 'Call here start_ship' to restart the boat.\n"); 
  BEACH;

  reset_room();
}
