inherit "/std/object";

#include "../guild.h"
#include <stdproperties.h>

static object who;

void create_object()
{
  set_name("_vamp_bitten_paralysis");
  set_no_show();
  remove_prop(OBJ_I_WEIGHT);
  remove_prop(OBJ_I_VALUE);
  remove_prop(OBJ_I_VOLUME);
  add_prop(OBJ_M_NO_GET, "");
  add_prop(OBJ_M_NO_DROP, "");
  add_prop(OBJ_M_NO_SELL, "");
  add_prop(OBJ_M_NO_BUY, "");
}

int catch_all(string str)
{
  switch (query_verb())
  {
    case "help":
    case "bug":
    case "commune":
    case "typo":
    case "sysbug":
    case "reply":
    case "stop":
    case "systypo":
    case "vthirst":
    case "vitals":
    case "health":
    case "h":
    case "drop":
      return 0;
  }

  write("You can't manage it.\n");
  return 1;
}

void init()
{
  ::init();

  if (environment() == this_player())
  {  
    if (!IS_WIZ(this_player()))
    {
#ifndef BLOCK_PLAYERS
        if (this_player()->query_npc())
        {
            add_action(catch_all, "", 1);
        }
#else
        add_action(catch_all, "", 1);
#endif
        this_player()->add_stun();
    }

    who = this_player();
  }
}

void remove_object()
{
  if (who)
  {  
    who->remove_stun();
  }

  ::remove_object();
}

void enter_env(object env, object from)
{
  ::enter_env(env, from);

  if (!living(env))
  {
    remove_object();
  }
}
