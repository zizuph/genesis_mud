inherit "/std/object";

#include <stdproperties.h>
#include "../guild.h"

void create_object()
{
  set_name("vamp_paralysis_ob");
  set_no_show();
  remove_prop(OBJ_I_WEIGHT);
  remove_prop(OBJ_I_VOLUME);
  remove_prop(OBJ_I_VALUE);
  add_prop(OBJ_M_NO_DROP, 1);
  add_prop(OBJ_M_NO_SELL, 1);
  add_prop(OBJ_M_NO_BUY, 1);
  add_prop(OBJ_M_NO_GET, 1);
}

int catch_all(string str)
{
  switch (query_verb())
  {
    case "quit":
    case "help":
    case "bug":
    case "commune":
    case "typo":
    case "sysbug":
    case "reply":
    case "stop":
    case "systypo":
    case "vthirst":
    case "drop":
    case "v":
    case "i":
    case "vitals":
    case "inventory":
    case "h":
    case "health":
    case "stats":
    case "l":
    case "look":
    case "exa":
    case "examine":
      return 0;
  }

  write("That is impossible in your current state.\n");
  return 1;
}

void init()
{
  ::init();

  if (IS_WIZ(TP))
  {
    return;
  }

  add_action(catch_all, "", 1);
}


