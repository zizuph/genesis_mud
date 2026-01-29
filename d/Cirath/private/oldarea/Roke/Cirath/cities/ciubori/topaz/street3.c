inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("Topaz Street");
  
  set_long(break_string(
           "You are standing on Topaz Street in the western part of "+
           "Ciubori. West lies one a house belonging to one of the "+
           "citizens. You can enter a pub to the east.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");

  OUTSIDE;

  add_exit(CIUBORI+"topaz/street2","north");
  add_exit(CIUBORI+"topaz/street4","south");
  add_exit(CIUBORI+"homes/home8","west");
  add_exit(CIUBORI+"market/pub","east");
}
