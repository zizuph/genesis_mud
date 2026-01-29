#pragma save_binary
#pragma strict_types

inherit "/std/scroll";

#include "../guild.h"

int read_access(object ob)
{
  if(ENV(ob) == TP) return ::read_access(ob);
  return 0;
}
