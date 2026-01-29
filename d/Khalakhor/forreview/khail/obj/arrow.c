#include "/d/Immortal/std/domain.h"

inherit STDOBJECT;

int
is_ammunition()
{ return 1; }

void
create_object()
{
  set_name("arrow");
  set_short("arrow");
  set_long("A long thin arrow for helping debug the missile system\n");
}
