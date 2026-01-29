inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("Northwestern corner");
  
  set_long(break_string(
           "You stand in the northwestern corner of Ciubori. To the northwest lies one "+
           "of the guard towers. East is the Diamond Street and south, the Topaz Street.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");

  OUTSIDE;

  add_exit(CIUBORI+"diamond/street1","east");
  add_exit(CIUBORI+"topaz/street2","south");
  add_exit(CIUBORI+"guards/g1","northwest");
}
