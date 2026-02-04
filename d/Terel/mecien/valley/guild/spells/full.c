/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

public void
create_object()
{
   set_name(MYSTIC_FULL);
   set_no_show();
   add_prop(OBJ_M_NO_DROP, 1);
}

public void
set_duration(int dur)
{
   set_alarm(itof(dur), -1.0, remove_object);
}

