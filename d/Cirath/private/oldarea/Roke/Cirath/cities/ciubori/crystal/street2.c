inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("Crystal Street");
  
  set_long(break_string(
           "You are standing on Crystal Street in the eastern part of "+
           "Ciubori. East lies one a house belonging to one of the "+
           "citizens. West of you is an entrance to a very large "+
           "building. You think it looks like a post office.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");

  OUTSIDE;

  add_exit(CIUBORI+"crystal/street1","north");
  add_exit(CIUBORI+"crystal/street3","south");
  add_exit(CIUBORI+"homes/home5","east");
  add_exit(CIUBORI+"market/post","west");
}
