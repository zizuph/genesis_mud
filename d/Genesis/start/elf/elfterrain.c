
#include "stddefs.h"

#pragma save_binary

// inherit "/std/mapsquare";
inherit ELFAREA;
inherit STRINGLIB;
inherit MISCLIB;

init()
{
  elfarea::init();
//   mapsquare::init();
}
