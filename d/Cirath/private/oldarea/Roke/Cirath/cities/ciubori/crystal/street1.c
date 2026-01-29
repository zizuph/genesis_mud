inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("Northeastern corner");
  
  set_long(break_string(
           "You stand in the northeastern corner of Ciubori. To the northeast lies one "+
           "of the guard towers. West is the Diamond Street and south, the Crystal Street.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");

  OUTSIDE;

  add_exit(CIUBORI+"diamond/street5","west");
  add_exit(CIUBORI+"crystal/street2","south");
  add_exit(CIUBORI+"guards/g2","northeast");
}
