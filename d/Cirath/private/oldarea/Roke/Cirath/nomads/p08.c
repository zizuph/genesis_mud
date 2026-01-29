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
           "You are standing on a path at the base of a large mountain. There's a "+
           "stream to your south and beyond it lies some plains. The vegitation consists "+
           "of grass and some high bushes.\n"
           ,60));  

  add_item("path","It's small and narrow.\n");
  add_item("stream","The stream is shimmering in the sunlight.\n");
  add_item(({"mountain","mountains"}),"The mountains are high with snow on the tops. "+
           "These mountains is the southern part of the large mountain ridge that dominates "+
           "the western parts of Cirath.\n");
  add_item(({"plain","plains"}),"They are vast. You think you can spot some kind of "+
           "town there too.\n");
  add_item(({"bush","bushes"}),"The bushes makes it hard to see where you go.\n");

  OUTSIDE;
  WATER;

  add_exit(NOMADS+"p09","southeast");
  add_exit(NOMADS+"p07","west");
}
