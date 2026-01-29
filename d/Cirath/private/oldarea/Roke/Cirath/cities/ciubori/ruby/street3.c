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
           "You're standing in a crossroad, close to the piers in the southern "+
           "part of in Ciubori. "+
           "East and west leads the Ruby Street, while north is the Sapphire "+
           "Street. North lies the piers.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");
  add_item("gate","The gate consists of a draw-bridge that protects the city from "+
           "uninvited guests.\n");

  OUTSIDE;

  add_exit(CIUBORI+"ruby/street4","east");
  add_exit(CIUBORI+"ruby/street2","west");
  add_exit(CIUBORI+"sapphire/street2","north");
  add_exit(CIUBORI+"piers","south");
}
