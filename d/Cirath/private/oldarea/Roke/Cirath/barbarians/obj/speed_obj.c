inherit "/std/object";

#include "/d/Roke/Cirath/defs.h"
#include "/d/Roke/common/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <herb.h>

int duration = 40;

create_object()
{
  set_no_show();
  set_name("invis_object");
  add_prop(OBJ_I_NO_DROP, 1);
  add_prop(OBJ_I_NO_GIVE, 1);
  TP->add_prop(LIVE_I_QUICKNESS,100);
}

set_duration_time(time)
{
  call_out("destruction",time);
}

destruction()
{
  TP->add_prop(LIVE_I_QUICKNESS,-100);
  write("You slow down.\n");
  say(QCTNAME(TP)+" slows down again.\n");
}

string
stat_object()
{
    string str;
    mixed alarms;
    int t;
    str = "This object is used to make the person move faster "+
          "drinking a potion.\n";
    return str;
}
