inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

int gate = 0;

string desc,
       str = "You are standing at Ciubori gate. The road leads north over a "+
             "drawbridge and becomes 'The Southern Trade Route' which leads "+
             "to the city Tyr, far away from here. South it leads further into "+
             "the city.";

object guard1,guard2;

change_room_desc()
{
  if (gate == 0) desc = " The drawbridge is currently down.\n";
  else desc = " The drawbridge is currently up.\n";

  set_long(break_string(str + desc + "\n",60));  
}

void
reset_room()
{
  gate = 0; /* 0 = open, 1 = closed*/
  change_room_desc();
}

void create_room()
{
  set_short("Ciubori gate");
  
  set_long(break_string(str + desc + "\n",60));  

  add_item("road","The road is made of sone bricks, neatly put together.\n");
  add_item(({"gate","bridge","drawbridge","draw-bridge"}),"The drawbridge protects the "+
    "city from unwelcome guests.\n");
  add_item(({"city","ciubori"}),"The second larges city in Cirath.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r01","north");
  add_exit(CIUBORI+"diamond/street3","south");

  reset_room();
}
