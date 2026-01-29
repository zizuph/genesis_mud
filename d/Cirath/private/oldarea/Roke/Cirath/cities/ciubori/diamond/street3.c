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
           "You're standing in a crossroad, close to the northern gate in Ciubori. "+
           "East and west leads the Diamond Street, while south is the Sapphire "+
           "Street. North lies the gate.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");
  add_item("gate","The gate consists of a draw-bridge that protects the city from "+
           "uninvited guests.\n");

  OUTSIDE;

  add_exit(CIUBORI+"diamond/street4","east");
  add_exit(CIUBORI+"diamond/street2","west");
  add_exit(CIUBORI+"gate","north");
  add_exit(CIUBORI+"sapphire/street1","south");
}
