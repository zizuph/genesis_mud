inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("Ruby Street");
  
  set_long(break_string(
           "You are standing on Ruby Street close to the city wall in the "+
           "southern part of Ciubori. North lies a large, fancy-looking "+
           "building, but you can't enter it from here.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");

  OUTSIDE;

  add_exit(CIUBORI+"ruby/street3","east");
  add_exit(CIUBORI+"ruby/street1","west");
}
