inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("Diamond Street");
  
  set_long(break_string(
           "You are standing on Diamond Street in the northeastern part of "+
           "Ciubori. North lies one a house belonging to one of the "+
           "citizens. South lies a large, impressive building, which you "+
           "can't enter from here. East you see a crossroad.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");

  OUTSIDE;

  add_exit(CIUBORI+"crystal/street1","east");
  add_exit(CIUBORI+"diamond/street4","west");
  add_exit(CIUBORI+"homes/home4","north");
}
