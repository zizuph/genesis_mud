inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On the southern trade-route");
  
  set_long(break_string(
           "You are travelling on a large and neatly bricked road that "+
           "leads between the two cities of Tyr and Ciubori. This road "+
           "is called 'The Southern Trade-Route' because it is frequently "+
           "used by merchants. East lies a jungle.\n"
           ,60));  

  add_item("road","This is the southern trade-route that leads between "+
           "the cities Tyr and Ciubori.\n");
  add_item("jungle","This is the west part of the large jungles that grows "+
           "on the southeastern part of Athas.\n");
  add_item(({"brick","bricks"}),"The road is made of them.\n");

  OUTSIDE;

  add_exit(S_TRADE+"r24","north");
  add_exit(S_TRADE+"r26","southwest");

}
