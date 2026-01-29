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
           "You're travelling a path in a very bushy area. There is a large mountain to "+
           "the northeast and from the south, you hear the sound of streaming water.\n"
           ,60));  

  add_item("path","It's small and narrow.\n");
  add_item(({"mountain","mountains"}),"The mountains are high with snow on the tops. "+
           "These mountains is the southern part of the large mountain ridge that dominates "+
           "the western parts of Cirath.\n");
  add_item(({"bush","bushes"}),"The bushes are high and hinders the sight.\n");

  OUTSIDE;

  add_exit(W_TRADE+"r05","northeast");
  add_exit(NOMADS+"p08","northwest");
}
