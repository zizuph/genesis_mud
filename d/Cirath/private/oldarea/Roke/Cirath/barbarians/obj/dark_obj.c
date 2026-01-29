inherit "/std/object";

#include "/d/Roke/Cirath/defs.h"
#include "/d/Roke/common/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <herb.h>

create_object()
{
  set_no_show();
  set_name("invis_object");
  add_prop(OBJ_I_NO_DROP, 1);
  add_prop(OBJ_I_NO_GIVE, 1);
  TP->add_prop(LIVE_I_SEE_DARK,2);
}

set_duration_time(time)
{
  call_out("destruction",time);
}

destruction()
{
  TP->add_prop(LIVE_I_SEE_DARK,-2);
  write("You lose the ability to see in darkness.\n");
}

string
stat_object()
{
    string str;
    mixed alarms;
    int t;
    str = "This object is used to make the person see in darkness after "+
          "drinking a potion.\n";
    return str;
}
