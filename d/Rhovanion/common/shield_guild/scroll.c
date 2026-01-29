#pragma save_binary

inherit "/std/scroll";

#include "/d/Rhovanion/defs.h"
#include "guild.h"

int read_access(object ob)
{
  if(ENV(ob) == TP) return ::read_access(ob);
  return 0;
}
