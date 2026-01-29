inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("Southwestern corner");
  
  set_long(break_string(
           "You stand in the southwestern corner of Ciubori. To the southwest lies one "+
           "of the guard towers. East is the Ruby Street and north, the Topaz Street.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");

  OUTSIDE;

  add_exit(CIUBORI+"ruby/street1","east");
  add_exit(CIUBORI+"topaz/street3","north");
  add_exit(CIUBORI+"guards/g4","southwest");
}
