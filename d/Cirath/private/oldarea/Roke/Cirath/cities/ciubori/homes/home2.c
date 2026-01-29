inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("a home in Ciubori");
  
  set_long(break_string(
           "You're standing inside one of the homes in Ciubori. The room looks "+
           "clean and the furniture is not shabby. The citizens of Ciubori are "+
           "quite wealthy.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");

  INSIDE;

  add_exit(CIUBORI+"diamond/street2","south");
}
