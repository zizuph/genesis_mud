
inherit "/std/container";

#include "/d/Krynn/common/defs.h"


void
create_container()
{

}

void
init()
{
  ::init();
    ADA("flick");
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob,from);
  if (from->query_wt() != 3)
    set_alarm(0.0,0.0,"refuse_it",ob,from);

}
