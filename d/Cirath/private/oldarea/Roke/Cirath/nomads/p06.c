inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On a path");
  
  set_long(break_string(
           "This is a small path in the southwestern part of the kingdom Cirath. "+
           "North lies a large mountain and south flows a small stream.\n"
           ,60));  

  add_item("path","It's small and narrow.\n");
  add_item("stream","The stream is shimmering in the sunlight.\n");
  add_item(({"mountain","mountains"}),"The mountains are high with snow on the tops. "+
           "These mountains is the southern part of the large mountain ridge that dominates "+
           "the western parts of Cirath.\n");
  OUTSIDE;
  WATER;

  add_exit(NOMADS+"p07","northeast");
  add_exit(NOMADS+"p05","west");
}
