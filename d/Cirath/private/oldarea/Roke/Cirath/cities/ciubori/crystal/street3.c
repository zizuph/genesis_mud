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
           "You are standing on Crystal Street in the eastern part of "+
           "Ciubori. East lies one a house belonging to one of the "+
           "citizens. You can enter the local hotel to the west.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");

  OUTSIDE;

  add_exit(CIUBORI+"crystal/street2","north");
  add_exit(CIUBORI+"crystal/street4","south");
  add_exit(CIUBORI+"homes/home6","east");
  add_exit(CIUBORI+"market/hotel","west");
}
