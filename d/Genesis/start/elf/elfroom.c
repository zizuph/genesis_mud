
#include "stddefs.h"

#pragma save_binary

inherit "/std/room";
inherit ELFAREA;
inherit STRINGLIB;
inherit MISCLIB;

init()
{
  elfarea::init();
  room::init();
}