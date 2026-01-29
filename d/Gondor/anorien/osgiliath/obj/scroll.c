inherit "/std/object";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_object()
{
  set_name("scroll");
  set_adj("yellowed");
  set_long("Some old and wrinkled letters are written on it.\n");
  add_prop(OBJ_I_VALUE,0);
  add_prop(OBJ_I_WEIGHT,10);
  add_prop(OBJ_I_VOLUME,10);
}

init()
{
  add_action("read_scroll","read");
}

read_scroll(string str)
{
  if (!str)
    {
      notify_fail("Read what?\n");
      return 0;
    }
  if (str=="scroll" || str == "text" || str == "text on scroll")
    {
      cat(OSG_DIR+"obj/scroll.txt");
      return 1;
    }
  notify_fail("Read what?\n");
  return 0;
}

