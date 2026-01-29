inherit "/std/object";

#include "defs.h"

void clone_neptune(object to);

void
create_object()
{
   set_short(0);
   set_name("clone_neptune");
   set_no_show();
   
   seteuid(getuid());
}

void
enter_env(object to,object from)
{
   ::enter_env(to,  from);
   set_alarm(5.0,0.0,"clone_neptune",to);
}

void
clone_neptune(object to)
{
   object neptune;
   neptune = clone_object(PIRATES_DIR+"npc/neptune");
   neptune ->move_living("M",to);
   tell_room(ENV(neptune),"Neptune steps forth from the sea.\n");
   remove_object();
}
