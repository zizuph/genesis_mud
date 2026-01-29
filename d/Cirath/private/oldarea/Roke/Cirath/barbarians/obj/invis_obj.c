inherit "/std/object";

#include "/d/Roke/Cirath/defs.h"
#include "/d/Roke/common/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <herb.h>

int invis;

create_object()
{
  set_no_show();
  set_name("invis_object");
  add_prop(OBJ_I_NO_DROP, 1);
  add_prop(OBJ_I_NO_GIVE, 1);
  TP->set_invis(50);
}

set_invis_time(time)
{
  call_out("destruction",time);
}

destruction()
{
  TP->set_invis(0);
  write("You become visable again.\n");
  say(QCTNAME(TP)+" suddenly appears in front of you!\n");
}

string
stat_object()
{
    string str;
    mixed alarms;
    int t;
    str = "This object is used to make the person invisible after drinking "+
          "a potion.\n";
    return str;
}
