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
           "Ciubori. The street is very crowdy and to your east you "+
           "can see a large building which has an entrance to a shop.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");
  add_item("shop","It looks that way anyway.\n");

  OUTSIDE;

  add_exit(CIUBORI+"topaz/street1","north");
  add_exit(CIUBORI+"topaz/street3","south");
  add_exit(CIUBORI+"homes/home7","west");
  add_exit(CIUBORI+"market/shop","east");
}
