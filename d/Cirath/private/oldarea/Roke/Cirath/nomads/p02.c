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
           "You are standing on a path in a pass between two mountains. "+
           "A stream is flowing beside the path.\n"
           ,60));  

  add_item("path","It's small and narrow.\n");
  add_item("stream","The stream is shimmering in the sunlight.\n");
  add_item("vegetation","Just some low, dry bushes and grass.\n");
  add_item(({"mountain","mountains"}),"The mountains are high with snow on the tops. "+
           "These mountains is the southern part of the large mountain ridge that dominates "+
           "the western parts of Cirath.\n");
  OUTSIDE;
  WATER;

  add_exit(NOMADS+"p03","southeast");
  add_exit(NOMADS+"p01","northwest");
}
